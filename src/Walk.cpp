#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "FileParser.h"
#include "Walk.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace FileParser;
using namespace StringHelper;

int updateX,updateY,updateZ;

Walk::Walk(char* fileName):Simulator(fileName)
{
}

void Walk::rndWalk(int dim)
{
	//wWay=new int[stepNumber];
	//for(int i=0;i<size;i++)
	//	wWay[i]=unifRand()*size;
}

void Walk::fileWalk(char* walkFileName)
{
	vector<string> v=readFromFile(walkFileName);
	wWay=new int[v.size()];
	for(unsigned int i=0;i<v.size();i++)
	{
		wWay[i]=atoi(v[i].c_str());
	}

}

void Walk::walkTypeGen(int dim, char* walkFileName)
{
	if(walkFileName==NULL)
	{
		rndWalk(dim);
	}
	else
	{
		fileWalk(walkFileName);
	}
}
