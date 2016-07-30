#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "Kernel.h"
#include "StringHelper.h"
#include "ProbabilisticD2.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

ProbabilisticD2::ProbabilisticD2(char* fileName) : Probabilistic(fileName)
{
}

void ProbabilisticD2::run()
{

	results=new int[size];


	runCL();
}

void ProbabilisticD2::printPD2Results()
{
	//printD2Results(bufferD2);
}


void ProbabilisticD2::runCL()
{
	string path;
	char* c;
	char k[]="kernelP2.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,1,2,size,NULL);
	krnl.connect();
	spreadMatrixD2toD1(state.d2,results);
	krnl.loadParameter(results, size, state.borderDim,state.probability, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputPD2-0.txt";
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
			path="outputPD2-"+intToString(i+1)+".txt";
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
