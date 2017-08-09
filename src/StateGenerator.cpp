#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "FileParser.h"
#include "StringHelper.h"
#include "RandomHelper.h"
#include "StateGenerator.h"
#include <time.h>


using namespace std;
using namespace StringHelper;
using namespace RandomHelper;
using namespace FileParser;

StateGenerator::StateGenerator(char* fileName)
{
	//stateFileName=new char('');
	vector<string> vec=readFromFile(fileName);
	state=stringSplit(getMyLine(vec,"S="),' ');
	dimension=extractDimension();
	save=false;
	subMatrix_Flag=false;
	stateType=stateTypology();
	stateData();
	breakString="-----------------";
	switch(stateType)
	{
		case(0):
			stateRndGen();
			break;
		case(1):
			stateFileLoad();
			break;
	}
	//cout<<"Dimension: "<<dimension<<endl;
}
StateGenerator::StateGenerator(){}

void StateGenerator::stateRndGen()
{
srand((unsigned) time(NULL));

		switch(dimension)
		{
		case(1):
			d1 = new int [sizeX];
			for(int b=0;b<borderDim;b++)
				d1[b]=borderVal;
			for(int f=sizeX-borderDim;f<sizeX;f++)
				d1[f]=borderVal;
			//result = new int [sizeX];
			for (int i=borderDim;i<sizeX-borderDim;i++)
			{
				d1[i]=rndBetween(rndInfLim,rndSupLim);
			}
			break;
		case(2):
			d2=new int*[sizeX];
			d2[0]=new int[sizeY];
			for(int j=0;j<sizeX;j++)
			{
				d2[j]=new int[sizeY];
			}
			for(int j=0;j<sizeX;j++)
			{
				
				for(int k=0;k<sizeY;k++)
					d2[j][k]=borderVal;
			}
			for(int j=borderDim;j<sizeX-borderDim;j++)
			{
				
				for(int k=borderDim;k<sizeY-borderDim;k++)
					d2[j][k]=rndBetween(rndInfLim,rndSupLim);
			}

			break;
		case(3):
			d3=new int**[sizeX];
			for(int i=0;i<sizeX;i++)
			{
				d3[i]=new int*[sizeY];
				for(int j=0;j<sizeY;j++)
				{
					d3[i][j]=new int[sizeZ];
					for(int k=0;k<sizeZ;k++)
						d3[i][j][k]=borderVal;
				}
			}
			for(int i=borderDim;i<sizeX-borderDim;i++)
			{
				for(int j=borderDim;j<sizeY-borderDim;j++)
				{
					for(int k=borderDim;k<sizeZ-borderDim;k++)
						d3[i][j][k]=rndBetween(rndInfLim,rndSupLim);
				}
			}
	}
		
}

