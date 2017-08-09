#ifndef _Simulator_h_included_
#define _Simulator_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "BorderMatrix.h"
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
using namespace std;

class Simulator{
public:
	RuleAnalyzer rule;
	StateGenerator state;
	int size;
	
	double* rand;
	Simulator(char* fileName);
	
	//Simulator();
protected:
	void printD1Results(int* buf);
	void printD2Results(int** buf);
	void printD3Results(int*** buf);
	void initializeDimensions();
	void writeOnFileD1(int* source, char* fileName);
	void writeOnFileD2(int** source, char* fileName);
	void writeOnFileD3(int*** source, char* fileName);
	void spreadMatrixD2toD1(int** source, int* final);
	void spreadMatrixD3toD1(int*** source, int* final);
	void spreadMatrixD2toD1(int** source, int* final,int xMax, int xMin,int yMax,int yMin, int borderDim);
	void compactMatrixD1toD2(int* source, int** final,int xMax, int xMin,int yMax,int yMin, int borderDim);
	void compactMatrixD1toD2(int* src, int** fnl);
	void compactMatrixD1toD3(int* src, int*** fnl);
	char * load_program_source(const char *filename);
	void spreadMatrixD3toD1(int*** source, int* final,int sizeX,int sizeY,int sizeZ);
	void compactMatrixD1toD3(int* source, int*** final, int sizeX,int sizeY, int sizeZ);
	char* kernelReplace(char* source,string toReplace, string newString);
};
#endif