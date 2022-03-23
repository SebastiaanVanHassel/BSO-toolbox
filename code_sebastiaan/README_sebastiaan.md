# README: Sebastiaan van Hassel Graduation thesis 2022

## Modified C++ files in the BSO-toolbox v1.0.0
The BSO-toolbox repository from TUe-excellent-buildings is used in the graduation project of Sebastiaan van Hassel. Thereby, seven files of the BSO-toolbox v1.0.0 are modified. It concerns the following files with directories:
1.   BSO-toolbox/bso/spatial_design/ms_building.cpp
2.   BSO-toolbox/bso/spatial_design/ms_building.hpp
3.   BSO-toolbox/bso/spatial_design/ms_space.cpp
4.   BSO-toolbox/bso/spatial_design/ms_space.hpp
5.   BSO-toolbox/bso/building_physics/properties/construction.cpp
6.   BSO-toolbox/bso/structural_design/component/structure.cpp
7.   BSO-toolbox/bso/utilities/geometry/quad_hexahedron.hpp

The files, “ms_building.cpp”, “ms_building.hpp”, “ms_space.cpp”, and “ms_space.hpp”, are modified to include non-orthogonal designs in the toolbox.
The files, “construction.cpp” and “structure.cpp”, are modified to solve error messages that occurred after the transfer to a new workstation 2 (Brisbane). 
The file, “quad_hexahedron.hpp”, is modified by the author, to the purpose of his thesis. 

## C++ Code written by Sebastiaan for his Graduation thesis
The code is related to the two research methods: Machine Learning (ML) and Genetic Algorithm (GA). The code is written in C++14 and uses external libraries in some of the files. An overview of all created C++ files is listed below. (File name, for which research method, on what operating system, and which external libraries are included.)

| File name	                | Method	     | Operating system	  | Includes BSO-toolbox	| Includes Eigen	| Includes OpenGL	  | Includes mlpack |
| ---												|	---					 | ---								| ---			  						| ---							| ---								| ---						  |
| generateBSDs_ML.cpp	      | ML	         | Linux							|												|									|										|								  |
| generateDataset_ML.cpp	  | ML	         | Linux	            |        x	            |          x			|										|									|
| NeuralNetwork_TRAIN.cpp	  | ML	         | Windows				    |                       |                 |                   |         x				|
| NeuralNetwork_PREDICT.cpp	| ML	         | Windows				    |                       |                 |                   |         x				|
| Visualisation_ML.cpp	    | ML	         | Linux			        |                       |                 |          x				|									|
| GA1and2.cpp	              | GA	         | Linux	            |        x							|									|										|									|
| Visualisation_GA.cpp	    | GA	         | Linux			        |                       |                 |          x				|									|

#### Operating system
Most of the files make use of a Linux operating system. These files are compiled on a server at the University. The two Neural Network files, which include the mlpack C++ library make use of a Windows operating system. The mlpack library is not installed on the server of the University and therefore, installed and used on the personal computer (Windows OS) of the author.

#### External software
The code is mainly based on two external software packages: BSO-toolbox and mlpack C++ library.
Other external libraries are included within these two software installations.

An overview of all external software is listed below. The reference to the documentation and installation guide, as well as, the used versions of all libraries are indicated.
*	BSO-toolbox developed at Eindhoven University of Technology
	-	See https://github.com/TUe-excellent-buildings/BSO-toolbox for documentation and installation guide.
	-	Version = v1.0.0
*	Eigen C++ library for linear algebra. (Installed with the BSO-toolbox installation)
	-	Version = v3.4.0
*	Boost C++ library for various utilities. (Installed with the BSO-toolbox installation)
	-	Version = v1.071.00
*	OpenGL C++ library for visualisation. (Installed with the BSO-toolbox installation)
	-	GSL (last tested for v2.4+dfsg-6 amd64)
	-	freeglut3 (last tested for v2.8.1-3 amd64)
