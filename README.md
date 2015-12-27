This is a Computational Vision project that uses the Viola Jones algorithm to do face detection.

1. HaarDetection.cpp contains the first 2 steps of the Viola Jones Algorithm.

2. FaceDetection.cpp deals with the final part of Viola Jones.

TO COMPILE:

Type the following in order:

cmake . ( DOT included, Make sure CMake is installed on your system ) \n
make

FaceDetection then takes 1 Parameter, an image.
HaarDetection also takes 1 Parameter, an image.

Example: ./FaceDetection gma.pgm
Example: ./HaarDetection gma.pgm

Group Project by:
	Andrew Miloslavsky
	Himanshu Tanwar
	Yuliya Emelyanova
	Manpreet Singh
	Jaber Janet
	
Credits to Rainer Lienhart for their trained face cascade classifier.
