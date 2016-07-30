#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "FileParser.h"
using namespace std;
using namespace StringHelper;

namespace FileParser
{
	vector<string> readFromFile(char* fileName)
	{
		string str;
		ifstream in(fileName);
		vector<string> v;
		while ( getline(in,str))
			v.push_back(str);
		string s;
		for(int i=0;i<(int)v.size();i++)
			s=v[i];
		return v;
	}
	void writeInFile(char* fileName,vector<string> v)
	{
		ofstream myfile;
		string s ="Output/"+string(fileName);
		myfile.open (s.c_str());
		for(int i=0;i<v.size();i++)
		{
			myfile << v[i]+"\n";
		}
		myfile.close();
	}



	
}
