#ifndef _ProbabilisticD3_h_included_
#define _ProbabilisticD3_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Probabilistic.h"
using namespace std;

class ProbabilisticD3 : protected Probabilistic{
public:
	int* results;
	ProbabilisticD3(char* fileName);
	void run();
	void printPD3Results();
protected:

	void runCL();

};
#endif