*	Mlpack C++ library for Machine learning.
	-	See https://www.mlpack.org/ for documentation and installation guide.
	-	mlpack is built and used on Windows 10 and Visual Studio 2019.
	-	Version = v3.4.2
	-	mlpack is built on:
		*	Armadillo C++ linear algebra library (v10.8.2)
		*	Ensmallen C++ numerical optimization library (v2.14.2)
		*	Boost C++ library (v1.75.0)

#### Makefile (Linux)
A make file has been added to the directory of code_sebastiaan, which can be used to compile the code that use Linux operating system. In the makefile, check if the dependencies (Eigen, Boost and BSO-toolbox) are linked to the locations of your local machine. 

The files can be compiled and ran by typing the following commands in the terminal:
| File name	                | Compile	     					 | Run	  			 |
| ---												|	---					 				   | ---					 |
| generateBSDs_ML.cpp	      | make clean design	     | ./bsd			   |
| generateDataset_ML.cpp	  | make clean data		     | ./dataset	   |
| Visualisation_ML.cpp	    | make clean viml	       | ./visualML	   |
| GA1and2.cpp	              | make clean ga	         | ./algo	       |
| Visualisation_GA.cpp	    | make clean viga	       | ./visualGA    |

#### Input text-files
Furthermore, the directory of code_sebastiaan contains two initial text-files: "input_BSD_ML.txt" and "cornerverticesBSD_GA.txt". These files are used as input for the two methods to predict the conformal representation of Test building 'A' and Test building 'A-O', as described in the analysis of the related MSc. Thesis.



## Example Machine Learning (ML)
The machine learning code consists of five C++ files, which are compiled separately. The filenames are listed below, and they are generally used in this order:
*	“generateBSDs_ML.cpp”
*	“generateDataset_ML.cpp”
*	“NeuralNetwork_TRAIN.cpp”
*	“NeuralNetwork_PREDICT.cpp”
*	“visualisation_ML.cpp”

See figure below for an overview of all C++ files, input and output files and the used libraries.

