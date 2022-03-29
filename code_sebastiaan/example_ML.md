## Example Machine Learning (ML)

In this example, Test Building 'A' from the corresponding Msc thesis, will be made conformal by a trained Machine Learning model. Therefore, first a dataset needs to be created with the files: "generateBSDs_ML.cpp" and "generateDataset_ML.cpp". Secondly, a ML model is trained using the created dataset and the file: "NeuralNetwork_TRAIN.cpp” and saved afterwards to make predictions with "NeuralNetwork_PREDICT.cpp”. Finally, a prediction of the conformal model can be visualised using "visualisation_ML.cpp".

### Test Building 'A'
![image](https://user-images.githubusercontent.com/101708661/160603980-30770b51-65e3-4073-8754-7701bd8795c8.png)

"test_inputBSD_ML.txt":
* 6000,6000,3000,10000,10000,0,6000,6000,5000,16000,12000,0

Corresponds to BSD:
* R, 1, 6000, 6000, 3000, 10000, 10000, 0, A
* R, 2, 6000, 6000, 5000, 16000, 12000, 0, A


### Files
The files “generateBSDs_ML.cpp”, “generateDataset_ML.cpp”, “visualisation_ML.cpp”, and "makefile" should be downloaded from the GitHub branch 'sebastiaan_changes', directory BSO-toolbox/code_sebastiaan/Linux/ and placed in the one folder. The same for “NeuralNetwork_TRAIN.cpp”, “NeuralNetwork_PREDICT.cpp”, and "test_inputBSD_ML.txt", but now from directory BSO-toolbox/code_sebastiaan/Windows/.  

C++ files:
* “generateBSDs_ML.cpp”
* “generateDataset_ML.cpp”
* “NeuralNetwork_TRAIN.cpp”
* “NeuralNetwork_PREDICT.cpp”
* “visualisation_ML.cpp”

Input Textfile:
* "test_inputBSD_ML.txt"

Makefile:
* "makefile"

### Execution
Figure below gives an overview of all files and the steps that need to be taken.

![image](https://user-images.githubusercontent.com/101708661/160605930-d4dd6116-e2ab-47d8-bcd3-f99bead21003.png)

Part of the files are compiled for a Linux operating system. These files use the "makefile" to compile and execute. 
The neural network files are compiled and executed for Windows OS in Visual Studio 2019.

#### "generateBSDs_ML.cpp"
The ML method starts with "generateBSDs_ML.cpp" to define a wide range of building configurations. The file generates 100 BSDs with 2 spaces for each variant: "top", "front", "behind", "left", "right". The width and depth range between 4000 - 8000 mm, and the height ranges between 2000 - 6000 mm.

The file can be compiled by typing the following command in the terminal:
```
make clean design
```
The file can be executed by typing the following command in the terminal:
```
./bsd
```

The ouput consists of 500 BSDs and is listed in text-file: “origin_dimensions_BSDs_ML.txt”. This text-file is used as input for next C++ file (“generateDataset_ML.cpp”).

#### “generateDataset_ML.cpp”