//DA RIFARE CON VETTORI//
//void StateGenerator::borderCration()
//{
//	switch(dimension)
//	{
//	case(1):
//		for(int b=0;b<borderDim;b++)
//			d1[b]=borderVal;
//		for(int f=sizeX-borderDim;f<sizeX;f++)
//			d1[f]=borderVal;
//		break;
//	case(2):
//		for(int j=0;j<borderDim;j++)
//		{
//			
//			for(int k=0;k<sizeY;k++)
//				d2[j][k]=borderVal;
//			for(int k=0;k<sizeY;k++)
//				d2[sizeX-j-1][k]=borderVal;
//		}
//		for(int j=borderDim;j<sizeX-borderDim;j++)
//		{
//			for(int k=0;k<borderDim;k++)
//				d2[j][k]=borderVal;
//			for(int k=sizeY-borderDim;k<sizeY;k++)
//				d2[j][k]=borderVal;
//		}
//
//
//		break;
//	case(3):
//		for(int i=0;i<sizeX;i++)
//		{
//			for(int j=0;j<sizeY;j++)
//			{
//				d3[i][j]=new int[sizeZ];
//				for(int k=0;k<sizeZ;k++)
//					d3[i][j][k]=borderVal;
//			}
//		}
//		for(int i=borderDim;i<sizeX-borderDim;i++)
//		{
//			for(int j=borderDim;j<sizeY-borderDim;j++)
//			{
//				for(int k=borderDim;k<sizeZ-borderDim;k++)
//					d3[i][j][k]=rndBetween(rndInfLim,rndSupLim);
//			}
//		}
//
//	}
//}

	void StateGenerator::stateFileLoad()
	{
		vector<string> v=readFromFile(stateFileName);
		vector<string> vect_tmp;
		int y=0;
		int z=0;
		switch(dimension)
		{
			case(1):
				d1 = new int [sizeX];
				vect_tmp=stringSplit(v[0],' ');
				
				for (int i=0;i<sizeX;i++)
				{
					d1[i]=atoi(vect_tmp[i].c_str());
				}
				break;
			case(2):
				d2 = new int* [sizeX];
				for(int i=0;i<sizeX;i++)
					d2[i]=new int[sizeY];
				for (int l=0;l<v.size();l++)
				{
					vect_tmp=stringSplit(v[l],' ');
					
					for (int i=0;i<sizeX;i++)
					{
						d2[i][y]=atoi(vect_tmp[i].c_str());
					}
					++y;
				}
				break;
			case(3):
				d3 = new int** [sizeX];
				for(int i=0;i<sizeX;i++)
				{
					d3[i]=new int*[sizeY];
					for(int j=0;j<sizeY;j++)
						d3[i][j]=new int[sizeZ];
				}
				for (int l=0;l<v.size();l++)
				{
					if (v[l]!= breakString)
					{
						vect_tmp=stringSplit(v[l],' ');
						for (int i=0;i<sizeX;i++)
						{
							d3[i][y][z]=atoi(vect_tmp[i].c_str());
						}
						++y;
					}
					else
					{
						z++;
						y=0;
					}
					
				}
				break;
		}
	}

	int StateGenerator::extractDimension ()
	{
		int dimension;
		string s;
		for(int i=0;i<(int)state.size();i++)
			if(state[i][0]=='D')
				s=state[i].substr(2,1);
		dimension=atoi(s.c_str());
		assert(!((dimension<1)||(dimension>3)));

		return dimension;
	}




	int StateGenerator::stateTypology()
	{
		int stateType;
		string str ("RANDOM");
		//string str2 ("SIZE");
		vector<string> tmp_v;
		size_t found;
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
				stateType=0; //RANDOM
		}
		str="FILE";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
				stateType=1; //FILE
		}
		return stateType;
	}

	void StateGenerator::stateData()
	{
		string str ("RANDOM");
		string str2 ("SIZE");
		vector<string> tmp_v;
		size_t found;
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
			{
				tmp_v=stringSplit(between(state[i],'(',')'),',');
				rndInfLim=atoi(tmp_v[0].c_str());
				rndSupLim=atoi(tmp_v[1].c_str());
				
				
			}
		}
		for(unsigned int j=0;j<state.size();j++)
		{
			found=state[j].find(str2);
			if (found!=string::npos)
			{
				switch(dimension)
				{
					case (1):
						sizeX=atoi(between(state[j],'(',')').c_str());
						break;
					case (2):
						tmp_v=stringSplit(between(state[j],'(',')'),',');
						sizeX=atoi(tmp_v[0].c_str());
						sizeY=atoi(tmp_v[1].c_str());
						break;
					case(3):
						tmp_v=stringSplit(between(state[j],'(',')'),',');
						sizeX=atoi(tmp_v[0].c_str());
						sizeY=atoi(tmp_v[1].c_str());
						sizeZ=atoi(tmp_v[2].c_str());
						break;
				}
			}
		}
		str="FILE";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
			{
				str2=between(state[i],'(',')');
				stateFileName=new char[str2.length()+1];
				strcpy(stateFileName, str2.c_str());
			}
		}

		str="WALKPATH";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
			{
				str2=between(state[i],'(',')');
				walkPath=new char[str2.length()+1];
				strcpy(walkPath, str2.c_str());
			}
		}
		str="ITERATION";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
				iteration=atoi(between(state[i],'(',')').c_str());
		}
		str="SUBMATRIX";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
				subMatrix_Flag=true;
		}
		str="SAVE";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
				save=true;
		}
		str="PROB";
		//vector<string> tmp_v;
		//size_t found;
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
			{
				probability=extractProbability(state[i]);
			}
		}
		str="ASHYNC";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			//if (found!=string::npos)
			//	executionType=2; //ASHYNCRONOUS
		}
		str="RAND";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			//if (found!=string::npos)
			//	executionType=3; //RANDOM
		}
		str="WALK";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			//if (found!=string::npos)
			//	executionType=4; //WALK
		}
		str="BCONDITION";
		for(unsigned int i=0;i<state.size();i++)
		{
			found=state[i].find(str);
			if (found!=string::npos)
			{
				tmp_v=stringSplit(between(state[i],'(',')'),',');
				borderGenerator(atoi(tmp_v[0].c_str()),atoi(tmp_v[1].c_str()));
				break;
			}
			else
			{
				borderGenerator(0,1);
			}
				
		}
		sizeX+=borderDim*2;
		sizeY+=borderDim*2;
		sizeZ+=borderDim*2;
	}

void StateGenerator::borderGenerator(int val, int dim)
{
	borderDim=dim;
	borderVal=val;
}

float StateGenerator::extractProbability(string s)
{
	string tmp;
	tmp=s.substr(5,s.length());
	probability=(float)atof(tmp.c_str());

	return probability;
}
