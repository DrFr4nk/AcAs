#ifndef _SynchronousD1_h_included_
#define _SynchronousD1_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Synchronous.h"
using namespace std;

class SynchronousD1 : protected Synchronous{
public:
	int* results;
	SynchronousD1(char* fileName);
	void run();
	void printSD1Results();
protected:

	void runCL();

};
#endif