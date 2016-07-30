#ifndef _Synchronous_h_included_
#define _Synchronous_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "Simulator.h"
using namespace std;

class Synchronous : protected Simulator{
public:
	Synchronous(char* fileName);
	//Synchronous();
};
#endif
