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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

#include"HomeWork.h"
#include"Pixel.h"
#include"Histogram.h"
#include"Image.h"

using namespace std;

void Problem_3_A()
{
	Image imPeperMix;
	Image imPeperClean;

	string szImageName("peppers_mix.raw");
	string szImageName_1("peppers_clean.raw");

	int **pcWindow;
	int *pcSeq;

	int iRows = 256;
	int iCols = 256;
	int iColorFormat = 3;
	int iWinSize;
	int iThresh;

	imPeperMix.SetImageName(szImageName);
	imPeperMix.SetImageRows(iRows);
	imPeperMix.SetImageCols(iCols);
	imPeperMix.SetImageColorFormat(iColorFormat);
	imPeperMix.iPixelCount = iRows*iCols;
	imPeperMix.AllocImageMem();

	imPeperMix.ReadImageData();
	imPeperMix.PlotHistogram();

	imPeperClean.SetImageName(szImageName_1);
	imPeperClean.SetImageRows(iRows);
	imPeperClean.SetImageCols(iCols);
	imPeperClean.SetImageColorFormat(iColorFormat);
	imPeperClean.iPixelCount = iRows*iCols;
	imPeperClean.AllocImageMem();

	cout<<"\n Enter Window Size: ";
	cin>>iWinSize;
	cout<<"Enter Threshold for Avg Filter: ";
	cin>>iThresh;

	//imPeperMix.ImageExtend((iWinSize-1)/2);

	pcWindow = new int*[iWinSize];
	pcSeq = new int[iWinSize*iWinSize];
	for(int i = 0;i<iWinSize ;i++)
	{
		pcWindow[i] = new int[iWinSize];
	}

	imPeperMix.ImageExtend((iWinSize-1)/2);
	imPeperMix.WriteImageData();

	int R,G,B;	
	for(int i = 1;i<iRows-1;i++)
	{
		for(int j = 1;j<iCols-1;j++)
		{
			pcWindow[0][0] = imPeperMix.GetPixel(i-1,j-1)->GetRed();
			pcWindow[0][1] = imPeperMix.GetPixel(i-1,j)->GetRed();
			pcWindow[0][2] = imPeperMix.GetPixel(i-1,j+1)->GetRed();

			pcWindow[1][0] = imPeperMix.GetPixel(i,j-1)->GetRed();
			pcWindow[1][1] = imPeperMix.GetPixel(i,j)->GetRed();
			pcWindow[1][2] = imPeperMix.GetPixel(i,j+1)->GetRed();

			pcWindow[2][0] = imPeperMix.GetPixel(i+1,j-1)->GetRed();
			pcWindow[2][1] = imPeperMix.GetPixel(i+1,j)->GetRed();
			pcWindow[2][2] = imPeperMix.GetPixel(i+1,j-1)->GetRed();

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					pcSeq[l*3+m] = pcWindow[l][m];
				}
			}

			for(int l = 0;l<9;l++)
			{
				for(int m = 0;m<9-1;m++)
				{
					int iTemp;

					if(pcSeq[m] > pcSeq[m+1])
					{
						iTemp = pcSeq[m];
						pcSeq[m] = pcSeq[m+1];
						pcSeq[m+1] = iTemp;
					}
				}
			}

			R = pcSeq[4];

			/*int iAvg = 0;

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					if(l == 1 && m == 1)
						continue;
					iAvg += pcWindow[l][m];
				}
			}

			iAvg/=8;

			if(abs(pcWindow[i][j] - iAvg) > iThresh)
			{
				R = iAvg;
			}
			else
				R = pcWindow[i][j];*/

			//Green
			pcWindow[0][0] = imPeperMix.GetPixel(i-1,j-1)->GetGreen();
			pcWindow[0][1] = imPeperMix.GetPixel(i-1,j)->GetGreen();
			pcWindow[0][2] = imPeperMix.GetPixel(i-1,j+1)->GetGreen();

			pcWindow[1][0] = imPeperMix.GetPixel(i,j-1)->GetGreen();
			pcWindow[1][1] = imPeperMix.GetPixel(i,j)->GetGreen();
			pcWindow[1][2] = imPeperMix.GetPixel(i,j+1)->GetGreen();

			pcWindow[2][0] = imPeperMix.GetPixel(i+1,j-1)->GetGreen();
			pcWindow[2][1] = imPeperMix.GetPixel(i+1,j)->GetGreen();
			pcWindow[2][2] = imPeperMix.GetPixel(i+1,j-1)->GetGreen();

			/*iAvg = 0;

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					if(l == 1 && m == 1)
						continue;
					iAvg += pcWindow[l][m];
				}
			}

			iAvg/=8;

			if(abs(pcWindow[i][j] - iAvg) > iThresh)
			{
				G = iAvg;
			}
			else
				G = pcWindow[i][j];*/

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					pcSeq[l*3+m] = pcWindow[l][m];
				}
			}

			for(int l = 0;l<9;l++)
			{
				for(int m = 0;m<9-1;m++)
				{
					int iTemp;

					if(pcSeq[m] > pcSeq[m+1])
					{
						iTemp = pcSeq[m];
						pcSeq[m] = pcSeq[m+1];
						pcSeq[m+1] = iTemp;
					}
				}
			}

			G = pcSeq[4];


			//Blue
			pcWindow[0][0] = imPeperMix.GetPixel(i-1,j-1)->GetBlue();
			pcWindow[0][1] = imPeperMix.GetPixel(i-1,j)->GetBlue();
			pcWindow[0][2] = imPeperMix.GetPixel(i-1,j+1)->GetBlue();

			pcWindow[1][0] = imPeperMix.GetPixel(i,j-1)->GetBlue();
			pcWindow[1][1] = imPeperMix.GetPixel(i,j)->GetBlue();
			pcWindow[1][2] = imPeperMix.GetPixel(i,j+1)->GetBlue();

			pcWindow[2][0] = imPeperMix.GetPixel(i+1,j-1)->GetBlue();
			pcWindow[2][1] = imPeperMix.GetPixel(i+1,j)->GetBlue();
			pcWindow[2][2] = imPeperMix.GetPixel(i+1,j-1)->GetBlue();

		    /*iAvg = 0;

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					if(l == 1 && m == 1)
						continue;
					iAvg += pcWindow[l][m];
				}
			}

			iAvg/=8;

			if(abs(pcWindow[i][j] - iAvg) > iThresh)
			{
				B = iAvg;
			}
			else
				B = pcWindow[i][j];*/

			for(int l = 0;l<3;l++)
			{
				for(int m = 0;m<3;m++)
				{
					pcSeq[l*3+m] = pcWindow[l][m];
				}
			}

			for(int l = 0;l<9;l++)
			{
				for(int m = 0;m<9-1;m++)
				{
					int iTemp;

					if(pcSeq[m] > pcSeq[m+1])
					{
						iTemp = pcSeq[m];
						pcSeq[m] = pcSeq[m+1];
						pcSeq[m+1] = iTemp;
					}
				}
			}

			B = pcSeq[4];

			Pixel pxP(R,G,B);
			imPeperClean.SetPixel(i,j,pxP);
		}
	}

	//imPeperClean.ImageExtend(1);
	imPeperClean.WriteImageData();
	imPeperClean.PlotHistogram();
}

void Problem_3_B()
{
	cout<<"\nUable to complete Homework on time :(";
	cout<<"\nPress 'C' to continue!";
	getch();
}

void Problem_3_C()
{
	cout<<"\nUable to complete Homework on time :(";
	cout<<"\nPress 'C' to continue!";
	getch();
}
