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
#include<string.h>
#include<iostream>

#include"Image.h"
#include"HomeWork.h"
#include"Histogram.h"


using namespace std;

void Problem_2_A_a()
{
	Image imBarbara[3];
	Image imResult_1[3];
	string szImageNames[] = {"barbara_dark.raw","barbara_mid.raw","barbara_bright.raw"};
	string szImageNames_1[] = {"barbara_dark_1.raw","barbara_mid_1.raw","barbara_bright_1.raw"};
	
	int iRows = 512, iCols = 512;
	int iColorFormat = 1;
	int iaFmin[3];
	int iaFmax[3];
	int iaGmin[3] = {0, 0, 0};
	int iaGmax[3] = {255, 255, 255};

	system("cls");
	cout<<"Q2(a) Histogram Equalization for Grayscale Images\Linear Histogram Method\n";
	
	//Take image info
	for(int i = 0;i<3;i++)
	{
		imBarbara[i].SetImageName(szImageNames[i]);
		imBarbara[i].SetImageRows(iRows);
		imBarbara[i].SetImageCols(iCols);
		imBarbara[i].SetImageColorFormat(iColorFormat);
		imBarbara[i].iPixelCount = iRows*iCols;
		imBarbara[i].AllocImageMem();

		imBarbara[i].ReadImageData();
		imBarbara[i].PlotHistogram();
		//imBarbara[i].hHist.FreeHistogram();
	}

	for(int i = 0;i<3;i++)
	{
		imResult_1[i].SetImageName(szImageNames_1[i]);
		imResult_1[i].SetImageRows(iRows);
		imResult_1[i].SetImageCols(iCols);
		imResult_1[i].SetImageColorFormat(iColorFormat);
		imResult_1[i].iPixelCount = iRows*iCols;
		imResult_1[i].AllocImageMem();
	}

	Pixel pxP;
	Pixel *ppxP;
	int iBW = 0;

	for(int i = 0;i<3;i++)
	{
		cout<<"\nFor Image_"<<i+1<<" from Histogram";
		cout<<"\nEnter Fmin: ";
		cin>>iaFmin[i];
		cout<<"Enter Fmax: ";
		cin>>iaFmax[i];

		for(int k = 0;k<512;k++)
		{
			for(int j = 0;j<512;j++)
			{				
				ppxP = imBarbara[i].GetPixel(k,j);
				pxP.iBW = (iaGmin[i] + ((iaGmax[i] - iaGmin[i])*(ppxP->GetBW() - iaFmin[i]))/(iaFmax[i] - iaFmin[i]));
				imResult_1[i].SetPixel(k,j,pxP);		
				delete ppxP;
			}
		}

		imResult_1[i].WriteImageData();
		imResult_1[i].PlotHistogram();
		//imResult_1[i].hHist.FreeHistogram();
	}	

	Image imTransferFunction[3];
	string szTransferFuncName[3]  = {"Trans_Lin_Dark.raw","Trans_Lin_Mid.raw","Trans_Lin_Bright.raw"};
	iRows =  256;
	iCols = 256;
	iColorFormat = 1;
	Pixel pxP1(255);

	for(int i = 0;i<3;i++)
	{
		imTransferFunction[i].SetImageName(szTransferFuncName[i]);
		imTransferFunction[i].SetImageRows(iRows);
		imTransferFunction[i].SetImageCols(iCols);
		imTransferFunction[i].SetImageColorFormat(iColorFormat);
		imTransferFunction[i].AllocImageMem();
	}

	int iGx,iGy;

	for(int i = 0;i<3;i++)
	{
		//Fill White
		pxP1.iBW = 255;
		for(int j = 0;j<iRows;j++)
		{
			for(int k = 0;k<iCols;k++)
			{
				imTransferFunction[i].SetPixel(j,k,pxP1);
			}
		}

		pxP1.iBW = 50;
		
		imTransferFunction[i].DrawLine(iRows - 1,0,iRows - 1,iaFmin[i],pxP1);
		imTransferFunction[i].DrawLine(iRows-1,iaFmin[i],0,iaFmax[i],pxP1);
		imTransferFunction[i].DrawLine(0,iaFmax[i],0,iCols,pxP1);

		imTransferFunction[i].WriteImageData();
	}

	for(int i = 0;i<3;i++)
	{
		//imBarbara[i].FreeResources();
		//imResult_1[i].FreeResources();
		//imTransferFunction[i].FreeResources();
	}

	cout<<"\nPress 'C' to continue to Cumulative Histogram method";
	getch();
}

