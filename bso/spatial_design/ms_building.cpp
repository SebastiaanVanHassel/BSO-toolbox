#ifndef MS_BUILDING_CPP
#define MS_BUILIDNG_CPP

#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <exception>
#include <boost/algorithm/string.hpp>
#include <bitset>

namespace bso { namespace spatial_design {

ms_building::ms_building()
{ // empty constructor
	mLastSpaceID = 0;
} // ms_building() (empty constructor)

ms_building::ms_building(std::string fileName)
{ // initilization by string or text file
	mLastSpaceID = 0;
	std::ifstream input;
	if (!fileName.empty()) input.open(fileName.c_str());
	
	if (fileName.empty() || !input.is_open())
	{
		std::stringstream errorMessage;
		errorMessage << "Could not initialize an MS building spatial design with the following input file:" << std::endl
								 << ((fileName.empty())? "no input file given" : fileName) << std::endl
								 << "(bso/spatial_design/ms_building.cpp). " << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
	
	std::string line;

	while (!input.eof()) // Parse the input file line by line
	{
		getline(input,line); // get next line from the file
		try
		{
			boost::algorithm::trim(line); // remove white space from start and end of line (to see if it is an empty line, removes any incidental white space)
			if (line == "") //skip empty lines (tokenizer does not like it)
			{
				continue; // continue to next line
			}
			else if (line.substr(0,2) == "R," || line.substr(0,2) == "r,")
			{
				line.erase(0,2);
				mSpaces.push_back(new ms_space(line));
			}
			else
			{
				continue;
			}
		}
		catch(std::exception& e)
		{
			std::stringstream errorMessage;
			errorMessage << "Encountered an error while parsing the following line of an MS input file:" << std::endl
									 << line << std::endl
									 << "(bso/spatial_design/ms_building.cpp). Got the following error: " << std::endl
									 << e.what() << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
	}
	
	mLastSpaceID = this->getLastSpaceID();
	this->checkValidity();
} // ms_building() (constructor using input file)

ms_building::ms_building(const ms_building& rhs)
{ // copy constructor
	mLastSpaceID = rhs.mLastSpaceID;
	for (auto i : rhs.mSpaces)
	{
		mSpaces.push_back(new ms_space(*i));
	}
	
	this->checkValidity();
} // ms_building() (copy constructor)

ms_building::ms_building(const sc_building& sc)
{ // convert SC to MS
	try
	{
		// initialize variables and variable size
		mLastSpaceID = 0;
		std::vector<unsigned int> originIndices = {sc.getWSize(), sc.getDSize(), sc.getHSize()};
		std::vector<std::vector<double> > globalCoords(3);
		std::vector<std::vector<double> > dimensions(3);
		for (unsigned int i = 0; i < 3; i++)
		{
			globalCoords[i] = std::vector<double>(originIndices[i]+1);
			dimensions[i] = std::vector<double>(originIndices[i]);
		}
		for (unsigned int i = 0; i < originIndices[0]; i++) dimensions[0][i] = sc.getWValue(i);
		for (unsigned int i = 0; i < originIndices[1]; i++) dimensions[1][i] = sc.getDValue(i);
		for (unsigned int i = 0; i < originIndices[2]; i++) dimensions[2][i] = sc.getHValue(i);

		// find the lowest cell indices (w,d,h) that index an active cell (i.e. they will represent the origin)
		for (unsigned int i = 1; i < sc.getBRowSize(); i++)
		{ // for each cell
			std::vector<unsigned int> indices = {sc.getWIndex(i), sc.getDIndex(i), sc.getHIndex(i)}; // temporarily store the indices (w,d,h)
			
			for (unsigned int j = 0; j < sc.getBSize(); j++)
			{ // for each space
				if (sc.getBValue(j,i) == 1)
				{ // if the cell i is active for space j
					for (unsigned int k = 0; k < 3; k++) 
					{ // check for each index
						if (indices[k] < originIndices[k])
						{ // if it is lower than the lowest found so far to index an active cell
							originIndices[k] = indices[k]; // if it is, set the lowest found to it.
						}
					}
				}
			}
		}

		for (unsigned int i = 0; i < 3; i++)
		{ // for each index
			globalCoords[i][originIndices[i]] = 0.0; // set the origins coordinate value to zero
			for (unsigned int j = originIndices[i] + 1; j < globalCoords[i].size(); j++)
			{ // for each consequent index value increment with the width of the dimensions described by the supercube
				globalCoords[i][j] = globalCoords[i][j-1] + dimensions[i][j-1];
			}
		}
		
		for (unsigned int i = 0; i < sc.getBSize(); i++)
		{ // for each space
			// find the indices of the minium and maximum cell index that is active for space i
			unsigned int max = 0, min = 0;
			for (unsigned int j = 0; j < sc.getBRowSize(); j++)
			{
				if (min == 0 && sc.getBValue(i,j) == 1) min = j;
				if (sc.getBValue(i,j) == 1) max = j;
			}
			
			//get the locations and dimensions from these indices
			utilities::geometry::vertex location;
			location << globalCoords[0][sc.getWIndex(min)],
									globalCoords[1][sc.getDIndex(min)],
									globalCoords[2][sc.getHIndex(min)];
			location.round(0);
			
			utilities::geometry::vector dimensions;
			dimensions << globalCoords[0][sc.getWIndex(max)+1],
										globalCoords[1][sc.getDIndex(max)+1],
										globalCoords[2][sc.getHIndex(max)+1];
			dimensions -= location;
			dimensions.round(0);
			
			//initialize a new space with the found location and dimensions
			mSpaces.push_back(new ms_space(sc.getBValue(i,0), location, dimensions));
			
			// check if the last space ID is up to date.
			if (mLastSpaceID < mSpaces.back()->getID())
			{ // if it is not, up date it
				mLastSpaceID = mSpaces.back()->getID();
			}
		}
	}
	catch (std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Could not convert SC building into MS building" << std::endl
								 << "(bso/spatial_design/ms_building.cpp)." << std::endl
								 << "Got the following error: " << std::endl
								 << e.what() << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
	
	
} // ms_building() (convert SC to MS)

ms_building::~ms_building()
{ // destructor
	for (auto i : mSpaces) delete i;
} // ~ms_building()

void ms_building::checkValidity() const
{
	
} // checkValidity()

void ms_building::writeToFile(std::string fileName) const
{
	std::ofstream output;
	if (!fileName.empty()) output.open(fileName.c_str());
	
	if (fileName.empty() || !output.is_open())
	{
		std::stringstream errorMessage;
		errorMessage << "Could not open the following file to write an MS building spatial design to:" << std::endl
								 << ((fileName.empty())? "no input file given" : fileName) << std::endl
								 << "(bso/spatial_design/ms_building.cpp). " << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
	
	output << *this;
} // writeToFile()

std::vector<ms_space*> ms_building::getSpacePtrs() const
{
	return mSpaces;
} //getSpacePtrs()

ms_space* ms_building::getSpacePtr(const ms_space& space) const
{
	for (auto i : mSpaces)
	{
		if (/*i == &space ||*/ *i == space)
		{
			return i;
		}
	}
	
	// if this part of code is reached, the space was not found in the preceding for loop
	std::stringstream errorMessage;
	errorMessage << "Could not find the following space in an MS building spatial design:" << std::endl
							 << space << std::endl
							 << "(bso/spatial_design/ms_building.cpp). " << std::endl;
	throw std::runtime_error(errorMessage.str());
} // getSpacePtr()

ms_space* ms_building::getSpacePtr(const ms_space* spacePtr) const
{
	return getSpacePtr(*spacePtr);
}

unsigned int ms_building::getLastSpaceID() const
{
	for (auto i : mSpaces)
	{
		if (mLastSpaceID < i->getID()) mLastSpaceID = i->getID();
	}
	return mLastSpaceID;
} // getLastSpaceID()

double ms_building::getVolume() const
{
	double volume = 0;
	for (auto i : mSpaces) volume += i->getVolume();
		
	return volume;
} // getVolume()

void ms_building::setZZero()
{
	double min = mSpaces[0]->getCoordinates()(2); // set an initial value to the minimum
	
	// find the minimum value of the z-coordinates in the building
	for (auto i : mSpaces) if (i->getCoordinates()(2) < min) min = i->getCoordinates()(2); 
	if (min <= 0) return;
	
	utilities::geometry::vector coordDifference;
	coordDifference << 0, 0, -min;
	
	for (auto i : mSpaces) i->setCoordinates(i->getCoordinates() + coordDifference);
} // setZZero()

void ms_building::addSpace(const ms_space& space)
{
	try
	{
		mSpaces.push_back(new ms_space(space));
		checkValidity();
	}
	catch(std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Could not add the following space to an MS building spatial design: " << std::endl
								 << space << std::endl
								 << "(bso/spatial_design/ms_building.cpp). Got the following error message: " << std::endl
								 << e.what() << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
} // addSpace

void ms_building::deleteSpace(ms_space* spacePtr)
{
	if (std::find(mSpaces.begin(), mSpaces.end(), spacePtr) == mSpaces.end()) spacePtr = getSpacePtr(spacePtr);
	try
	{
		mSpaces.erase(std::remove(mSpaces.begin(), mSpaces.end(), spacePtr), mSpaces.end());
	}
	catch(std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Could not delete the following space from an MS building spatial design: " << std::endl
								 << *spacePtr << std::endl
								 << "(bso/spatial_design/ms_building.cpp). Got the following error message: " << std::endl
								 << e.what() << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
} // deleteSpace()

void ms_building::deleteSpace(ms_space& space)
{
	this->deleteSpace(this->getSpacePtr(space));
}

void ms_building::scale(const std::vector<std::pair<unsigned int, double> >& scales /*= {{0,sqrt(2.0)},{1,sqrt(2.0)}}*/)
{
	utilities::geometry::vertex coords;
	utilities::geometry::vector tempSum;
	
	unsigned int axis;
	double n;
	bool checkDouble[3] = {false};
	
	for (auto i : scales)
	{
		axis = i.first;
		if (axis != 0 && axis != 1 && axis != 2)
		{
			std::stringstream errorMessage;
			errorMessage << "Trying to scale an MS building spatial design over the following non-existent axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		
		if (checkDouble[axis])
		{
			std::stringstream errorMessage;
			errorMessage << "Defined a scaling factor to scale and MS building spatial design twice for the same axis, axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		else checkDouble[axis] = true;
	}
	
	for (auto i : mSpaces)
	{
		coords = i->getCoordinates();
		tempSum = coords + i->getDimensions();

		for (auto j : scales)
		{
			axis = j.first;
			n = j.second;
			
			coords(axis)  *= n;
			tempSum(axis) *= n;
		}

		i->setCoordinates(coords);
		i->setDimensions(tempSum - coords);
	}
} // scale()

void ms_building::splitSpace(ms_space* spacePtr, const std::vector<std::pair<unsigned int, unsigned int> >& splits /*= {{0,2},{1,2}}*/)
{	
	this->getLastSpaceID();
	utilities::geometry::vertex coords  = spacePtr->getCoordinates();
	utilities::geometry::vector tempSum = coords + spacePtr->getDimensions();
	
	std::vector<double> splitValues[3];
	for (unsigned int i = 0; i < 3; i++)
	{
		splitValues[i] = std::vector<double>();
		splitValues[i].push_back(coords(i));
		splitValues[i].push_back(tempSum(i));
	}
	
	unsigned int axis, div;
	bool checkDouble[3] = {false};
	
	for (auto i : splits)
	{
		axis = i.first;
		div = i.second;
		
		if (axis != 0 && axis != 1 && axis != 2)
		{
			std::stringstream errorMessage;
			errorMessage << "Trying to split space \"" << spacePtr->getID() << "\" over a non-existing axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		
		if (div < 2)
		{
			std::stringstream errorMessage;
			errorMessage << "Trying to split space \"" << spacePtr->getID() << "\" into less than two new spaces: n_split = " << div << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		
		if (checkDouble[axis])
		{
			std::stringstream errorMessage;
			errorMessage << "Defined a split for space \"" << spacePtr->getID() << "\" twice for the same axis, axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		else checkDouble[axis] = true;
		
		double delta = floor((splitValues[axis][1] - splitValues[axis][0])/div);

		for (unsigned int i = 0; i < div-1; i++)
		{
			double nextCoord;
			nextCoord = splitValues[axis][i] + delta;
			splitValues[axis].insert(splitValues[axis].begin() + i + 1,nextCoord);
		}
	}
	
	ms_space* temp;
	for (unsigned int i = 0; i < splitValues[0].size() - 1; i++)
	{
		for (unsigned int j = 0; j < splitValues[1].size() - 1; j++)
		{
			for (unsigned int k = 0; k < splitValues[2].size() - 1; k++)
			{
				temp = new ms_space(*spacePtr);
				temp->setID(++mLastSpaceID);
				coords << splitValues[0][i], splitValues[1][j], splitValues[2][k];
				temp->setCoordinates(coords);
				tempSum << splitValues[0][i+1], splitValues[1][j+1], splitValues[2][k+1];
				temp->setDimensions(tempSum - coords);
				mSpaces.push_back(temp);
			}
		}
	}
	
	deleteSpace(spacePtr);
} // splitSpace()

void ms_building::splitSpace(ms_space& space, const std::vector<std::pair<unsigned int, unsigned int> >& splits /*= {{0,2},{1,2}}*/)
{
	this->splitSpace(this->getSpacePtr(space), splits);
} // splitSpace()

void ms_building::snapOn(const std::vector<std::pair<unsigned int, double> >& snaps /*= {{0,10},{1,10}}*/)
{
	utilities::geometry::vertex coords;
	utilities::geometry::vector tempSum;
	
	unsigned int axis;
	double n;
	bool checkDouble[3] = {false};
	
	for (auto i : snaps)
	{
		axis = i.first;
		if (axis != 0 && axis != 1 && axis != 2)
		{
			std::stringstream errorMessage;
			errorMessage << "Trying to snap-on an MS building spatial to a grid over the following non-existent axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		
		if (checkDouble[axis])
		{
			std::stringstream errorMessage;
			errorMessage << "Defined a snap-on for an MS building spatial design twice for the same axis, axis: " << axis << std::endl
									 << "(bso/spatial_design/ms_building.cpp)." << std::endl;
			throw std::invalid_argument(errorMessage.str());
		}
		else checkDouble[axis] = true;
	}
	
	for (auto i : mSpaces)
	{
		coords = i->getCoordinates();
		tempSum = coords + i->getDimensions();
		
		for (auto j : snaps)
		{
			axis = j.first;
			n = j.second;

			coords(axis)  = round(coords(axis)  / n) * n;
			tempSum(axis) = round(tempSum(axis) / n) * n;
		}
		
		i->setCoordinates(coords);
		i->setDimensions(tempSum - coords);
	}
} // snapOn()

bool ms_building::checkSCCEll(const sc_building& sc, const unsigned int& cellIndex, const unsigned int& spaceIndex, utilities::geometry::vertex /*= {0.0,0.0,0.0}*/) const 
{
	
}

bool ms_building::operator == (const ms_building& rhs)
{
	if (mSpaces.size() != rhs.mSpaces.size()) return false;
	
	// check if rhs contains the same spaces, assuming they may be in different order
	std::vector<ms_space*> cmp = rhs.mSpaces; // copy the vector containing the spaces to safe computation time, matches can be removed from this
	std::reverse(cmp.begin(), cmp.end()); // reverse the vector, since items will be removed we want to iterate from the back, however if vectors are same order we want to benefit from that to safe computation time

	for (auto i : mSpaces)
	{
		bool found = false;
		for (unsigned int j = cmp.size(); j > 0; j--)
		{
			if (*i == *(cmp[j - 1]))
			{
				found = true;
				cmp.erase(cmp.begin() + j - 1);
				break;
			}
		}
		if (!found) return false;
	}
	return true;
}

bool ms_building::operator != (const ms_building& rhs)
{
	return !(*this == rhs);
}

ms_building::operator sc_building() const
{ // convert MS to SC
	try
	{
		sc_building sc;
		std::vector<std::vector<double> > coordValues(3); // {xValues,yValues,Zvalues}
		
		// store all coordinate values in this MS building model in the three std::vectors
		for (auto i : mSpaces)
		{
			utilities::geometry::vertex p1 = i->getCoordinates();
			utilities::geometry::vertex p2 = i->getDimensions() + p1;
			for (unsigned int i = 0; i < 3; i++)
			{
				coordValues[i].push_back(p1(i));
				coordValues[i].push_back(p2(i));
			}
		}
		
		// sort the three vectors with coordinate values, and remove duplicates
		for (auto& i : coordValues)
		{
			sort(i.begin(), i.end());
			i.erase(std::unique(i.begin(), i.end()), i.end());
		}
		
		// create the width, depth and height vectors of the supercube, and compute the size of the bitmask of the b vectors
		unsigned int cubeSize = 1;
		for (unsigned int i = 0; i < coordValues.size(); i++)
		{
			std::vector<double> tempDimensions;
			for (unsigned int j = 0; j < coordValues[i].size()-1; j++)
			{
				tempDimensions.push_back(coordValues[i][j+1] - coordValues[i][j]);
			}
			
			cubeSize *= tempDimensions.size();
			if (i == 0) sc.mWValues = tempDimensions;
			else if (i == 1) sc.mDValues = tempDimensions;
			else if (i == 2) sc.mHValues = tempDimensions;
		}
		
		// for each space, create an emtpy bit mask, and subsequently find out which cells in that mask belong to the space, and should be activated
		for (auto i : mSpaces)
		{
			std::vector<int> tempRow(cubeSize + 1);
			tempRow[0] = i->getID();
			
			utilities::geometry::vertex p1 = i->getCoordinates();
			utilities::geometry::vertex p2 = i->getDimensions() + p1;
			
			for (unsigned int j = 1; j < tempRow.size(); j++)
			{
				utilities::geometry::vertex pCheck = utilities::geometry::vertex();
				pCheck[0] = sc.getWValue(j);
				pCheck[1] = sc.getDValue(j);
				pCheck[2] = sc.getHValue(j);
				
				bool belongsToSpace = true;
				for (unsigned int k = 0; k < 3; k++)
				{
					if (pCheck[k] < p1[k] || pCheck[k] >= p2[k])
					{
						belongsToSpace = false;
						break;
					}
				}
				tempRow[j] = belongsToSpace;
			}
			sc.mBValues.push_back(tempRow);
		}
		sc.checkValidity();
		return sc;
	}
	catch (std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Could not convert MS building into SC building" << std::endl
								 << "(bso/spatial_design/ms_building.cpp)." << std::endl
								 << "Got the following error: " << std::endl
								 << e.what() << std::endl;
		throw std::invalid_argument(errorMessage.str());
	}
} // sc_building() (convert MS to SC)

std::ostream& operator <<(std::ostream& stream, const ms_building& building)
{
	bool first = true;
	for (auto i : building.getSpacePtrs())
	{
		if (!first) stream << std::endl;
		else first = false;
		stream << *i;
	}
	
	return stream;
} // << operator

} // namespace spatial_design
} // namespace bso

#endif // MS_BUILDING_CPP