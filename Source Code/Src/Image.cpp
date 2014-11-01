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

#include"Image.h"
#include"Histogram.h"

Image::Image()
{
	this->pImageDate = NULL;
}

Image::Image(unsigned char **ImageData,int Rows, int Cols, int ColorFormat, string ImageName)
{
	this->pImageDate = ImageData;
	this->iRows = Rows;
	this->iCols = Cols;
	this->iColorFormat  = ColorFormat;
	this->szImageName = ImageName;
}

Image::~Image()
{

}

string Image::GetImageName()
{
	return this->szImageName;
}

int Image::GetImageRows()
{
	return this->iRows;
}

int Image::GetImageCols()
{
	return this->iCols;
}

int Image::GetImageColorFormat()
{
	return this->iColorFormat;
}

void Image::SetImageRows(int iRows)
{
	this->iRows = iRows;
}

void Image::SetImageCols(int iCols)
{
	this->iCols = iCols;
}

void Image::SetImageColorFormat(int iColorFormat)
{
	this->iColorFormat = iColorFormat;
}

void Image::SetImageName(string szName)
{
	this->szImageName = szName;
}

void Image::SetPixel(int X,int Y, Pixel pxP)
{
	if(this->GetImageColorFormat() == 3)
	{
		this->pImageDate[X][Y*3] = pxP.GetRed();
		this->pImageDate[X][Y*3+1] = pxP.GetGreen();
		this->pImageDate[X][Y*3+2] = pxP.GetBlue();
	}
	else if(this->GetImageColorFormat() == 1)
	{
		this->pImageDate[X][Y] = pxP.GetBW();
	}
}

Pixel* Image::GetPixel(int X, int Y)
{
	int R, G, B, BW;
	Pixel *pPixel;

	if(this->GetImageColorFormat() == 1)
	{
		BW = this->pImageDate[X][Y];
	}
	else
	{
		R = this->pImageDate[X][3*Y];
		G = this->pImageDate[X][3*Y+1];
		B = this->pImageDate[X][3*Y+2];
	}

	if(this->GetImageColorFormat() == 1)
	{
		pPixel = new Pixel(BW ,X ,Y, true);
	}
	else if(this->GetImageColorFormat() == 3)
	{
		pPixel  = new Pixel(R, G, B, X, Y);
	}

	return pPixel;
}

Pixel* Image::GetNBPixel(Pixel pxP, int idX, int idY)
{
	Pixel *pNBP = new Pixel;
	int iCX, iCY;

	iCX = pxP.GetPixelX();
	iCY = pxP.GetPixelY();

	pNBP = this->GetPixel(iCX + idX,iCY + idY);

	return pNBP;
}

void Image::WriteImageData()
{
	FILE *fpOutImageFile;
	char szOpImageName[30];
	int iImageSize;

	
	strcpy(szOpImageName,this->szImageName.c_str());

	fpOutImageFile = fopen(szOpImageName,"wb");	

	for(int i = 0;i<this->iRows;i++)
	{
		fwrite(this->pImageDate[i],sizeof(unsigned char),iCols*iColorFormat,fpOutImageFile);
	}
	fclose(fpOutImageFile);

	fopen(szOpImageName,"rb");
	
	fseek (fpOutImageFile, 0, SEEK_END); 
	iImageSize = ftell(fpOutImageFile);

	cout<<"\n*Output Image Data write complete:";
	cout<<"\n Name: "<<szOpImageName;
	cout<<"\n Size: "<<this->iCols<<"x"<<iRows<<", "<<iImageSize/1024<<" KBytes";
	cout<<"\n Color Format: "<<this->iColorFormat;

	fclose(fpOutImageFile);
}

