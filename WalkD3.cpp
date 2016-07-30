#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "WalkD3.h"
#include "Kernel.h"
#include "RandomHelper.h"
#include "FileParser.h"

using namespace RandomHelper;
using namespace std;
using namespace FileParser;
using namespace StringHelper;

WalkD3::WalkD3(char* fileName) : Walk(fileName)
{
}

void WalkD3::run()
{
	loadPath();
	results=new int[size];
	runCL();
}

void WalkD3::loadPath()
{
	vector<string> v=readFromFile(state.walkPath);
	string stmp;
	vector<string> vect_tmp;
	pathIndex = new int* [state.iteration];
	int i=0;
	vect_tmp=stringSplit(v[0],' ');
	for (int l=0;l<v.size();l++)
	{
			pathIndex[i]=new int[3];
			stmp=between(v[l],'(',')');
			vect_tmp=stringSplit(stmp,',');
			pathIndex[i][0]=atoi(vect_tmp[0].c_str());
			pathIndex[i][1]=atoi(vect_tmp[1].c_str());
			pathIndex[i][2]=atoi(vect_tmp[2].c_str());
			i++;
	}
}

void WalkD3::runCL()
{
	string path;
	char* c;
	char k[]="kernelW3.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,2,3,size, pathIndex);
	krnl.connect();
	spreadMatrixD3toD1(state.d3,results);
	krnl.loadParameter(results, size, state.borderDim,0.0f, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputWD3-0.txt";
			c=(char*)path.c_str();
			writeOnFileD3(state.d3, c);
		}
	ivllib::Timer t;	
	t.start();
	for(int i=0;i<state.iteration;i++)
	{
		results=krnl.run();
		compactMatrixD1toD3(results,state.d3);
		if (state.save)
		{
			path="outputWD3-"+intToString(i+1)+".txt";
			c=(char*)path.c_str();
			writeOnFileD3(state.d3, c);
		}
	}
	t.stop();
	if (t.getElapsedTime()>60)
	{
		int min=t.getElapsedTime()/60;
		double sec=t.getElapsedTime()-min*60;
		printf("Tempo esecuzione OpenCL: %d minuti %f secondi\n", min,sec);
	}
	else
		printf("Tempo esecuzione OpenCL: %f secondi\n", t.getElapsedTime());
	krnl.disconnect();
	
}
