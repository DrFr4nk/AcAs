#ifndef _WalkD1_h_included_
#define _WalkD1_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Walk.h"
using namespace std;

class WalkD1 : protected Walk{
public:
	int* bufferD1;
	int* results;
	int** pathIndex;
	WalkD1(char* fileName);
	void run();
	void printWD1Results();
protected:
	void loadPath();
	void runCL();

};
#endif