void Image::ReadImageData()
{
	char szImageFileName[30];	
	FILE *fpImageFileIn;	
	int iImageSize;

	strcpy(szImageFileName,this->szImageName.c_str());
	while(1)
	{
		fpImageFileIn = fopen(szImageFileName,"rb");
		
		if(!fpImageFileIn)
		{
			cout<<"\nCan Not Open File. ";
			cout<<"Please Enter File name correctly.!";
			cout<<"\nFile Name: ";
			cin>>szImageFileName;
		}
		else
		{
			this->szImageName.assign(szImageFileName);
			break;
		}
	}

	for(int i = 0;i < this->GetImageRows() ;i++)
	{
		fread(this->pImageDate[i],sizeof(unsigned char),this->iCols*this->iColorFormat,fpImageFileIn);
	}

	fseek (fpImageFileIn, 0, SEEK_END);   
	iImageSize = ftell(fpImageFileIn);
	fclose(fpImageFileIn);	

	cout<<"\n*Input Image Data read complete:";
	cout<<"\n Name: "<<szImageFileName;
	cout<<"\n Size: "<<iImageSize/1024<<" KBytes";
	cout<<"\n Color Format: "<<this->iColorFormat;
}

void Image::ReadImageInfo()
{
	char szImageFileName[30];
	int iRows,iCols,iColorFormat;

	cout<<"\n Enter Image Name: ";
	cin>>szImageFileName;
	cout<<" Enter the Number of Rows: ";
	cin>>iRows;
	cout<<" Enter the Number of Cols: ";
	cin>>iCols;
	cout<<" Enter the Color Format (RBG: 3, GraScale: 1): ";
	cin>>iColorFormat;

	this->szImageName.assign(szImageFileName);
	this->iRows = iRows;
	this->iCols = iCols;
	this->iColorFormat = iColorFormat;
	this->iPixelCount = iRows*iCols;

	this->AllocImageMem();	
}

void Image::AllocImageMem()
{
	this->pImageDate = new unsigned char* [this->GetImageRows()];	

	for(int i = 0;i< this->GetImageRows();i++)
	{
		this->pImageDate[i] = new unsigned char[this->GetImageCols()*this->GetImageColorFormat()];
	}

	this->hHist.InitHist(this->szImageName,this->GetImageRows(),this->GetImageCols(),this->GetImageColorFormat());
}

void Image::DrawLine(int X1, int Y1, int X2, int Y2, Pixel pxP)
{
	int idX = abs(X2 - X1), idY(Y2 - Y1);
	int iErr = idX - idY;
	int iSx,iSy;

	if(X1 < X2)
	{
		iSx = 1;
	}
	else
	{
		iSx = -1;
	}

	if(Y1 < Y2)
	{
		iSy = 1;
	}
	else
	{
		iSy = -1;
	}

	while(1)
	{
		this->SetPixel(X1,Y1,pxP);

		if(X1 == X2 && Y1 == Y2)
			break;

		if(iErr*2 > -idY)
		{
			iErr -= idY;
			X1 += iSx;
		}

		if(X1 == X2 && Y1 == Y2)
		{
			this->SetPixel(X1,Y1,pxP);
			break;
		}

		if(iErr*2 < idX)
		{
			iErr += idX;
			Y1 += iSy;
		}
	}
}

void Image::PlotHistogram()
{
	//Fill The Pixel Array used for Histogram
	Pixel *ppxP;

	for(int i=0;i<this->GetImageRows();i++)
	{
		for(int j=0;j<this->GetImageCols();j++)
		{
			ppxP = this->GetPixel(i,j);
			this->hHist.pxaPixArr[i][j] = *ppxP;
			delete ppxP;
		}
	}

	this->hHist.PlotHistogram();
}

void Image::PlotCumHistogram()
{
	//Fill The Pixel Array used for Histogram
	Pixel *ppxP;

	for(int i=0;i<this->GetImageRows();i++)
	{
		for(int j=0;j<this->GetImageCols();j++)
		{
			ppxP = this->GetPixel(i,j);
			this->hHist.pxaPixArr[i][j] = *ppxP;
			delete ppxP;
		}
	}

	this->hHist.PlotCumHistogram();
}

void Image::FreeResources()
{

	this->hHist.FreeHistogram();

	if(this->pImageDate ==NULL)
		return;

	for (int i = 0; i < this->iRows; i++)
  	{
		delete [] this->pImageDate[i];
  	}

	delete[] this->pImageDate;

	this->pImageDate = NULL;
}