void Problem_2_A_b()
{
	Image imBarbara[3];
	Image imResult_2[3];
	string szImageNames[] = {"barbara_dark.raw","barbara_mid.raw","barbara_bright.raw"};
	string szImageNames_2[] = {"barbara_dark_2.raw","barbara_mid_2.raw","barbara_bright_2.raw"};

	int iRows = 512, iCols = 512;
	int iColorFormat = 1;
	int iaFmin[3];
	int iaFmax[3];
	int iaGmin[3] = {0, 0, 0};
	int iaGmax[3] = {255, 255, 255};

	system("cls");
	cout<<"Q2(a) Histogram Equalization for Grayscale Images:\nCumulative Histogram Method\n";

	for(int i = 0;i<3;i++)
	{
		imBarbara[i].SetImageName(szImageNames[i]);
		imBarbara[i].SetImageRows(iRows);
		imBarbara[i].SetImageCols(iCols);
		imBarbara[i].SetImageColorFormat(iColorFormat);
		imBarbara[i].iPixelCount = iRows*iCols;
		imBarbara[i].AllocImageMem();

		imBarbara[i].ReadImageData();
		imBarbara[i].PlotHistogram();
	}

	for(int i = 0;i<3;i++)
	{
		imResult_2[i].SetImageName(szImageNames_2[i]);
		imResult_2[i].SetImageRows(iRows);
		imResult_2[i].SetImageCols(iCols);
		imResult_2[i].SetImageColorFormat(iColorFormat);
		imResult_2[i].iPixelCount = iRows*iCols;
		imResult_2[i].AllocImageMem();
	}

	//Cumulative Histogram	
	Pixel pxP;

	for(int i = 0;i<3;i++)
	{
		imBarbara[i].PlotCumHistogram();	
		for(int j = 0;j<iRows;j++)
		{
			for(int k = 0;k<iCols;k++)
			{
				pxP.iBW = ((imBarbara[i].hHist.iCumHistogramBW[imBarbara[i].GetPixel(j,k)->GetBW()])*255)/imBarbara[i].iPixelCount;

				if(pxP.GetBW() >= 255)
				{
					pxP.iBW = 255;
					imResult_2[i].SetPixel(j,k,pxP);
				}
				else
					imResult_2[i].SetPixel(j,k,pxP);
			}
		}

		imResult_2[i].WriteImageData();
		imResult_2[i].PlotHistogram();
	}

	cout<<"\nPress 'C' to continue";
	getch();
}

void Problem_2_B_a()
{
	Image imOcean;
	Image imResult_1;

	string szImageName("ocean_contrast.raw");
	string szImageName_1("ocean_clean.raw");

	int iRows = 332, iCols = 500;
	int iColorFormat = 3;

	imOcean.SetImageName(szImageName);
	imOcean.SetImageRows(iRows);
	imOcean.SetImageCols(iCols);
	imOcean.SetImageColorFormat(iColorFormat);
	imOcean.iPixelCount = iRows*iCols;
	imOcean.AllocImageMem();

	imOcean.ReadImageData();
	imOcean.PlotHistogram();

	imResult_1.SetImageName(szImageName_1);
	imResult_1.SetImageRows(iRows);
	imResult_1.SetImageCols(iCols);
	imResult_1.SetImageColorFormat(iColorFormat);
	imResult_1.iPixelCount = iRows*iCols;
	imResult_1.AllocImageMem();	

	Pixel pxP;

	//Plot Transfer function of each channel
	imOcean.PlotCumHistogram();	
	
	//HE 
	for(int j = 0;j<iRows;j++)
	{
		for(int k = 0;k<iCols;k++)
		{
			pxP.iR = ((imOcean.hHist.iCumHistogramR[imOcean.GetPixel(j,k)->GetRed()])*255)/imOcean.iPixelCount;
			pxP.iG = ((imOcean.hHist.iCumHistogramG[imOcean.GetPixel(j,k)->GetGreen()])*255)/imOcean.iPixelCount;
			pxP.iB = ((imOcean.hHist.iCumHistogramB[imOcean.GetPixel(j,k)->GetBlue()])*255)/imOcean.iPixelCount;

			if(pxP.GetRed() >= 255)
			{
				pxP.iR = 255;					
			}
			
			if(pxP.GetBlue() >= 255)
			{
				pxP.iB = 255;					
			}
			if(pxP.GetGreen() >= 255)
			{
				pxP.iG = 255;					
			}
				
			imResult_1.SetPixel(j,k,pxP);					
		}		
	}

	imResult_1.WriteImageData();
	imResult_1.PlotHistogram();
	cout<<"\nPress 'C' to continue to Digital IMplementation of Equalized HIstogram";
	getch();
}

