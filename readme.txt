IDE Used: Visual Studio 2012 Professional
OS: Widows 8/ Windows 7
Language: C++

The source code contains the following files

*Headers Files:
Homework.h		--COntains prototype of genera fucntions used
Pixel.h			--Contains decln of Pixel class	
Image.h			--Contains decln of Image class
Histogram.h		--Contains decln of Histogram class

*Source Files:
Source.cpp		--Contains the main() and the start point for the program
Pixel.cpp		--Contains class functions
Image.cpp		--Contains class functions
Histogram.cpp		--Contains class functions
ImageManipulation.cpp	--Contains functions for Problem 1
ImageEnhancement.cpp	--COntains functions for Prolem 2
NoiseRemoval.cpp	--Contains functions for Problem 3


*All files are required to compile the program

*Output will be in the form of a console window with a main menu 

*Steps to compile in Visual Studio
  Build Menu -> Build Solution		(F6)

*Steps to run in Visual Studio
  Debug Menu -> Start without debugging (CTRL + F5)


*Running the program

1) Few Functions will ask the user to input image file info again, please consider. Unable to modify completely due to deadline constrains.
2) All the images should be in the root folder of the executable

for ex

HW1
|->(All the cpp files)
|->(All the header files)
|->(All the image files)

Also the output image files will be generated in the root directorty itself.
Some functions may require user to input the image info of few output images as well, again same reason please consider.

The Problems which i was unable to solve have empty functions

The naming convention used is a modified hungarian notation i have developed for myself

eg,

Pixel pxP;
Image imOcean, imBarara[i];
int iRows, iCols;

The small case letters in each variable name point to the type of the variable, this should make it easy to read the code as i have had very little time to comments
again please consider.


RAM might become full for some functions esp Problem 2A, and 2B
so i would kindly request you to run the program again an directly jump to the Problem from the menu
