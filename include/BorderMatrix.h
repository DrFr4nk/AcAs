#ifndef _BorderMatrix_h_included_
#define _BorderMatrix_h_included_
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "Simulator.h"
using namespace std;

class BorderMatrix{
public:
	BorderMatrix();
	queue<int> xMax;
	queue<int> xMin;
	queue<int> yMax;
	queue<int> yMin;
	queue<int> zMax;
	queue<int> zMin;
	int count;
	void push(int vxMax,int vxMin,int vyMax,int vyMin,int vzMax,int vzMin);
	void pop();
	bool isEmpty();
};
#endif