void Image::ImageExtend(int iSize)
{
	int iRow = this->iRows + iSize;
	int iCol = this->iCols + iSize;
	string szName("extened.raw");

	this->SetImageName(szName);

	unsigned char **pcExtendImage = new unsigned char*[iRow];

	for(int i = 0;i<iRow;i++)
	{
		pcExtendImage[i] = new unsigned char[iCol*this->iColorFormat];
	}

	//Mid	
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iCols*iColorFormat;j++)
		{
			pcExtendImage[i+iSize][j+iSize] = this->pImageDate[i][j];
			pcExtendImage[i+iSize][j+iSize+1] = this->pImageDate[i][j+1];
			pcExtendImage[i+iSize][j+iSize+2] = this->pImageDate[i][j+2];
		}
	}

	//Corners
	for(int i = 0;i<iSize;i++)
	{
		for(int j = 0;j<iSize*iColorFormat;j++)
		{
			pcExtendImage[i][j] = this->pImageDate[0][0];
			pcExtendImage[i][j+1] = this->pImageDate[0][1];
			pcExtendImage[i][j+2] = this->pImageDate[0][2];

			pcExtendImage[iRows - 1 + i][j] = this->pImageDate[iRows-1][0];
			pcExtendImage[iRows - 1 + i][j+1] = this->pImageDate[iRows-1][1];
			pcExtendImage[iRows - 1 + i][j+2] = this->pImageDate[iRows-1][0];

			pcExtendImage[i][iCols -1 + j] = this->pImageDate[0][iCols - 1];
			pcExtendImage[i][iCols -1 + j +1] = this->pImageDate[0][iCols];
			pcExtendImage[i][iCols -1+ j +2] = this->pImageDate[0][iCols +1];

			pcExtendImage[iRows - 1 + i][iCols -1 + j] = this->pImageDate[iRows -1][iCols - 1];
			pcExtendImage[iRows - 1 + i][iCols - 1 + j] = this->pImageDate[iRows -1][iCols];
			pcExtendImage[iRows -1 + i][iCols -1 + j] = this->pImageDate[iRows -1][iCols + 1];
		}
	}
	
	//Left
	for(int i = 0;i<iRows;i++)
	{
		for(int j = 0;j<iSize*iColorFormat;j++)
		{
			pcExtendImage[i][j] = this->pImageDate[i][0];
			pcExtendImage[i][j+1] = this->pImageDate[i][1];
			pcExtendImage[i][j+2] = this->pImageDate[i][2];
		}
	//Right
		for(int j = iCol - iSize - 1;j<iCol*iColorFormat;j++)
		{
			pcExtendImage[i][j] = this->pImageDate[i][iCols - 1];
			pcExtendImage[i][j+1] = this->pImageDate[i][iCols];
			pcExtendImage[i][j+2] = this->pImageDate[i][iCols + 1];
		}
	}

	//Top
	for(int j = 0;j<iCols*iColorFormat;j++)
	{
		for(int i = 0;i<iSize;i++)
		{
			pcExtendImage[i][j] = this->pImageDate[0][j];
			pcExtendImage[i][j+1] = this->pImageDate[0][j+1];
			pcExtendImage[i][j+2] = this->pImageDate[0][j+2];
		}
		//Bottom
		for(int i = iRow - iSize - 1;i<iRow;i++)
		{
			pcExtendImage[i][j] = this->pImageDate[iRows - 1][j];
			pcExtendImage[i][j+1] = this->pImageDate[iRows - 1][j+1];
			pcExtendImage[i][j+2] = this->pImageDate[iRows - 1][j+2];
		}
	}

	for(int i = 0;i<iRows;i++)
		delete [] this->pImageDate[i];
	delete [] this->pImageDate;
	
	this->pImageDate=pcExtendImage;

	this->iRows = iRow;
	this->iCols = iCol;

	this->iPixelCount = iRow*iCol;
}