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
#include<conio.h>
#include<iostream>

#include"HomeWork.h"
#include"Image.h"
#include"Pixel.h"

using namespace std;

int PrintMenu();

int main()
{
	int iCh = 0;
	Image imInput_1;

	while(1)
	{
		iCh = PrintMenu();		
		
		switch(iCh)
		{
			case 1:
				system("cls");
				Problem_1_A();
			break;
		
			case 2:
				system("cls");
				Problem_1_B();				
			break;
		
			case 3:
				system("cls");
				Problem_1_C();
			break;
		
			case 4:
				system("cls");
				Problem_1_D();
			break;
		
			case 5:
				system("cls");
				Problem_2_A_a();
				Problem_2_A_b();
			break;
		
			case 6:		
				system("cls");
				Problem_2_B_a();
				
			break;
		
			case 7:		
				system("cls");
				Problem_2_C();
			break;
		
			case 8:
				system("cls");
				Problem_3_A();
			break;
		
			case 9:
				system("cls");
				Problem_3_B();
			break;
		
			case 10:
				system("cls");
				Problem_3_C();
			break;
		
			case 11:
				system("cls");
				Problem_3_D();
			break;
		
			case 12:
				exit(0);
			break;
		
			default:
				cout<<"Shreyansh Daga E569";
		}
	}
}

int PrintMenu()
{
	int iCh = 0;

	while(1)
	{
		system("CLS");
		
		cout<<"\t\t\t\t\t\tShreyansh Daga, USCID 6375334833\n";
		cout<<"******* Home work 1 ********\n";
		cout<<" Problem 1: Image Manipulation \n";
		cout<<"1.  Q1(a) Blue Screen Technique \n";
		cout<<"2.  Q1(b) Identifying Geometrical Objects \n";
		cout<<"3.  Q1(c) Extracting Geometrical Objects \n";
		cout<<"4.  Q1(d) Smart Camera: Moving Object Removal \n\n";
		cout<<" Problem 2: Image Enhancement \n";
		cout<<"5.  Q2(a) Histogram Equalization for Greyscale Images \n";
		cout<<"6.  Q2(b) Histogram Equalization for Color Images \n";
		cout<<"7.  Q2(c) Histogram Transform \n\n";
		cout<<" Problem 3: Noise Removal \n";
		cout<<"8.  Q3(a) Mix Noise in Color Image \n";
		cout<<"9.  Q3(b) Bilateral Filtering \n";
		cout<<"10. Q3(c) Non-Local Mean (NLM) Filtering \n\n";
		cout<<" Bonus Problem \n";
		cout<<"11. Q3(d) Block Matching 3D Transform Filter \n";
		cout<<"12. Exit\n";
		cout<<"\n Enter your choice: ";
		cin>>iCh;

		if(iCh > 12)
		{
			cout<<"\n\n!! Please enter valid choice !!\n\n";
			iCh = 0;
		}
		else
		{
			break;
		}
	}
	return iCh;
}