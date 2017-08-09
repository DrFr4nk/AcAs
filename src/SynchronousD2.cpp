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
#include "VectorQueue.h"
#include "Kernel.h"
#include "SynchronousD2.h"
#include "RandomHelper.h"
#include "HoleMatrixParser.h"

using namespace HoleMatrixParser;
using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

SynchronousD2::SynchronousD2(char* fileName) : Synchronous(fileName)
{
}

void SynchronousD2::run()
{
	results=new int[size];

	/*if(state.subMatrix_Flag)
		subRunCL();
	else*/
		runCL();

}


void SynchronousD2::printSD2Results()
{
	//printD2Results(bufferD2);
}

void SynchronousD2::runCL()
{
	string path;
	char* c;
	char k[]="kernelS2.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,0,2,size,NULL);
	krnl.connect();
	spreadMatrixD2toD1(state.d2,results);
	krnl.loadParameter(results, size, state.borderDim,0.0f, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputSD2-0.txt";
			c=(char*)path.c_str();
			writeOnFileD2(state.d2, c);
		}
	ivllib::Timer t;	
	t.start();
	for(int i=0;i<state.iteration;i++)
	{
		results=krnl.run();
		compactMatrixD1toD2(results,state.d2);
		if (state.save)
		{
			path="outputSD2-"+intToString(i+1)+".txt";
			c=(char*)path.c_str();
			writeOnFileD2(state.d2, c);
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
