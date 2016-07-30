#ifndef _SynchronousD3_h_included_
#define _SynchronousD3_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Synchronous.h"
using namespace std;

class SynchronousD3 : protected Synchronous{
public:
	int* results;
	SynchronousD3(char* fileName);
	void run();
	void printSD3Results();
protected:
	void runCL();

};
#endif
