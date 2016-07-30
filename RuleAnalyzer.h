#ifndef _RuleAnalyzer_h_included_
#define _RuleAnalyzer_h_included_
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class RuleAnalyzer
{
public:
	vector<string> rule;
	string kernelRule;
	double* rand;
	
	int executionType;
	RuleAnalyzer(char* fileName, int mod, int dim);
	RuleAnalyzer();
	
private:
	void ruleComprehension(int rndSupLim,int dim);
	
	string ruleD2revision(string s);
	string ruleD3revision(string s);
	string gidCalc2D(string s);
	string gidCalc3D(string s);
	string comprehensionD1(string s, int mod);
	string comprehensionD2(string s, int mod);
	string comprehensionD3(string s, int mod);
	void executionComprehension();
};
#endif