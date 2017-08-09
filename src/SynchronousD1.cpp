#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "timer.h"
#include "Kernel.h"
#include "StringHelper.h"
#include "SynchronousD1.h"
#include "RandomHelper.h"
using namespace RandomHelper;
using namespace std;
using namespace StringHelper;




SynchronousD1::SynchronousD1(char* fileName) : Synchronous(fileName)
{
}

void SynchronousD1::run()
{
	results=new int[size];
	runCL();
}


void SynchronousD1::runCL()
{
	string path;
	char* c;
	char k[]="kernelS.cl";
	char* ckrnl=k;
	Kernel krnl(ckrnl,rule.kernelRule,0,1,size,NULL);
	krnl.connect();
	krnl.loadParameter(state.d1, size, state.borderDim,0.0f, state.sizeX, state.sizeY, state.sizeZ);
	if (state.save)
		{
			path="outputSD1-0.txt";
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
			path="outputSD1-"+intToString(i+1)+".txt";
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

void SynchronousD1::printSD1Results()
{
	//printD1Results(bufferD1);
}
