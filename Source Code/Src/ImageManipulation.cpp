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
#include<ctime>

#include"Image.h"
#include"HomeWork.h"

using namespace std;

int iaResultSizeofCircle[5];
int iaResultSizeofSquare[5];

void Problem_1_A()
{
	Image imInput_1, imOutput_1;
	int iBMax = 210, iGMax = 50, iRMax = 50;

	system("CLS");
	cout<<"\nQ.1(A) Blue Screen Technique";
	//Read input and output image information from user
	cout<<"\nInput Image Info:\n";
	imInput_1.ReadImageInfo();
	cout<<"\nOutput Image Info:\n";
	imOutput_1.ReadImageInfo();

	//Read Image Data
	imInput_1.ReadImageData();
	
	//Plot Histogram
	//PlotHistogram(imInput_1);
	imInput_1.PlotHistogram();

	cout<<"\nEnter Values of (B)min: ";
	cin>>iBMax;
	cout<<"Enter Value of G(max): ";
	cin>>iGMax;
	cout<<"Enter Value of R(max): ";
	cin>>iRMax;

	//Remove Blue Screen
	for(int i  = 0; i < imInput_1.GetImageRows(); i++)
	{		
		for(int j = 0; j < imInput_1.GetImageCols()*imInput_1.GetImageColorFormat(); j += imInput_1.GetImageColorFormat())
		{			
			if( ((int)imInput_1.pImageDate[i][j] <= iRMax) && ((int)imInput_1.pImageDate[i][j + 1] <= iGMax) && ((int)imInput_1.pImageDate[i][j + 2] >= iBMax) )
			{
				imOutput_1.pImageDate[i][j] = (unsigned char)255;
				imOutput_1.pImageDate[i][j + 1] = (unsigned char)255;
				imOutput_1.pImageDate[i][j + 2] = (unsigned char)255;
			}
			else
			{
				imOutput_1.pImageDate[i][j] = imInput_1.pImageDate[i][j];
				imOutput_1.pImageDate[i][j+1] = imInput_1.pImageDate[i][j+1];
				imOutput_1.pImageDate[i][j+2] = imInput_1.pImageDate[i][j+2];
			}
		}
	}

	//Write output ImageFile
	imOutput_1.WriteImageData();
	imOutput_1.PlotHistogram();

	cout<<"\nPress 'C' to continue:";
	getch();
}

void Problem_1_B()
{
	int iCx,iCy,x = 0;
	Image imCleanImage;
	Pixel pxaIntersectPointsHR[20];
	Pixel pxCurr;
	int iObjects = 0;
	int iSqs = 0, iCrs = 0;
	bool bSq = true, bCr = true;
	int c = 0; //Circle count
	int s = 0; //Square count

	cout<<"\nQ.1(2) Identifying Geometrical Objects";
	//Read input and output image information from user
	cout<<"\nInput Image Info(shapes_out.raw):\n";
	//Get the clean image from user
	imCleanImage.ReadImageInfo();
	imCleanImage.ReadImageData();

	//Aquire Center of image
	iCx = imCleanImage.GetImageCols()/2;
	iCy = imCleanImage.GetImageRows()/2;

	//Find Intersectpoints
	//First Traversal Horizontal right from center
	int i = iCx;
	for(int j = iCy;j<iCy*2;j++)
	{
		pxCurr = *(imCleanImage.GetPixel(i,j));

		//Check for intercept
		if(!(pxCurr.GetRed() == 255 && pxCurr.GetBlue() == 255 && pxCurr.GetGreen() == 255))
		{
			pxaIntersectPointsHR[x] = pxCurr;
			x++;//INtersection Count
		}
	}

	//Check each point's neighbourhood for circles
	float fDist  = 0.00;
	for(int j = 0;j<x;j++)
	{	
		//AssumeRadius
		fDist = imCleanImage.GetPixel(iCx,iCy)->DistanceTo(pxaIntersectPointsHR[j]);

		//Check for thickness
		if(imCleanImage.GetNBPixel(pxaIntersectPointsHR[j],0,1)->GetBW() != 255)
		{
			//Increase pixel distance to next pixel as we have hit a circle
			fDist++;
			//Skip pixel to enable correct detection of radius and cuts at 45 60 and 30 degrees
			j++;
			continue;
		}

		//Find Points at 45,30,60 from center with radius for circle
		if((imCleanImage.GetPixel((int)(fDist*0.7072 + iCx),(int)(fDist*0.7072 + iCy))->GetBW() != 255) || ((imCleanImage.GetPixel((int)(fDist*0.8660 + iCx),(int)(fDist*0.5 + iCy))->GetBW() != 255) && (imCleanImage.GetPixel((int)(fDist*0.5 + iCx),(int)(fDist*0.8660 + iCy))->GetBW() != 255)))
		{
			iCrs++;
			cout<<"\nObject Detected: Circle, Radius: "<<fDist<<" pixels";
			iaResultSizeofCircle[++c] =(int) fDist;
		}//else its square
		else if(imCleanImage.GetPixel((int)(fDist + iCx),(int)(fDist + iCy))->GetBW() != 255)
		{
			iSqs++;
			cout<<"\nObject Detected: Square, Size: "<<fDist*2<<" pixels";
			iaResultSizeofSquare[++s] =(int) fDist;
		}
	}
	
	cout<<"\nTotal Objects detected: "<<iSqs+iCrs;
	iaResultSizeofCircle[0] = iCrs;
	iaResultSizeofSquare[0] = iSqs;

	cout<<"\nPress 'C' to continue:";
	getch();
}

