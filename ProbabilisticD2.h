#ifndef _ProbabilisticD2_h_included_
#define _ProbabilisticD2_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Probabilistic.h"
using namespace std;

class ProbabilisticD2 : protected Probabilistic{
public:
	int* results;
	ProbabilisticD2(char* fileName);
	void run();
	void printPD2Results();
protected:

	void runCL();

};
#endif