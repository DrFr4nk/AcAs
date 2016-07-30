#ifndef _SynchronousD2_h_included_
#define _SynchronousD2_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Synchronous.h"
using namespace std;

class SynchronousD2 : protected Synchronous{
public:
	SynchronousD2(char* fileName);
	void run();
	//~SynchronousD2();
	void printSD2Results();
protected:
	int* results;
	void subMatrix_run();
	void runCL();
};
#endif
