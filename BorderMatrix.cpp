#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <queue>
#include <sys/stat.h>
#include "BorderMatrix.h"

using namespace std;

BorderMatrix::BorderMatrix()
{
	count=0;
}

void BorderMatrix::push(int vxMax,int vxMin,int vyMax,int vyMin,int vzMax,int vzMin)
{
	xMax.push(vxMax);
	xMin.push(vxMin);
	yMax.push(vyMax);
	yMin.push(vyMin);
	zMax.push(vzMax);
	zMin.push(vzMin);
	count++;
}

void BorderMatrix::pop()
{
	if(count>0)
	{
		xMax.pop();
		xMin.pop();
		yMax.pop();
		yMin.pop();
		zMax.pop();
		zMin.pop();
		count--;
	}
}

bool BorderMatrix::isEmpty()
{
	if (count==0)
		return true;
	return false;
}
