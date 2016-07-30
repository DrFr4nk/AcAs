#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <CL/opencl.h>
#include <sstream>
#include <sys/stat.h>
#include "Kernel.h"
#include "StringHelper.h"
#include "ProbabilisticD3.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

ProbabilisticD3::ProbabilisticD3(char* fileName) : Probabilistic(fileName)
{
}

void ProbabilisticD3::run()
{
	results=new int[size];

	runCL();

}

void ProbabilisticD3::printPD3Results()
{
	//printD3Results(bufferD3);
}

void ProbabilisticD3::runCL()
{
	string path;
	char* c;
	char k[]="kernelP3.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,1,3,size,NULL);
	krnl.connect();
	spreadMatrixD3toD1(state.d3,results);
	krnl.loadParameter(results, size, state.borderDim,state.probability, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputPD3-0.txt";
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
			path="outputPD3-"+intToString(i+1)+".txt";
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


