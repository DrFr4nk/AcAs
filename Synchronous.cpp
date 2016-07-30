#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "Synchronous.h"
#include "RandomHelper.h"

Synchronous::Synchronous(char* fileName):Simulator(fileName)
{
	

}

//Synchronous::Synchronous():Simulator(){}

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;
