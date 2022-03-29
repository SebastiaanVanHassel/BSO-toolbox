# README: Sebastiaan van Hassel Graduation thesis 2022

This readme elaborates the software that is used for the graduation thesis of Sebastiaan van Hassel. In GitHub, a fork is made of the BSO-toolbox repository from TUe-excellent-buildings. In this fork, a new bracnch is created, called 'sebastiaan_changes', where all the necessary files are modified or added. During the graduation project, seven files of the BSO-toolbox v1.0.0 are modified and listed in this bracnch. Furthermore, the folder 'code_sebastiaan' includes all files written for the corresponding thesis. 

The MSc thesis of Sebastiaan van Hassel [1] with title: "Machine learning and Genetic Algorithms for conformal geometries in design support systems", presents research on whether Machine Learning (ML) and Genetic Algorithms (GA) can be used to obtain a conformal geometry for BSDs. To optimise both building designs and their underlying design processes, design support systems exist. For domain specific analyses, these systems benefit from a conformal (CF) representation for the Building Spatial Design (BSD). In a conformal representation, for all entities: the vertices of an entity are, if intersecting an-other entity, only allowed to coincide with this other entity's vertices. 

[1] van Hassel, S.J.F. (2022). *Machine learning and Genetic Algorithms for conformal geometries in design support systems.* (MSc thesis). Eindhoven, The Netherlands: Eindhoven University of Technology.


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
The files, “construction.cpp” and “structure.cpp”, are modified to solve error messages that occurred after the transfer to a new workstation. 
The file, “quad_hexahedron.hpp”, is modified by the author, to the purpose of his thesis. 

## C++ Code written by Sebastiaan for his Graduation thesis
The code is related to the two research methods: Machine Learning (ML) and Genetic Algorithm (GA). The code is written in C++14 and uses external libraries in some of the files. An overview of all created C++ files is listed below. 

(File name, for which research method, on what operating system, and which external libraries are included.)

| File name	                | Method	     | Operating system	  | Includes BSO-toolbox	| Includes Eigen	| Includes OpenGL	  | Includes mlpack |
| ---												|	---					 | ---								| ---			  						| ---							| ---								| ---						  |
| generateBSDs_ML.cpp	      | ML	         | Linux							|												|									|										|								  |
| generateDataset_ML.cpp	  | ML	         | Linux	            |        x	            |          x			|										|									|
| NeuralNetwork_TRAIN.cpp	  | ML	         | Windows				    |                       |                 |                   |         x				|
| NeuralNetwork_PREDICT.cpp	| ML	         | Windows				    |                       |                 |                   |         x				|
| Visualisation_ML.cpp	    | ML	         | Linux			        |                       |                 |          x				|									|
| GA1and2.cpp	              | GA	         | Linux	            |        x							|									|										|									|
| Visualisation_GA.cpp	    | GA	         | Linux			        |                       |                 |          x				|									|

The files are listed in the folder 'code_sebastiaan', which is further separated in two folders, based on their operating system: Linux or Windows.

#### Operating system
Most of the files are compiled for a Linux operating system using GCC C++ compiler version 9.4.0.
The two Neural Network files, which include the mlpack C++ library are compiled for a Windows operating system. These two files are compiled and ran via Visual Studio Community 2019 version 16.8.4 using MSVC compiler version 14.28. 

#### Makefile (Linux)
A makefile has been added to the Linux folder, which can be used to compile the code for Linux operating system. In the makefile, check if the dependencies (Eigen, Boost and BSO-toolbox) are linked to the locations of your local machine. 

The files can be compiled and ran by typing the following commands in the terminal:

| File name	                | Compile	     					 | Run	  			 |
| ---												|	---					 				   | ---					 |
| generateBSDs_ML.cpp	      | make clean design	     | ./bsd			   |
| generateDataset_ML.cpp	  | make clean data		     | ./dataset	   |
| Visualisation_ML.cpp	    | make clean viml	       | ./visualML	   |
| GA1and2.cpp	              | make clean ga	         | ./algo	       |
| Visualisation_GA.cpp	    | make clean viga	       | ./visualGA    |

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


#### Input text-files
Furthermore, the directory of code_sebastiaan contains two initial text-files: "input_BSD_ML.txt" and "cornerverticesBSD_GA.txt". These files are used as input for the two methods to predict the conformal representation of Test building 'A' and Test building 'A-O', as described in the analysis of the related MSc thesis.

| Test Building	   | Input file	    			       | Method	   |
| ---						   |	---					 				       | ---			 |
| 'A'	             | "input_BSD_ML.txt"	         | ML			   |
| 'A-0'	           | "cornerverticesBSD_GA.txt"	 | GA	       |

