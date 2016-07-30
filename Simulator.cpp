#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sstream>
#include <sys/stat.h>
#include "StringHelper.h"
#include "StateGenerator.h"
#include "FileParser.h"
#include "Simulator.h"
#include "BorderMatrix.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace FileParser;
using namespace StringHelper;

Simulator::Simulator(char* fileName)
{
	StateGenerator st(fileName);
	state=st;
	RuleAnalyzer rl(fileName,state.rndSupLim,state.dimension);
	rule=rl;
	initializeDimensions();
}

void Simulator::initializeDimensions()
{
	switch(state.dimension)
	{
	case 1:
		size=state.sizeX;
		break;
	case 2:
		size=state.sizeX*state.sizeY;
		break;
	case 3:
		size=state.sizeX*state.sizeY*state.sizeZ;
		break;
	}
	//results=new int[size];
}

char * Simulator::load_program_source(const char *filename)
{
	struct stat statbuf;
	FILE *fh; 
	char *source; 
	
	fh = fopen(filename, "r");
	if (fh == 0)
		return 0; 
	
	stat(filename, &statbuf);
	source = (char *) malloc(statbuf.st_size + 1);
	size_t t=fread(source, statbuf.st_size, 1, fh);
	source[statbuf.st_size] = '\0'; 
	return source; 
} 

char* Simulator::kernelReplace(char* source,string toReplace, string newString)
{
	string app;
	int i=0;
	while(source[i])
	{
		app+=source[i];
		i++;
	}
	app=myReplace(app,toReplace,newString);
	char* rpl=new char[app.length() + 1];
	strcpy(rpl, app.c_str());
	return rpl;
}

void Simulator::printD1Results(int* buf)
{
		for(int j=state.borderDim;j<size-state.borderDim;j++)
			cout<<buf[j]<<" ";
		cout<<endl;
}

void Simulator::printD2Results(int** buf)
{
		for(int j=state.borderDim;j<state.sizeX-state.borderDim;j++)
		{
			for(int k=state.borderDim;k<state.sizeY-state.borderDim;k++)
				cout<<buf[j][k]<<" ";
			cout<<endl;
		}
}

void Simulator::printD3Results(int*** buf)
{
		for(int j=state.borderDim;j<state.sizeX-state.borderDim;j++)
		{
			for(int k=state.borderDim;k<state.sizeY-state.borderDim;k++)
			{
				for(int n=state.borderDim;n<state.sizeZ-state.borderDim;n++)
					cout<<buf[j][k][n]<<" ";
				cout<<endl;
			}
			cout<<endl;
		}
}
void Simulator::writeOnFileD1(int* source, char* fileName)
{
	vector<string> v;
	string s;
	char buffer[33];
	int val=0;
	stringstream out;
	for(int i=0;i<state.sizeX;i++)
	{
		s+=intToString(source[i]);
		s+=" ";
	}
	v.push_back(s);
	writeInFile(fileName,v);

}
void Simulator::writeOnFileD2(int** source, char* fileName)
{
	vector<string> v;
	string s;
	char buffer[33];
	int val=0;
	stringstream out;
	for(int i=0;i<state.sizeY;i++)
	{
		for(int j=0;j<state.sizeX;j++)
		{
			val=source[j][i];
			s+=intToString(val);
			s+=" ";
		}
		v.push_back(s);
		s="";
	}
	writeInFile(fileName,v);

}

void Simulator::writeOnFileD3(int*** source, char* fileName)
{
	vector<string> v;
	string s;
	char buffer[33];
	int val=0;
	stringstream out;
	for(int i=0;i<state.sizeZ;i++)
	{
		for(int j=0;j<state.sizeY;j++)
		{
			for(int k=0;k<state.sizeX;k++)
			{
				val=source[k][j][i];
				s+=intToString(val);
				s+=" ";
			}
			v.push_back(s);
			s="";
		}
		v.push_back("-----------------");
	}
	writeInFile(fileName,v);

}

void Simulator::spreadMatrixD2toD1(int** source, int* final,int xMax, int xMin,int yMax,int yMin, int borderDim)
{
	int k=0;
	for(int i=yMin-borderDim;i<=yMax+borderDim;i++)
	{
		for(int j=xMin-borderDim;j<=xMax+borderDim;j++)
		{
			final[k++]=source[j][i];
		}
	}
}


void Simulator::compactMatrixD1toD2(int* source, int** final,int xMax, int xMin,int yMax,int yMin, int borderDim)
{
	int i,j,k;
	i=yMin-borderDim;
	j=xMin-borderDim;
	k=0;
	while(i<=yMax+borderDim)
	{
		while(j<=xMax+borderDim)
		{
			final[j++][i]=source[k];
			k++;
		}
		j=xMin-borderDim;
		i++;
	}
}

void Simulator::spreadMatrixD2toD1(int** source, int* final)
{
	int k=0;
	for(int i=0;i<state.sizeY;i++)
	{
		for(int j=0;j<state.sizeX;j++)
		{
			final[k++]=source[j][i];
		}
	}
}

void Simulator::spreadMatrixD3toD1(int*** source, int* final)
{

	int k=0;
	for(int n=0;n<state.sizeZ;n++)
		for(int i=0;i<state.sizeY;i++)
		{
			for(int j=0;j<state.sizeX;j++)
			{
				final[k++]=source[j][i][n];
			}
		}
}

void Simulator::spreadMatrixD3toD1(int*** source, int* final,int sizeX,int sizeY,int sizeZ)
{

	int k=0;
	for(int n=0;n<sizeZ;n++)
		for(int i=0;i<sizeY;i++)
		{
			for(int j=0;j<sizeX;j++)
			{
				
					final[k++]=source[j][i][n];
			}
		}
}

void Simulator::compactMatrixD1toD2(int* source, int** final)
{
	int i,j,k;
	i=j=k=0;
	while(i<state.sizeY)
	{
		while(j<state.sizeX)
		{
			final[j++][i]=source[k];
			k++;
		}
		j=0;
		i++;
	}
}

void Simulator::compactMatrixD1toD3(int* source, int*** final)
{
	int i,j,k,n;
	i=j=k=n=0;
	while(n<state.sizeZ)
	{
		while(j<state.sizeY)
		{
			while(i<state.sizeX)
			{
				final[i++][j][n]=source[k];
				k++;
			}
			j++;
			i=0;
		}
		j=0;
		n++;
	}
}

void Simulator::compactMatrixD1toD3(int* source, int*** final, int sizeX,int sizeY, int sizeZ)
{
	int i,j,k,n;
	i=j=k=n=0;
	while(n<sizeZ)
	{
		while(j<sizeY)
		{
			while(i<sizeX)
			{
				final[i++][j][n]=source[k];
				k++;
			}
			j++;
			i=0;
		}
		j=0;
		n++;
	}
}
