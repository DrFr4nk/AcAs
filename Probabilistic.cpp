#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "Probabilistic.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

Probabilistic::Probabilistic(char* fileName):Simulator(fileName)
{
}

void Probabilistic::probGenerator01()
{
	for(int i=0;i<size;i++)
		vec[i]=unifRand();
}

void Probabilistic::probGeneratorBtw(int inf, int sup)
{
	for(int i=0;i<size;i++)
		vec[i]=rndBetween(inf,sup);
}
