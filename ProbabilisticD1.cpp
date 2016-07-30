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
#include "ProbabilisticD1.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

ProbabilisticD1::ProbabilisticD1(char* fileName) : Probabilistic(fileName)
{
}

void ProbabilisticD1::run()
{
	size=state.sizeX;
	results=new int[size];

	//bufferD1=new int[size];
	runCL();

}

void ProbabilisticD1::printPD1Results()
{
	//printD1Results(bufferD1);
}

void ProbabilisticD1::runCL()
{
	string path;
	char* c;
	char k[]="kernelP.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,1,1,size,NULL);
	krnl.connect();
	krnl.loadParameter(state.d1, size, state.borderDim,state.probability, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputPD1-0.txt";
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
			path="outputPD1-"+intToString(i+1)+".txt";
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