void Problem_2_B_b()
{
	cout<<"\nUable to complete Homework on time :(";
	cout<<"\nPress 'C' to continue!";
	getch();
}

/*void Problem_2_B_b()
{
	Image imOcean;
	Image imResult_1;

	string szImageName("ocean_contrast.raw");
	string szImageName_1("ocean_clean.raw");

	int iRows = 332, iCols = 500;
	int iColorFormat = 3;
	int iPixelCount = iRows*iCols;

	int **iaLoc = new int*[iRows];
	
	for(int i = 0;i<iRows;i++)
	{
		iaLoc[i] = new int[iCols*iColorFormat];
	}

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols*iColorFormat;j++)
		{
			iaLoc[i][j] = 0;
		}
	}
	
	//Read Input Image
	imOcean.SetImageName(szImageName);
	imOcean.SetImageRows(iRows);
	imOcean.SetImageCols(iCols);
	imOcean.SetImageColorFormat(iColorFormat);
	imOcean.iPixelCount = iRows*iCols;
	imOcean.AllocImageMem();
	imOcean.ReadImageData();
	imOcean.PlotHistogram();

	imResult_1.SetImageName(szImageName_1);
	imResult_1.SetImageRows(iRows);
	imResult_1.SetImageCols(iCols);
	imResult_1.SetImageColorFormat(iColorFormat);
	imResult_1.iPixelCount = iRows*iCols;
	imResult_1.AllocImageMem();

	for(int k = 0; k < iColorFormat; k++)
	{
		unsigned char cColor = 0 ,cGColor = 0;
		int iFCount = 0;	//Input Intensity Count
		int iGCount = 0;	//Intensity count
					
		while(cColor < 255)
		{
			for(int i = 0; i<iRows; i++)
			{
				for(int j = 0; j<iCols*iColorFormat;j+=3)
				{
					if(imOcean.pImageDate[i][j + k] == cColor)
					{
						iGCount++;
					}
				}
			}
		
			//While Target Intensity Count is not 0
			while(iGCount > 0)
			{				
				for(int i = 0; i < iRows; i++)
				{
					for(int j = 0; j < iCols*iColorFormat;j+=3)
					{
						if(imOcean.pImageDate[i][j + k] == cColor)
						{
							if(iaLoc[i][j + k] == 0)
							{
								imResult_1.pImageDate[i][j + k] = cGColor;
								iFCount++;
								iGCount--;
								iaLoc[i][j + k] = 1;	//Location is recovered
							}
						}

						if((iFCount >= ((iRows * iCols)/255)) || (iGCount <= 0))
							break;												
					}

					if((iFCount >= ((iRows * iCols)/255))  || (iGCount <= 0))
						break;
				}

				//Move to next target intensity
				if((iFCount >= ((iRows * iCols)/255)))
				{
					cGColor++;
					iFCount = 0;
				}			
			}	

			cColor++;
			iGCount = 0;
		}
	}

	imResult_1.WriteImageData();
	imResult_1.PlotHistogram();
}*/