void Problem_1_C()
{
	Image imExObj_Sq, imInputImage;
	Image imExObj_Cr;
	int iObjEx;
	int iRadius, iSize;
	int iX1,iY1,iX2,iY2,iCX,iCY;

	system("cls");
	cout<<"\nQ.1(3) Extracting Geometrical Objects";
	cout<<"\nInput Image Info (shapes_out.raw) :\n";
	//Get the clean image from user
	imInputImage.ReadImageInfo();
	imInputImage.ReadImageData();

	//Get output Image info
	cout<<"\nOutput Image Info: Square\n";
	imExObj_Sq.ReadImageInfo();

	iCX = imInputImage.GetImageRows()/2;
	iCY = imInputImage.GetImageCols()/2;

	//Second largest Square
	iSize = iaResultSizeofSquare[2];

	iX1 = iCX - iSize;
	iY1 = iCY - iSize;
	iX2 = iCX + iSize;
	iY2 = iCY + iSize;

	//Create White Image	
	for(int i = 0;i < imExObj_Sq.GetImageRows();i++)
	{
		for(int j = 0;j < imExObj_Sq.GetImageCols()*imExObj_Sq.GetImageColorFormat();j++)
		{
			imExObj_Sq.pImageDate[i][j] = (unsigned char)255;
		}
	}

	Pixel *ppxP;
	//Top
	for(int i = iX1;i <=iX2;i++)
	{
		ppxP = imInputImage.GetPixel(i,iY1);
		imExObj_Sq.SetPixel(i,iY1,*ppxP);//*imInputImage.GetPixel(i,iY1));
		delete ppxP;
	}
	//Bottom
	for(int i = iX1;i<=iX2;i++)
	{
		ppxP = imInputImage.GetPixel(i,iY2);
		imExObj_Sq.SetPixel(i,iY2,*ppxP);
		delete ppxP;
	}
	//Left
	for(int j = iY1;j<=iY2;j++)
	{
		ppxP = imInputImage.GetPixel(iX1,j);
		imExObj_Sq.SetPixel(iX1,j,*ppxP);
		delete ppxP;
	}
	//Bottom
	for(int j = iY1;j<=iY2;j++)
	{
		ppxP = imInputImage.GetPixel(iX2,j);
		imExObj_Sq.SetPixel(iX2,j,*ppxP);
		delete ppxP;
	}
	//Write square image
	imExObj_Sq.WriteImageData();


	//Get output Image info
	cout<<"\nOutput Image Info: Circle \n";
	imExObj_Cr.ReadImageInfo();

	//Circle
	iSize = iaResultSizeofCircle[3];

	//Create White Image	
	for(int i = 0;i < imExObj_Cr.GetImageRows();i++)
	{
		for(int j = 0;j < imExObj_Cr.GetImageCols()*imExObj_Cr.GetImageColorFormat();j++)
		{
			imExObj_Cr.pImageDate[i][j] = (unsigned char)255;
		}
	}

	int iTX,iTY;

	iSize--;
	for(int theta = 0;theta<=360;theta++)
	{
		iTX = (int)(iSize*cos(theta*3.14159/180) + iCX);
		iTY = (int)(iSize*sin(theta*3.14159/180) + iCY);
		
		//Main Pixel
		imExObj_Cr.SetPixel(iTX,iTY,*imInputImage.GetPixel(iTX,iTY));
		//NB Pixels
		imExObj_Cr.SetPixel(iTX+1,iTY,*imInputImage.GetPixel(iTX+1,iTY));
		imExObj_Cr.SetPixel(iTX+2,iTY,*imInputImage.GetPixel(iTX+2,iTY));
		imExObj_Cr.SetPixel(iTX-1,iTY,*imInputImage.GetPixel(iTX-1,iTY));
		imExObj_Cr.SetPixel(iTX,iTY+1,*imInputImage.GetPixel(iTX,iTY+1));
		imExObj_Cr.SetPixel(iTX,iTY+2,*imInputImage.GetPixel(iTX,iTY+2));
		imExObj_Cr.SetPixel(iTX,iTY-1,*imInputImage.GetPixel(iTX,iTY-1));
		imExObj_Cr.SetPixel(iTX+1,iTY+1,*imInputImage.GetPixel(iTX+1,iTY+1));
		imExObj_Cr.SetPixel(iTX-1,iTY-1,*imInputImage.GetPixel(iTX-1,iTY-1));
		imExObj_Cr.SetPixel(iTX-1,iTY+1,*imInputImage.GetPixel(iTX-1,iTY+1));
		imExObj_Cr.SetPixel(iTX+1,iTY-1,*imInputImage.GetPixel(iTX+1,iTY-1));
	}

	//Write circle image
	imExObj_Cr.WriteImageData();

	cout<<"\nPress 'C' to continue:";
	getch();
}

