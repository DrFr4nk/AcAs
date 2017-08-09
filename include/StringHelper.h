#ifndef _StringHelper_h_included_
#define _StringHelper_h_included_
#include <string>
#include <vector>
using namespace std;

namespace StringHelper
{
	string getMyLine(vector<string> v, string s, char first, char last);
	string getMyLine(vector<string> v, string s);
	const string strToLower(string s);
	vector<string> vectorToLower(vector<string> vec);
	string myReplace(string s, string f, string r);
	vector<string> stringSplit(string s, char c);
	string between(string s, char first, char last);
	string compression(vector<string> v, string first, char last);
	bool findInString(string s, char c);
	int findPos(string s,char e);
	string intToString(int i);
	int stringToInt(string s);
};
#endif