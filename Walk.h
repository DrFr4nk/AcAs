#ifndef _Walk_h_included_
#define _Walk_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "Simulator.h"
using namespace std;

class Walk : protected Simulator{
public:
	Walk(char* fileName);
	void walkTypeGen(int dim,char* walkFileName);
	//Synchronous();
protected:
	void rndWalk(int dim);
	int* wWay;
	void fileWalk(char* walkFileName);
};
#endif