/*
void Problem_2_B_()
{
	Image imOcean;
	Image imResult_1;

	string szImageName("ocean_contrast.raw");
	string szImageName_1("ocean_clean.raw");

	int iRows = 332, iCols = 500;
	int iColorFormat = 3;
	int iPixelCount = iRows*iCols;

	//Create Bins for all the values
	int iPixelPerBin = (iRows*iCols)/256;

	Pixel **paPix = new Pixel*[256];
	Pixel *paPixArr = new Pixel[iRows*iCols];
	
	unsigned char **pcR = new unsigned char*[256];
	unsigned char **pcG = new unsigned char*[256];
	unsigned char **pcB = new unsigned char*[256];

	Pixel *pxP;

	//Read Input Image
	imOcean.SetImageName(szImageName);
	imOcean.SetImageRows(iRows);
	imOcean.SetImageCols(iCols);
	imOcean.SetImageColorFormat(iColorFormat);
	imOcean.iPixelCount = iRows*iCols;
	imOcean.AllocImageMem();
	imOcean.ReadImageData();
	imOcean.PlotHistogram();

	imResult_1.SetImageName(szImageName_1);
	imResult_1.SetImageRows(iRows);
	imResult_1.SetImageCols(iCols);
	imResult_1.SetImageColorFormat(iColorFormat);
	imResult_1.iPixelCount = iRows*iCols;
	imResult_1.AllocImageMem();

	int iaCountR[256] = {0};
	int iaCountG[256] = {0};
	int iaCountB[256] = {0};

	//Get count of each intensity of each color
	/*for(int c = 0;c<256;c++)
	{
		for(int i = 0;i<iRows;i++)
		{
			for(int j = 0;j<iCols;j++)
			{
				if(imOcean.GetPixel(i,j)->GetRed() == c)
					iaCountR[c]++;
				if(imOcean.GetPixel(i,j)->GetGreen() == c)
					iaCountG[c]++;
				if(imOcean.GetPixel(i,j)->GetBlue() == c)
					iaCountB[c]++;
			}
		}
	}///

	imOcean.PlotHistogram();
	unsigned char R,G,B;
	Pixel *pP;

	for(int c = 0;c<256;c++)
	{
		//paPix[c] = new Pixel[iaCountR[c]];
		//Ascending order		
		pcR[c] = new unsigned char[imOcean.hHist.iHistogramR[c]];
		pcG[c] = new unsigned char[imOcean.hHist.iHistogramG[c]];
		pcB[c] = new unsigned char[imOcean.hHist.iHistogramB[c]];

		for(int j = 0;j<iRows;j++)
		{
			for(int k = 0;k<iCols;k++)
			{
				pP = imOcean.GetPixel(j,k);
				
				R = pP->GetRed();
				G = pP->GetGreen();
				B = pP->GetBlue();

				//Red			
				for(int i = 0;i<imOcean.hHist.iHistogramR[c];i++)
				{
					if(R == c)
					{						
						pcR[c][i] = c;
					}
				}

				//Green
				for(int i = 0;i<imOcean.hHist.iHistogramG[c];i++)
				{
					if(G == c)
					{						
						pcG[c][i] = c;
					}
				}

				//Blue
				for(int i = 0;i<imOcean.hHist.iHistogramB[c];i++)
				{
					if(B == c)
					{					
						pcB[c][i] = c;
					}
				}

				delete pP;
			}
		}			

		paPix[c] = new Pixel[iRows*iCols/256];

		//Spread Uniform
		for(int i = 0;i<iRows*iCols/256;i++)
		{
			paPix[c][i].iR = pcR[c][i];		//R
			paPix[c][i].iG = pcG[c][i];		//G
			paPix[c][i].iB = pcB[c][i];		//B;		
		}
	}

	
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			imResult_1.SetPixel(i,j,paPix[i][j]);
		}
	}

	imResult_1.WriteImageData();
}*/

