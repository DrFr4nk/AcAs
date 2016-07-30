#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <queue>
#include <sys/stat.h>
#include "StringHelper.h"
#include "VectorQueue.h"
#include "RandomHelper.h"

using namespace RandomHelper;
using namespace std;
using namespace StringHelper;

VectorQueue::VectorQueue()
{
	count=0;
}

void VectorQueue::push(int vx,int vy, int vz)
{
	x.push(vx);
	y.push(vy);
	z.push(vz);
	count++;
}

void VectorQueue::front(int* vx,int* vy, int* vz)
{
	*vx=x.front();
	*vy=y.front();
	*vz=z.front();
}

void VectorQueue::pop()
{
	x.pop();
	y.pop();
	z.pop();
	count--;
}

bool VectorQueue::isEmpty()
{
	if (count==0)
		return true;
	return false;
}