##### Test Building 'A'
![image](https://user-images.githubusercontent.com/101708661/160603980-30770b51-65e3-4073-8754-7701bd8795c8.png)

"test_inputBSD_ML.txt":
* 6000,6000,3000,10000,10000,0,6000,6000,5000,16000,12000,0

Corresponds to BSD:
* R, 1, 6000, 6000, 3000, 10000, 10000, 0, A
* R, 2, 6000, 6000, 5000, 16000, 12000, 0, A

##### Test Building 'A-O'
![image](https://user-images.githubusercontent.com/101708661/160610241-64051a2f-0d6e-4018-876f-46096729c39f.png)

"cornerverticesBSD_GA.txt":
* N, 1, 10,10,0, 16,10,0, 16,16,0, 10,16,0, 10,10,3, 16,10,3, 16,16,3, 10,16,3
* N, 2, 16,12,0, 22,12,0, 22,18,0, 16,18,0, 16,12,5, 22,12,5, 22,18,5, 16,18,5


## Machine Learning (ML)
The machine learning code consists of five individual C++ files. The filenames are listed below, and they are generally used in this order:
*	“generateBSDs_ML.cpp”
*	“generateDataset_ML.cpp”
*	“NeuralNetwork_TRAIN.cpp”
*	“NeuralNetwork_PREDICT.cpp”
*	“visualisation_ML.cpp”

See figure below for an overview of all C++ files, input and output text-files, used libraries, and operating system.

![image](https://user-images.githubusercontent.com/101708661/160603712-bd65a2c4-db03-4c1d-95c9-b5709ed43da3.png)


### "generateBSDs_ML.cpp"
The ML method starts with "generateBSDs_ML.cpp" to define a wide range of building configurations. 
The number of BSDs, included variant types and the range of dimensions can all be changed by the user.
The output is a textfile: “origin_dimensions_BSDs_ML.txt”, which includes the input for next C++ file (“generateDataset_ML.cpp”).

The “origin_dimensions_BSDs_ML.txt” file consists of multiple buildings. However, as example, one Building Spatial Design (BSD) can be described as follows:

* R, 1, 6000, 5000, 5000, 10000, 10000, 0, A
* R, 2, 6000, 7000, 3000, 9000, 5000, 5000, A

Which indicates: R, space ID, dimensions vector (width, depth, height), origin vector (x, y, z), A

##### Example
For the example, the file "generateBSDs_ML.cpp" generates 100 BSDs with 2 spaces for each variant: "top", "front", "behind", "left", "right".
The width and depth range between 4000 - 8000 mm, and the height ranges between 2000 - 6000 mm.

The file can be compiled by typing the following command in the terminal:
```
make clean design
```
The file can be executed by typing the following command in the terminal:
```
./bsd
```

### "generateDataset_ML.cpp"
A dataset with input features (BSDs) and output targets (conformal models) can be created by "generateDataset_ML.cpp".
For each BSD in “origin_dimensions_BSDs_ML.txt”, the transformation to its conformal geometry is executed by the BSO-toolbox. As a result, the input features and output targets are saved in the following text-files.

The input can be described in 4 different ways.
Input text-files (features):
*	“inputBSD_ML.txt”										describes the BSD by origin and dimensions vector. 
*	“inputBSD_NumberEncoded_ML.txt”			describes the BSD by origin and dimensions vector plus number encoded building types. 
*	“inputBSD_OneHotEncoded_ML.txt”     describes the BSD by origin and dimensions vector plus One-hot encoded building types. 
*	“cornerverticesBSD_ML.txt”					describes the BSD by corner-vertices of each space.

Output text-files (targets):
*	“outputCF_ML.txt”										describes the CF model by corner-vertices of each cuboid.

##### Example
For the example, the “inputBSD_ML.txt” file is used for the features, and the “outputCF_ML.txt” file is used for the targets. When the features need to be, for example One-hot encoded, the “inputBSD_OneHotEncoded_ML.txt” file is used as input.

The file can be compiled by typing the following command in the terminal:
```
make clean data
```
The file can be executed by typing the following command in the terminal:
```
./dataset
```

### "NeuralNetwork_TRAIN.cpp"
The resulting text-files from previous C++ file are copied and pasted to the Visual Studio 19 project on Windows 10 OS, where all the dependencies of mlpack library are installed.
The features (“inputBSD_ML.txt”) and targets (“outputCF_ML.txt”) are used as dataset to train the Neural network. Finally, a trained ML model is saved, which then can be used to make predictions of conformal models (see “NeuralNetwork_PREDICT.cpp”). Additionally, the loss (MSE) is calculated during the training process and saved in “MSE.txt”.

##### Example
For the example, a neural network with one hidden layer and 180 neurons is trained on “inputBSD_ML.txt” as features and “outputCF_ML.txt” as targets. The C++ files and text-files should be located in the same folder in the Visual Studio project. The trained ML model is also saved in the same folder as XML file: “trained_ML_model.xml”.

### "NeuralNetwork_PREDICT.cpp"
With the trained ML model (“trained_ML_model.xml”), a test building can be used as input to predict its conformal (CF) representation (“predictionCF_ML.txt”).

##### Example
For the example, test building 'A' is used to predict its conformal representation. Test building 'A' is described by "test_inputBSD_ML.txt", and should be placed in the same folder.


### "visualisation_ML.cpp"
The predicted CF models can be visualised by "visualisation_ML.cpp" to compare the actual conformal model and its prediction.

##### Example
The predicted CF model of test building 'A' is visualised below. The input for the visualisation is the “predictionCF_ML.txt”-file. 

The file can be compiled by typing the following command in the terminal:
```
make clean viml
```
The file can be executed by typing the following command in the terminal:
```
./visualML
```

![image](https://user-images.githubusercontent.com/101708661/159496119-2ffb1bb1-bc09-47d9-8daf-b05120774279.png)


## Genetic Algorithm (GA)
The GA code consists of two individual C++ files. One for the both GAs, and one for the visualisation of the BSD and CF model.  First, "GA1and2.cpp" is executed to run the evolutionary process and to find a conformal representation of the input BSD. Secondly, "visualisation_GA.cpp" can be executed to visualise the generated conformal model by the GA.

![image](https://user-images.githubusercontent.com/101708661/160578064-c244c549-5fe8-4060-9721-ea4b3364c358.png)

### "GA1and2.cpp"
Both GAs are structured in the same file. The simulations of GA1 and GA2 are ran in succession. 

#### Input and output files
The corner-vertices (p) of the spaces of a BSD (“cornerverticesBSD_GA.txt”) are used as input for the GA. 

If a perfect conformal geometry is found by the GA, it is saved in “cf.txt”-file, and can be used for visualisation. Additionally, the BSD corner-vertices are saved in “bsd.txt”, and the point cloud is saved in “pnts.txt”. All can be used as input for “visualisation_GA.cpp”.

Input text-files:
*	“cornerverticesBSD_GA.txt”

Output text-files: 
*	“bsd.txt”
*	“pnts.txt”
*	“cf.txt”

#### User-defined parameters
Parameters exist in both GAs that can be changed by the user. The default values for following example are listed below.

For GA1:
* initial Population (N)   = 512
* stopping criteria  (n)   = 100		(after n generations where no new unique Quad-Hexahedron is found, GA1 stops)

For GA2:
* initial Population (M)   = 8
* probability_1_min			   = 10     (minimal probability of ones in chromosome)
* probability_1_max			   = 100    (maximal probability of ones in chromosome)
* mutation rate population = 0.5		(50% of population undergoes mutation)
* mutation rate individual = 1			(nr. of bit flips in chromosome)


##### Example
In the example, Test building 'A-O' from the MSc thesis is used to make conformal by the GA.

Test building 'A-O' is described in the text-file “cornerverticesBSD_GA.txt” as follows:
*  N,	1,	10,10,0,  16,10,0,  16,16,0,  10,16,0,  10,10,3,  16,10,3,  16,16,3,  10,16,3
*  N,	2,	16,12,0,  22,12,0,  22,18,0,  16,18,0,  16,12,5,  22,12,5,  22,18,5,  16,18,5

In this example, the dimensions and coordinates of the test building are indicated in meters.

The file can be compiled by typing the following command in the terminal:
```
make clean ga
```
The file can be executed by typing the following command in the terminal:
```
./algo
```

Finally, Test building 'A-O' is made conformal by the Genetic Algortihm file "GA1and2.cpp". The results are listed below.

| Test building	    | generations GA1 | generations GA2 | nr. of quad-hexahedrons in CF model |
| ---								|	---					 		| ---					    | ---																	|
| 'A-O'     			  | 200             | 5			          | 6																		|


### "visualisation_GA.cpp"
The BSD, point cloud, and conformal model can be visualised. The input for the visualisation is the “bsd.txt”, “pnts.txt”, or “cf.txt” text-file.

##### Example
The conformal model of Test Building 'A-O' is shown in the figure below. One can see the generated conformal model by the GA ("cf.txt") and point cloud ("pnts.txt").

The file can be compiled by typing the following command in the terminal:
```
make clean viga
```
The file can be executed by typing the following command in the terminal:
```
./visualGA
```

![image](https://user-images.githubusercontent.com/101708661/159507167-03b1b30b-f98a-4ce1-a9d1-28add9d59f17.png)

