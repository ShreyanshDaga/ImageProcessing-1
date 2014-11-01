//////////////////////////////////////////////////
//EE 569 Homework #1
//
//Date:			September 22, 2013
//Name:		Shreyansh Dnyanesh Daga
//ID:				6375-3348-33	
//Email:		sdaga@usc.edu
//Compiled and build on Visual Studio 2012
//OS: Windows 8
//////////////////////////////////////////////////


#ifndef HomeWork_H
	#define HomeWork_H

	#include <Windows.h>
	#include"Image.h"

	void Problem_1_A();
	void Problem_1_B();
	void Problem_1_C();
	void Problem_1_D();
	void Problem_2_A_a();
	void Problem_2_A_b();
	void Problem_2_B_a();
	void Problem_2_B_b();
	void Problem_2_C();
	void Problem_3_A();
	void Problem_3_B();
	void Problem_3_C();
	void Problem_3_D();
	void PlotHistogram(Image imImage);
	void WriteHistogramFile(Image imImage, int iHistCount[256], unsigned char **pcHistData,char cColor);
#endif