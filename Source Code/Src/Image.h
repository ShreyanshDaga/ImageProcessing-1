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

#ifndef IMAGE_H
#define IMAGE_H

#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>

#include"Pixel.h"
#include"Histogram.h"

using namespace std;

class Image
{
	public:
		unsigned char **pImageDate;		
		int iPixelCount;

	private:
		
		int iRows;
		int iCols;
		int iColorFormat;
		string szImageName;		

	public:
		Histogram hHist;

		Image();
		~Image();
		Image(unsigned char **ImageData,int Rows, int Cols, int ColorFormat, string ImageName);		
		string GetImageName();		
		int GetImageRows();
		int GetImageCols();
		int GetImageColorFormat();
		void SetImageRows(int iRows);
		void SetImageCols(int iCols);
		void SetImageColorFormat(int iColorFormat);
		void SetImageName(string szName);
		void SetPixel(int X,int Y, Pixel pxP);
		void DrawLine(int X1, int Y1, int X2, int Y2, Pixel pxP);
		Pixel* GetPixel(int X, int Y);
		Pixel* GetNBPixel(Pixel pxP, int idX, int idY);
		void ReadImageInfo();
		void WriteImageData();
		void ReadImageData();
		void AllocImageMem();
		void PlotHistogram();
		void PlotCumHistogram();
		void FreeResources();
		void ImageExtend(int iSize);
};

#endif