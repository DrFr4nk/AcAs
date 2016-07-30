#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "SubMatrix.h"
#include "Kernel.h"
#include "SynchronousD3.h"
#include "RandomHelper.h"
#include "FileParser.h"
#include "VectorQueue.h"
#include "HoleMatrixParser.h"

using namespace HoleMatrixParser;

using namespace RandomHelper;
using namespace std;
using namespace FileParser;
using namespace StringHelper;

SynchronousD3::SynchronousD3(char* fileName) : Synchronous(fileName)
{
}

void SynchronousD3::run()
{
	results=new int[size];

	state.d1=new int[size];
	/*if(state.subMatrix_Flag)
		subRunCL();
	else*/
		runCL();
}


void SynchronousD3::printSD3Results()
{
	//printD3Results(bufferD3);
}

void SynchronousD3::runCL()
{
	string path;
	char* c;
	char k[]="kernelS3.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,0,3,size,NULL);
	krnl.connect();
	spreadMatrixD3toD1(state.d3,results);
	krnl.loadParameter(results, size, state.borderDim,0.0f, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputSD3-0.txt";
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
			path="outputSD3-"+intToString(i+1)+".txt";
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
