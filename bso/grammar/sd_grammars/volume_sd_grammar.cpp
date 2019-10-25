#ifndef BSO_GRAMMAR_VOLUME_SD_GRAMMAR_CPP
#define BSO_GRAMMAR_VOLUME_SD_GRAMMAR_CPP

#include <stdexcept>
#include <sstream>

namespace bso { namespace grammar {

template <>
structural_design::sd_model grammar::sd_grammar<VOLUME_SD_GRAMMAR>(const std::string& fileName,
	const bool& useSurfaceTypeInsteadOfSpaceType /*= false*/,
	const bool& b2 /*= false*/, const bool& b3 /*= false*/)
{
	// initialize a new SD model
	mSDModel = bso::structural_design::sd_model();
	// read the structural design settings
	this->mReadSDSettings(fileName);

	for (const auto& i : mCuboidProperties)
    {
        // get the space type depending on the settings
        std::string usedType = i.second->getSpaceType();

        // determine the structural type and properties of the cuboid
        bool structureFound = false;
        auto structureSearch = mSDSpaceProperties.find(usedType);
			if (i.second->isInSpace())
			{
				if (structureSearch != mSDSpaceProperties.end())
				{
					structureFound = true;
				}
			}

			if (!structureFound)
			{
				std::stringstream errorMessage;
				errorMessage << "\nError, in volume grammar could not find the specified\n"
										 << "type settings: \"" << usedType << "\" ("
										 //<< ((i.second->isInSpace())? "space" ) << ")\n"
										 << "Has this type set been specified in the inputfile?: \""
										 << fileName << "\"\n(bso/grammar/sd_grammars/volume_sd_grammar.cpp)"
										 << std::endl;
				throw std::runtime_error(errorMessage.str());
			}

        // create a cuboid rule set
        auto sdCuboidRuleSet = new rule_set::sd_cuboid_rule(i.second);
        mSDCuboidRules[i.first] = sdCuboidRuleSet;
        if (structureSearch->second.type() != "none")
        {
            sdCuboidRuleSet->assignStructure(structureSearch->second);
        }
    }

	for (const auto& i : mRectangleProperties)
	{
		if (i.second->isSpaceSeparating())
		{
			// get the space or surface types, depending on the settings
			std::pair<std::string, std::string> usedTypes = i.second->getSpaceTypes();
			if (useSurfaceTypeInsteadOfSpaceType) usedTypes = i.second->getSurfaceTypes();

			// determine the structural type and properties of the rectangle
			bool structureFound = false;
			auto structureSearch = mSDFloorProperties.find(usedTypes);
			if (i.second->isFloor())
			{
				if (structureSearch != mSDFloorProperties.end())
				{
					structureFound = true;
				}
			}
			else if (i.second->isWall())
			{
				structureSearch = mSDWallProperties.find(usedTypes);
				if (structureSearch != mSDWallProperties.end())
				{
					structureFound = true;
				}
			}
			if (!structureFound)
			{
				std::stringstream errorMessage;
				errorMessage << "\nError, in volume grammar could not find the specified\n"
										 << "type settings: \"" << usedTypes.first << "\" - \""
										 << usedTypes.second << "\" ("
										 << ((i.second->isFloor())? "floor" : "wall") << ")\n"
										 << "Has this type set been specified in the inputfile?: \""
										 << fileName << "\"\n(bso/grammar/sd_grammars/volume_sd_grammar.cpp)"
										 << std::endl;
				throw std::runtime_error(errorMessage.str());
			}

			// create a rectangle rule set
			auto sdRectangleRuleSet = new rule_set::sd_rectangle_rule(i.second);
			mSDRectangleRules[i.first] = sdRectangleRuleSet;
			if (structureSearch->second.type() != "none")
			{
				sdRectangleRuleSet->assignStructure(structureSearch->second);
			}
			sdRectangleRuleSet->assignLoadPanel(mLoadPanel);
			sdRectangleRuleSet->addLoads(&mLoads);
		}
	}
	// find each line that is associated to a rectangle that has a rectangle rule set
	for (const auto& i : mSDRectangleRules)
	{ // for each sd rectangle rule
		for (const auto& j : i.first->cfLines())
		{ // for each line associated to the rectangle associated to the rectangle rule
			if (mSDLineRules.find(j) == mSDLineRules.end());
			{ // if it has not yet been added to the vector, add it
				mSDLineRules[j] = new rule_set::sd_line_rule(mLineProperties[j]);
			}
		}
	}

	for (auto& i : mSDLineRules)
	{ // for each sd line rule
		// find the potential structural types from all the possible sd rectangle rules this
		// line rule may be associated with
		std::vector<structural_design::component::structure> potentialStructures;
		for (const auto& j : i.first->cfRectangles())
		{ // for each rectangle that this line is associated with
			auto SDRectangleRuleSearch = mSDRectangleRules.find(j);
			if (SDRectangleRuleSearch != mSDRectangleRules.end())
			{ // if that rectangle is accociated with an sd rectangle rule, store its structural type
				potentialStructures.push_back(SDRectangleRuleSearch->second->getStructure());
			}
		}

		// pass the potential structural types to the sd line rule
		i.second->assignStructure(potentialStructures);
	}
	for (const auto& i : mVertexProperties)
	{
		if (i.second->isSpaceCorner())
		{
			mSDVertexRules[i.first] = new rule_set::sd_vertex_rule(i.second);
		}
	}

	for (const auto& i : mSDVertexRules) i.second->apply(mSDModel);
	for (const auto& i : mSDLineRules) i.second->apply(mSDModel);
	for (const auto& i : mSDRectangleRules) i.second->apply(mSDModel);
	for (const auto& i : mSDCuboidRules) i.second->apply(mSDModel);
	mSDModel.setMeshSize(mMeshSize);

	// delete the rules
	for (auto& i : mSDVertexRules) delete i.second;
	for (auto& i : mSDLineRules) delete i.second;
	for (auto& i : mSDRectangleRules) delete i.second;
	for (auto& i : mSDCuboidRules) delete i.second;

	return mSDModel;
} // volume_sd_grammar

} // namespace grammar
} // namespace bso

#endif // BSO_GRAMMAR_VOLUME_SD_GRAMMAR_CPP
