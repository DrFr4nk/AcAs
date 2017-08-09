#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "Kernel.h"
#include "WalkD1.h"
#include "FileParser.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;
using namespace FileParser;

WalkD1::WalkD1(char* fileName) : Walk(fileName)
{
}

void WalkD1::run()
{
	loadPath();
	results=new int[size];
	bufferD1=new int[size];
	runCL();
}

void WalkD1::loadPath()
{
	vector<string> v=readFromFile(state.walkPath);
	vector<string> vect_tmp;
	pathIndex = new int* [state.iteration];
	vect_tmp=stringSplit(v[0],' ');
	
	for (int i=0;i<state.iteration;i++)
	{
		pathIndex[i]=new int[1];
		pathIndex[i][0]=atoi(vect_tmp[i].c_str());
	}
}

void WalkD1::runCL()
{
	string path;
	char* c;
	char k[]="kernelW.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,2,1,size, pathIndex);
	krnl.connect();
	krnl.loadParameter(state.d1, size, state.borderDim,0.0f, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputWD1-0.txt";
			c=(char*)path.c_str();
			writeOnFileD1(state.d1, c);
		}
	ivllib::Timer t;	
	t.start();
	for(int i=0;i<state.iteration;i++)
	{
		results=krnl.run();
		if (state.save)
		{
			path="outputWD1-"+intToString(i+1)+".txt";
			c=(char*)path.c_str();
			writeOnFileD1(results, c);
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


void WalkD1::printWD1Results()
{
	printD1Results(bufferD1);
}
