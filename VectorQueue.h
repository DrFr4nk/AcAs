#ifndef _VectorQueue_h_included_
#define _VectorQueue_h_included_
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "Simulator.h"
using namespace std;

class VectorQueue{
public:
	queue<int> x;
	queue<int> y;
	queue<int> z;
	int count;
	void push(int vx,int vy, int vz);
	void front(int* vx,int* vy, int* vz);
	void pop();
	VectorQueue();
	bool isEmpty();
};
#endif