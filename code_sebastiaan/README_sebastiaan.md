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
The code consists of two individual parts with respect to the research methods: Machine Learning (ML) and Genetic Algorithm (GA). The code is written in C++14 and uses external libraries in some of the files. An overview of all created C++ files is listed below. (File name, for which research method, on what operating system, and which external libraries are included.)

| File name	                | Method	     | Operating system	  | Includes BSO-toolbox	| Includes Eigen	| Includes OpenGL	  | Includes mlpack |
| ---												|	---					 | ---								| ---			  						| ---							| ---								| ---						  |
| generateBSDs_ML.cpp	      | ML	         | Linux							|												|									|										|								  |
| generateDataset_ML.cpp	  | ML	         | Linux	            |        x	            |          x			|										|									|
| NeuralNetwork_TRAIN.cpp	  | ML	         | Windows				    |                       |                 |                   |         x				|
| NeuralNetwork_PREDICT.cpp	| ML	         | Windows				    |                       |                 |                   |         x				|
| Visualisation_ML.cpp	    | ML	         | Linux			        |                       |                 |          x				|									|
| GA1and2.cpp	              | GA	         | Linux	            |        x							|									|										|									|
| Visualisation_GA.cpp	    | GA	         | Linux			        |                       |                 |          x				|									|

Most of the files make use of a Linux operating system. These files are compiled on a server at the University. The two Neural Network files, which include the mlpack C++ library make use of a Windows operating system. The mlpack library is not installed on the server of the University and therefore, installed and used on the personal computer (Windows OS) of the author.

Overview of external software:
*	BSO-toolbox developed at Eindhoven University of Technology
	-	See https://github.com/TUe-excellent-buildings/BSO-toolbox for documentation and installa-tion guide.
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

A make file has been added to the directory of code_sebastiaan, which can be used to compile the code that use Linux OS. In the makefile, check if the dependencies (Eigen, Boost and BSO-toolbox) are linked to the locations of your local machine. 

The files can be compiled and ran by typing the following commands in the terminal:
| File name	                | Compile	     					 | Run	  			 |
| ---												|	---					 				   | ---					 |
| generateBSDs_ML.cpp	      | make clean design	     | ./bsd			   |
| generateDataset_ML.cpp	  | make clean data		     | ./dataset	   |
| Visualisation_ML.cpp	    | make clean viml	       | ./visualML	   |
| GA1and2.cpp	              | make clean ga	         | ./algo	       |
| Visualisation_GA.cpp	    | make clean viga	       | ./visualGA    |

## Example Machine Learning (ML)
The machine learning code consists of five C++ files, which are compiled separately. The filenames are listed below, and they are generally used in this order:
*	“generateBSDs_ML.cpp”
*	“generateDataset_ML.cpp”
*	“NeuralNetwork_TRAIN.cpp”
*	“NeuralNetwork_PREDICT.cpp”
*	“visualisation_ML.cpp”
See figure below for an overview of all C++ files, input and output files and the used libraries.
![image](https://user-images.githubusercontent.com/101708661/159466691-23ec21e9-b8b7-4536-b24f-6b1134e3f5c7.png)

#### "generateBSDs_ML.cpp"
The ML method starts with "generateBSDs_ML.cpp" to define a wide range of building configurations. 
The file "generateBSDs_ML.cpp" in this directory generates 100 BSDs with 2 spaces for each variant: "top", "front", "behind", "left", "right".
The width and depth range from 4000 - 8000 mm, and the height from 2000 - 6000 mm.
The output is a textfile: “origin_dimensions_BSDs_ML.txt”, which includes the input for next C++ file (“generateDataset_ML.cpp”).

#### "generateDataset_ML.cpp"
A dataset with input features (BSDs) and output targets (conformal models) can be created by "generateDataset_ML.cpp".
For each BSD, the transformation to its conformal geometry is executed by the BSO-toolbox. As a result, the input features and output targets are saved.

Input text-files (features):
*	“inputBSD.txt”
*	“inputBSD_NumberEncoded.txt”
*	“inputBSD_OneHotEncoded.txt”
*	“cornerverticesBSD_ML.txt”

Output text-files (targets):
*	“outputCF.txt”

#### "NeuralNetwork_TRAIN.cpp"
The features (“inputBSD.txt”) and targets (“outputCF.txt”) are used as dataset to train the Neural network. Finally, a trained ML model is saved, which then can be used to make predictions of conformal models (see “NeuralNetwork_PREDICT.cpp”). Additionally, the loss (MSE) is calculated during the training process and saved in “mse.txt”.

#### "NeuralNetwork_PREDICT.cpp"
With the trained ML model (“trained_ML_model.xml”), a test building can be used as input to predict its conformal (CF) representation (“predictionCF.txt”).
A test building ("test_inputBSD.txt") is added to the directory.

#### "visualisation_ML.cpp"
The predicted CF model can be visualised. The input for the visualisation is the “predictionCF.txt”-file. 