![image](https://user-images.githubusercontent.com/101708661/159500771-6991e3d3-a303-4eb0-bdab-93b7b959865a.png)

### "generateBSDs_ML.cpp"
The ML method starts with "generateBSDs_ML.cpp" to define a wide range of building configurations. 
The file "generateBSDs_ML.cpp" in this directory generates 100 BSDs with 2 spaces for each variant: "top", "front", "behind", "left", "right".
The width and depth range between 4000 - 8000 mm, and the height between 2000 - 6000 mm.
The number of BSDs, variant types and the range of dimensions can all be changed by the user.
The output is a textfile: “origin_dimensions_BSDs_ML.txt”, which includes the input for next C++ file (“generateDataset_ML.cpp”).

### "generateDataset_ML.cpp"
A dataset with input features (BSDs) and output targets (conformal models) can be created by "generateDataset_ML.cpp".
For each BSD, the transformation to its conformal geometry is executed by the BSO-toolbox. As a result, the input features and output targets are saved in the following text-files.

Input text-files (features):
*	“inputBSD_ML.txt”
*	“inputBSD_NumberEncoded_ML.txt”
*	“inputBSD_OneHotEncoded_ML.txt”
*	“cornerverticesBSD_ML.txt”

Output text-files (targets):
*	“outputCF_ML.txt”

For this example, the “inputBSD_ML.txt” file is used for the features, and the “outputCF_ML.txt” file is used for the targets. When the features need to be, for example One-hot encoded, the “inputBSD_OneHotEncoded_ML.txt” file is used as input.

### "NeuralNetwork_TRAIN.cpp"
The resulting text-files from previous C++ file are copied and pasted to the Visual Studio 19 project on Windows 10 OS, where all the dependencies of mlpack library are installed.
The features (“inputBSD_ML.txt”) and targets (“outputCF_ML.txt”) are used as dataset to train the Neural network. Finally, a trained ML model is saved, which then can be used to make predictions of conformal models (see “NeuralNetwork_PREDICT.cpp”). Additionally, the loss (MSE) is calculated during the training process and saved in “MSE.txt”.

### "NeuralNetwork_PREDICT.cpp"
With the trained ML model (“trained_ML_model.xml”), a test building can be used as input to predict its conformal (CF) representation (“predictionCF_ML.txt”).
Test building 'A', as used in the MSc. Thesis, is described in "test_inputBSD_ML.txt" and added to the directory.

### "visualisation_ML.cpp"
The predicted CF model of test building 'A' is visualised below. The input for the visualisation is the “predictionCF_ML.txt”-file. 
![image](https://user-images.githubusercontent.com/101708661/159496119-2ffb1bb1-bc09-47d9-8daf-b05120774279.png)


## Example Genetic Algorithm (GA)
The GA code consists of two C++ files, which are compiled separately. One for the both GAs, and one for the visualisation of the BSD and CF model.  

![image](https://user-images.githubusercontent.com/101708661/159501430-a6ce70a4-9ff6-4f2c-9e3d-e29ebef1d29e.png)


### "GA1and2.cpp"
Both GAs are structured in the same file. The simulations of GA1 and GA2 are ran in succession. 

#### Input and output files
The corner-vertices (p) of the spaces of a BSD (“cornerverticesBSD_GA.txt”) are used as input for the GA. In this example, Test building 'A-O' from the MSc. Thesis is used to make conformal by the GA.

Test building 'A-O' is described in the text-file “cornerverticesBSD_GA.txt” as follows:
*  N,	1,	10,10,0,  16,10,0,  16,16,0,  10,16,0,  10,10,3,  16,10,3,  16,16,3,  10,16,3
*  N,	2,	16,12,0,  22,12,0,  22,18,0,  16,18,0,  16,12,5,  22,12,5,  22,18,5,  16,18,5

The GA method uses meter as unit for dimensions and coordinates.

If a perfect conformal geometry is found by the GA, it is saved in “cf.txt”-file, and can be used for visualisation. Additionally, the BSD corner-vertices are saved in “bsd.txt”, and the point cloud is saved in “pnts.txt”. All can be used as input for “visualisation_GA.cpp”.

Input text-files:
*	“cornerverticesBSD_GA.txt”

Output text-files: 
*	“bsd.txt”
*	“pnts.txt”
*	“cf.txt”

#### User-defined parameters
There are parameters in both GAs that can be changed by the user. The default values for this example are listed below.

For GA1:
* initial Population (N)   = 512
* stopping criteria  (n)   = 100		(after n generations where no new unique Quad-Hexahedron is found, GA1 stops)

For GA2:
* initial Population (M)   = 8
* probability_1_min			   = 10     (minimal probability of ones in chromosome)
* probability_1_max			   = 100    (maximal probability of ones in chromosome)
* mutation rate population = 0.5		(50% of population undergoes mutation)
* mutation rate individual = 1			(nr. of bit flips in chromosome)


#### Results
Finally, Test building 'A-O' is made conformal by the Genetic Algortihm file "GA1and2.cpp". The results are listed below.

| Test building	    | generations GA1 | generations GA2 | nr. of quad-hexahedrons in CF model |
| ---								|	---					 		| ---					    | ---																	|
| 'A-O'     			  | 200             | 5			          | 6																		|


### "visualisation_GA.cpp"
The BSD, point cloud, and conformal model can be visualised. The input for the visualisation is the “bsd.txt”, “pnts.txt”, or “cf.txt” text-file.
In the figure below, one can see the generated conformal model by the GA ("cf.txt") and point cloud ("pnts.txt").
![image](https://user-images.githubusercontent.com/101708661/159507167-03b1b30b-f98a-4ce1-a9d1-28add9d59f17.png)

