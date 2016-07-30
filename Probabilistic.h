#ifndef _Probabilistic_h_included_
#define _Probabilistic_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "Simulator.h"
using namespace std;

class Probabilistic : protected Simulator{
public:
	float* vec;
	float* sill;
	Probabilistic(char* fileName);
	//Synchronous();
protected:
	void probGenerator01();
	void probGeneratorBtw(int inf, int sup);
};
#endif