void Problem_2_C()
{
	Image imBarbara;
	Image imResult_1;
	Image imTransfer;

	string szTrans("barbara_trans.raw");
	string szName("barbara_contrast.raw");
	string szName_1("barbara_clean.raw");

	int iRows = 512, iCols = 512;
	int iColorFormat = 1;

	float fMu,fSigma;

	int iaX[256];
	float faP_X[256];
	float faPnX[256];
	float iaCDF[256];
	float fFmin, fFmax;
	float fGmax = 255.00;
	float fGmin = 0.00;

	system("cls");
	cout<<"\nProblem 2.c Histogram Transform Method:";

	imBarbara.SetImageName(szName);
	imBarbara.SetImageRows(iRows);
	imBarbara.SetImageCols(iCols);
	imBarbara.SetImageColorFormat(iColorFormat);
	imBarbara.iPixelCount = iRows*iCols;
	imBarbara.AllocImageMem();

	imBarbara.ReadImageData();
	imBarbara.PlotHistogram();

	imResult_1.SetImageName(szName_1);
	imResult_1.SetImageRows(iRows);
	imResult_1.SetImageCols(iCols);
	imResult_1.SetImageColorFormat(iColorFormat);
	imResult_1.iPixelCount = iRows*iCols;
	imResult_1.AllocImageMem();

	cout<<"\nEnter Value of Mu: ";
	cin>>fMu;
	cout<<"Enter Valur of Sigma: ";
	cin>>fSigma;

	//Init x(n) from 0->255
	for(int i = 0;i<256;i++)
	{
		iaX[i] = i;
	}

	//Find P(X[n])
	for(int i = 0;i<256;i++)
	{
		faP_X[i] = (0.39894/(sqrtf(fSigma))*(exp(-1*pow((float)iaX[i] - fMu,2.00)/(2*pow(fSigma,2.00)))));
	}

	//Find fFmin and fFmax;
	fFmin = faP_X[255];
	fFmax = faP_X[0];
	for(int i = 0;i<256;i++)
	{
		if(fFmax < faP_X[i+1] && i<255)
		{
			fFmax = faP_X[i+1];
		}

		if(fFmin > faP_X[i+1] && i<255)
		{
			fFmin = faP_X[i+1];
		}

	}

	cout<<"\nFmin: "<<fFmin;
	cout<<"\nFmax: "<<fFmax;

	//Normalize Back to 0->1
	for(int i = 0;i<256;i++)
	{
		faPnX[i] = (0.00 + ((1)*(faP_X[i] - fFmin))/(fFmax - fFmin)); 
	}

	float iMax = faPnX[0];

	for(int i = 1;i<256;i++)
	{
		if(iMax < faPnX[i] && i <= 255)
		{
			iMax = faPnX[i];
		}
	}

	for(int i = 0;i<256;i++)
	{
		faPnX[i] = faPnX[i]/iMax;
	}

	iaCDF[0] = faPnX[0];
	//Find CDF Mean
	for(int i = 1;i<256;i++)
	{
		iaCDF[i] = iaCDF[i-1] + faPnX[i];
	}	

	iMax = iaCDF[0];

	for(int i = 1;i<256;i++)
	{
		if(iMax < iaCDF[i] && i <= 255)
		{
			iMax = iaCDF[i];
		}
	}

	for(int i = 0;i<256;i++)
	{
		iaCDF[i] = iaCDF[i]/iMax;
	}

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols;j++)
		{
			Pixel pxP;

			pxP.iBW = faPnX[imBarbara.GetPixel(i,j)->GetBW()]*255;
			
			if(pxP.iBW >= 255)
				pxP.iBW = 255;

			imResult_1.SetPixel(i,j,pxP);	
		}
	}
	
	imResult_1.WriteImageData();
	imResult_1.PlotHistogram();

	//Transfer Function
	iRows = 256;
	iCols = 256;
	iColorFormat = 1;
	Pixel pxP1;
		
	imTransfer.SetImageName(szTrans);
	imTransfer.SetImageRows(iRows);
	imTransfer.SetImageCols(iCols);
	imTransfer.SetImageColorFormat(iColorFormat);
	imTransfer.AllocImageMem();

	//Fill White
	pxP1.iBW = 255;
	for(int j = 0;j<iRows;j++)
	{
		for(int k = 0;k<iCols;k++)
		{
			imTransfer.SetPixel(j,k,pxP1);
		}
	}

	pxP1.iBW = 50;

	for(int i = 0;i<255;i++)
	{
		imTransfer.DrawLine(255 - faPnX[i]*255,i,255 - faPnX[i+1]*255,i+1,pxP1);
	}

	cout<<"\nPloting Transfer Function: ";
	imTransfer.WriteImageData();

	cout<<"\nPress 'C' to contniue.!";
	getch();
}



