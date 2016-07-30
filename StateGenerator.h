#ifndef _StateGenerator_h_included_
#define _StateGenerator_h_included_
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class StateGenerator
{
public:
	int stateType;
	int dimension;
	char* stateFileName;
	char* walkPath;
	float probability;
	int iteration;
	int sizeX,sizeY,sizeZ;
	int borderVal;
	int borderDim;
	int* d1;
	int** d2;
	int*** d3;
	bool save;
	bool subMatrix_Flag;
	string breakString;
	int rndSupLim,rndInfLim;
	vector<string> state;
	StateGenerator(char* fileName);
	StateGenerator();
private:
	float extractProbability(string s);
	void borderGenerator(int val,int dim);
	int extractDimension ();
	void stateRndGen();
	void stateFileLoad();
	int stateTypology();
	void stateData();
};
#endif