void Problem_1_D()
{
	Image imSuperManImages[8];
	Image imSuperManDiff[8];
	unsigned char **pcTemp;
	Image imCleanWhiteHouse_1,imCleanWhiteHouse_2,imCleanWhiteHouse;
	string szImageNames[] = {"firstclick.raw","secondclick.raw","thirdclick.raw","fourthclick.raw","fifthclick.raw","sixthclick.raw","seventhclick.raw","eighthclick.raw"};	
	string szDiffNames[] = {"firstclick_d.raw","secondclick_d.raw","thirdclick_d.raw","fourthclick_d.raw","fifthclick_d.raw","sixthclick_d.raw","seventhclick_d.raw","eighthclick_d.raw"};	

	int iRows, iCols, iColorFormat;
	char szImagName[30];

	int iRand1,iRand2;

	int iBlackPixCount = 0;

	//Load superman images
	system("cls");
	iRows = 453;
	iCols = 750;
	iColorFormat = 3;
	
	int **dpiFlag = new int* [iRows];

	for(int i = 0;i<iRows;i++)
	{
		dpiFlag[i] = new int[iCols*3];
	}

	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols*3;j++)
		{
			dpiFlag[i][j] = 1;
		}
	}

	for(int i = 0;i<8;i++)
	{
		imSuperManImages[i].SetImageName(szImageNames[i]);
		imSuperManImages[i].SetImageRows(iRows);
		imSuperManImages[i].SetImageCols(iCols);
		imSuperManImages[i].SetImageColorFormat(iColorFormat);
		imSuperManImages[i].iPixelCount = iRows*iCols;
		imSuperManImages[i].AllocImageMem();
	}

	//Read the images
	for(int i = 0;i<8;i++)
	{
		imSuperManImages[i].ReadImageData();
	}

	pcTemp = new unsigned char*[iRows];
	for(int i = 0;i<iRows;i++)
	{
		pcTemp[i] = new unsigned char[iCols*iColorFormat];
	}

	cout<<"\nEnter info for Clean White House image: \n";
	imCleanWhiteHouse.ReadImageInfo();

	srand(150);
	
	int iFlag = 0;

	while(iFlag < iRows*iCols*3)
	{
		iRand1 = (rand())%8;
		iRand2 = (rand())%8;
		
		if(iRand1 == iRand2)
			continue;
		
		cout<<"\n"<<iRand1<<","<<iRand2;

		for(int i = 0; i<iRows;i++)
		{
			for(int j = 0; j<iCols*iColorFormat;j++)
			{
				//if(*imSuperManImages[iRand1].GetPixel(i,j) == *imSuperManImages[iRand2].GetPixel(i,j))
				if(imSuperManImages[iRand1].pImageDate[i][j] == imSuperManImages[iRand2].pImageDate[i][j])
				{
					//Same Pix
					if(dpiFlag[i][j] == 1)
					{
						//Recover backgnd
						imCleanWhiteHouse.pImageDate[i][j] = imSuperManImages[iRand1].pImageDate[i][j];
						dpiFlag[i][j] = 0;
						
						//Increment flag
						iFlag++;
					}						
				}							
			}		
		}
	}
	Image imWhiteHouseCleanTuned(imCleanWhiteHouse);
	imWhiteHouseCleanTuned.SetImageName(*new string("White_ReClean.raw"));
	imWhiteHouseCleanTuned.AllocImageMem();

	//Fine tune
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols*3;j++)
		{
			dpiFlag[i][j] = 1;
		}
	}

	for(int k = 0;k<8;k++)
	{
		iFlag = 0;
		for(int i = 0; i<iRows;i++)
		{
			for(int j = 0; j<iCols*iColorFormat;j++)
			{				
				if(imSuperManImages[k].pImageDate[i][j] == imCleanWhiteHouse.pImageDate[i][j])
				{
					//Same Pix
					if(dpiFlag[i][j] == 1)
					{
						//Recover backgnd					
						imWhiteHouseCleanTuned.pImageDate[i][j] = imCleanWhiteHouse.pImageDate[i][j];
						dpiFlag[i][j] = 0;
						//Increment flag
						iFlag++;
					}						
				}							
			}	
		}
	}

	//cout<<"all end";
	imCleanWhiteHouse.WriteImageData();
	imWhiteHouseCleanTuned.WriteImageData();


	//Allocate diff images
	for(int i = 0;i<8;i++)
	{
		//cout<<"\nEnter Image "<<i+1<<" Name: ";
		//cin>>szImagName;
		imSuperManDiff[i].SetImageName(szDiffNames[i]);
		imSuperManDiff[i].SetImageRows(iRows);
		imSuperManDiff[i].SetImageCols(iCols);
		imSuperManDiff[i].SetImageColorFormat(iColorFormat);
		imSuperManDiff[i].iPixelCount = imSuperManDiff[i].GetImageCols()*imSuperManDiff[i].GetImageRows();
		imSuperManDiff[i].AllocImageMem();
	}

	//Diff with superman and clean image
	for(int i = 0;i<8;i++)
	{
		for(int j = 0;j<iRows;j++)
		{
			for(int k = 0;k<iCols;k++)
			{
				if(*imSuperManImages[i].GetPixel(j,k) == *imWhiteHouseCleanTuned.GetPixel(j,k))
				{
					imSuperManDiff[i].SetPixel(j,k,(*imSuperManImages[i].GetPixel(j,k) - *imWhiteHouseCleanTuned.GetPixel(j,k)));
				}
				else
					imSuperManDiff[i].SetPixel(j,k,(*imSuperManImages[i].GetPixel(j,k)));
			}
		}
		imSuperManDiff[i].WriteImageData();
	}
		//Find Bounding box for each diff;
		Pixel *ppxPArr[8]; 
		Image imSuperMan[8];
		string szSubBlockName[8] = {"S_1.raw","S_2.raw","S_3.raw","S_4.raw","S_5.raw","S_6.raw","S_7.raw","S_8.raw"};
		int iMaxX = 0,iMaxY = 0,iMinX = 453,iMinY = 750;
		int iCount = 0;

		//INit Variables
		for(int i = 0;i<8;i++)
		{
			ppxPArr[i] = new Pixel[iRows*iCols];
		}

	for(int k = 0;k<8;k++)
	{
		iCount = 0;
		for(int i = 0;i <iRows;i++)
		{
			for(int j=0;j<iCols;j++)
			{
				if(imSuperManDiff[k].GetPixel(i,j)->GetBW() == 0)
					continue;
				else
					ppxPArr[k][iCount++] = *imSuperManDiff[k].GetPixel(i,j);
			}
		}

		iMaxX = 0;
		iMaxY = 0;
		iMinX = 453;
		iMinY = 750;

		//Extract Superman bock	
		for(int i = 0;i<iCount;i++)
		{
			if(ppxPArr[k][i].GetPixelX() > iMaxX)
				iMaxX = ppxPArr[k][i].GetPixelX();

			if(ppxPArr[k][i].GetPixelY() > iMaxY)
				iMaxY = ppxPArr[k][i].GetPixelY();

			if(ppxPArr[k][i].GetPixelX() < iMinX)
				iMinX = ppxPArr[k][i].GetPixelX();

			if(ppxPArr[k][i].GetPixelY() <iMinY)
				iMinY = ppxPArr[k][i].GetPixelY();
		}
			
		imSuperMan[k].SetImageRows(iMaxX + 1 - iMinX);
		imSuperMan[k].SetImageCols(iMaxY + 1 - iMinY);
		imSuperMan[k].SetImageColorFormat(3);
		imSuperMan[k].SetImageName(szSubBlockName[k]);
		imSuperMan[k].AllocImageMem();

		//Extract Block
		for(int i = iMinX;i<iMaxX+1;i++)
		{
			for(int j = iMinY;j<iMaxY+1;j++)
			{
				imSuperMan[k].SetPixel(i - iMinX,j - iMinY,*imSuperManDiff[k].GetPixel(i,j));
			}
		}
		imSuperMan[k].WriteImageData();
	}

	int iMaxCount = 0;

	for(int i = 0;i<8;i++)
	{
		for(int j = 0;j<7;j++)
		{
			if(imSuperMan[j].GetImageRows() < imSuperMan[j+1].GetImageRows())
			{
				Image im(imSuperMan[j]);
				imSuperMan[j] = imSuperMan[j+1];
				imSuperMan[j+1] = im;
			}
		}
	}

	//Get the dog
	Image imDog;
	Image imDog_Out;

	cout<<"\nDogjump info: ";
	imDog.ReadImageInfo();
	imDog.ReadImageData();
	imDog_Out.ReadImageInfo();

	for(int i = 0;i<507;i++)
	{
		for(int j = 0;j<900;j++)
		{
			Pixel *pxP = imDog.GetPixel(i,j);
			imDog_Out.SetPixel(i,j,*pxP);
			delete pxP;
		}
	}

	for(int i = 0;i<imSuperMan[1].GetImageRows();i++)
	{
		for(int j = 0;j<imSuperMan[1].GetImageCols();j++)
		{
			Pixel *pxP = imSuperMan[1].GetPixel(i,j);
			if(((int)pxP->iR != 0) && ((int)pxP->iG != 0) && ((int)pxP->iB != 0))
			{
				imDog_Out.SetPixel(i+270,j+320,*pxP);
			}
			delete pxP;
		}
	}	

	imDog_Out.WriteImageData();

	cout<<"\nPress 'C' to continue!";
	getch();
}
