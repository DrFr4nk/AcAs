#ifndef _WalkD3_h_included_
#define _WalkD3_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Walk.h"
using namespace std;

class WalkD3 : protected Walk{
public:
	int* results;
	int** pathIndex;
	WalkD3(char* fileName);
	void run();
	void printWD1Results();
protected:
	void loadPath();
	void runCL();

};
#endif