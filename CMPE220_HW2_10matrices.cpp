//============================================================================
// Name        : CMPE220_HW2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<istream>
#include<string>
#include<cstdlib>

#include <string.h>

#include<limits.h>

#include<pthread.h>
#include<time.h>

#include <windows.h>

extern "C"
{
#include <unistd.h>
}

//#include <winuser.h>
//#include <windowsx.h>
//#include <time.h>
#include <stdlib.h>






using namespace std;

#define SIZE 11

int s[11][11];

void optimal_mult(int i,int j)
{
	if (i == j)
		cout<<" A"<<i;
	else
	{
		cout<<" ( ";
		optimal_mult(i, s[i][j]);
		optimal_mult(s[i][j] + 1, j);
		cout<<" ) ";
	}
}

int MatrixChainOrder(int p[], int n)
{

	/* For simplicity of the program, one extra row and one extra column are
       allocated in m[][].  0th row and 0th column of m[][] are not used */
	int m[n][n];

	int i, j, k, L, q;

	/* m[i,j] = Minimum number of scalar multiplications needed to compute
       the matrix A[i]A[i+1]...A[j] = A[i..j] where dimention of A[i] is
       p[i-1] x p[i] */

	// cost is zero when multiplying one matrix.

	for (i = 1; i < n; i++)
	{
		for (j = 1; j < n; j++)
		{
			m[i][j]=-1;
		}

	}
	for (i = 1; i < n; i++)
		m[i][i] = 0;
	char ch;

	// L is chain length.
	for (L=2; L<n; L++)
	{
		cout<<"\nNext Step?:";
		cin>>ch;
		//cout<<ch<<":";
		if(ch=='y')
		{
			for (i=1; i<=n-L+1; i++)
			{
				j = i+L-1;
				m[i][j] = INT_MAX;
				for (k=i; k<=j-1; k++)
				{

					// q = cost/scalar multiplications
					q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
					if (q < m[i][j])
						m[i][j] = q;
				}
			}
			//printf("\n");
			cout<<"\n";
			for (i = 1; i < n; i++)
			{
				for (j = 1; j < n; j++)
				{
					if(m[i][j]==-1)
					{
						//printf("\t");
						cout<<"\t";
					}
					else
						//printf("M(%i,%i):%i\t",i,j,m[i][j]);
						cout<<"M("<<i<<","<<j<<"):"<<m[i][j]<<"\t";
				}
				//printf("\n\n");
				cout<<"\n\n";
			}

		}

	}

	return m[1][n-1];
}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	int n,  i, p[11]={30, 100, 50, 98, 102, 45, 28, 555, 16, 77, 20}, j, k;

	string line;

	cout<<"\nEnter the number of matrices you want to multiply!";
	cin>>n;
	n=10;

	ifstream in_file;
	in_file.open("input.txt");

	cout<<"\nOpening input file!";
	cout<<"\nKeep the file in the following format strictly:\nA1: 30 x 100\nA2: 100 x 50\nA3: 50 x 98";

	if(in_file.fail())
	{
		cout << "Unable to open file";
		exit(1);
	}
	else
	{
		cout<<"\nOpened the input file and reading contents!";
	}


	//while(!in_file.eof())
	//	{
	//		in_file.getline(buf, sizeof buf);
	//		cout << buf << '\n';
	//		//a[index]=next;
	//		//index++;
	//	}
	i=1;
	while ( getline (in_file,line) )
	{
		cout << '\n'<<line << '\n';

		int a=line.find(':');
		int b=line.find('x');
		string temp=line.substr(a+2, b-a);
		string temp1=line.substr(b+2, line.length()-b);
		p[i-1]=atoi(temp.c_str());
		p[i]=atoi(temp1.c_str());

		//cout<<'\n'<<p[i-1]<<'\t'<<p[i]<<temp<<temp1;
		//cout<<'\n'<<temp_p[i-1]<<temp_p[i]<<'\t'<<i;
		i++;
	}
	in_file.close();
	//ifile.close();






	//cout<<"\nEnter the dimensions of each matrix!";

	/*for(i=1;i<=n;i++)
	{
		cout<<"A"<<i;
		cin>>p[i-1];
		cin>>p[i];
	}*/

	int temp;
	int m[11][11];

	//sleep(2);

	cout<<"\nSo for each matrix A, here are the dimensions:";
	for(i=1;i<=n;i++)
	{
		cout<<"\nA"<<i<<"'s Dimensions:"<<p[i-1]<<"*"<<p[i];
	}

	int choice;
	while(1)
	{
		cout<<"\nHello User! Choose from the following:\n 1. Would you be interested in just displaying the results?- Press 1. \n 2. Would you be interested in step-by-step display of the results? Press 2.";
		cin>>choice;

		if(choice==1){


			for(i=1;i<=n;i++)
				for(j=i;j<=n;j++)
				{

					m[i][j]=9999999;
					s[i][j]=0;
				}

			for(i=n;i>=1;i--)
			{
				for(j=i;j<=n;j++)
				{
					if(i==j)
					{
						m[i][j]=0;
						//cout<<"\nHere!";
					}
					else
					{
						for(k=i;k<j;k++)
						{
							temp=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
							//cout<<"\ntemp:"<<temp;
							if(temp<m[i][j])
							{
								m[i][j]=temp;
								s[i][j]=k;
							}
						}
					}
				}
			}

			for(i=1;i<=n;i++)
				for(j=i;j<=n;j++)
				{
					cout<<"\nm["<<i<<"]["<<j<<"]:"<<m[i][j]<<" by the following optimal way: "<<s[i][j];
					optimal_mult(i,j);
				}
			Sleep(2);

			cout<<"\nHence the table would look like follows:\n";

			int i_temp=1;
			n=10;

			for(j=n;j>=1;j--)
			{
				for(i=1;i<=j;i++)
				{
					//for(j=n;j>=i;j--)
					//{
					cout<<"\tm["<<i<<"]["<<j<<"]:"<<m[i][j];
					//optimal_mult(i,j);
					//}
					//cout<<'\n';
				}
				i_temp++;
				cout<<'\n';
			}


		}

		else if(choice==2)
		{

			cout<<"Minimum number of multiplications is "<<
					MatrixChainOrder(p, n+1)<<"\n";

		}

		else{
			cout<<"\nPlease enter a valid input!";
		}
	}

	return 0;
}
