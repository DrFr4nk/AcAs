#ifndef _ProbabilisticD1_h_included_
#define _ProbabilisticD1_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
#include "Probabilistic.h"
using namespace std;

class ProbabilisticD1 : protected Probabilistic{
public:
	//int* bufferD1;
	int* results;
	ProbabilisticD1(char* fileName);
	void run();
	void printPD1Results();
protected:

	void runCL();

};
#endif