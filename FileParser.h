#ifndef _FileParser_h_included_
#define _FileParser_h_included_
#include <string>
#include <fstream>
#include <vector>
using namespace std;

namespace FileParser
{
	
	vector<string> readFromFile(char* fileName);
	void writeInFile(char* fileName, vector<string> v);
	
};
#endif