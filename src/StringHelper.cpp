#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "StringHelper.h"
using namespace std;
namespace StringHelper
{
	vector<string> stringSplit(string s, char c)
	{
		string buf; // Have a buffer string
		stringstream ss(s); // Insert the string into a stream
		vector<string> tokens; // Create vector to hold our words
		while(getline(ss, buf, c))
		{
			tokens.push_back(buf);
		}
		return tokens;
	}

	string myReplace(string s, string f, string r)
	{
		string b=s;
		string app;
		size_t found;
		found=s.find(f);
		while (found!=string::npos)
		{
			b=b.substr(0,(int)found)+r+b.substr((int)found+f.length(),b.length());
			found=b.find(f);
		}
		return b;
	}

	string between(string s, char first, char last)
	{
		int j=0;
		string b;
		for(unsigned int i=0; i<s.size();i++)
			if (s[i]==first)
			{
				j=i+1;
				while(s[j]!=last)
					b=b+s[j++];
				break;
			}
		return b;
	}

	string intToString(int i)
	{
		stringstream ss;
		ss<<i;
		return ss.str();
	}

	int stringToInt(string s)
	{
		int number;
		istringstream ss(s);
		ss >> number;
		return number;
	}
	const string strToLower(string s)
	{
	  //transform(s.begin(), s.end(), s.begin(),ptr_fun(tolower));
	  return s;
	}

	string getMyLine(vector<string> v, string s)
	{
		string tmp;
		for(int i=0;i<(int)v.size();i++)
		{
			if(v[i].substr(0,2)==s)
			{
				tmp=compression(v,s,'}');
				tmp=between(tmp,'{','}');
			}
		}
		//cout<<"The "<<s[0]<<" is: "<<tmp<<endl;
		assert(!(tmp==""));
		return tmp;
	}

	string getMyLine(vector<string> v, string s, char first, char last)
	{
		string tmp;
		for(int i=0;i<(int)v.size();i++)
		{
			if(v[i].substr(0,2)==s)
			{
				tmp=compression(v,s,last);
				tmp=between(tmp,first,last);
			}
		}
		//cout<<"The "<<s[0]<<" is: "<<tmp<<endl;
		assert(!(tmp==""));
		return tmp;
	}

	string compression(vector<string> v, string first, char last)
	{
		string s;
		unsigned int i=0;
		int j=0;
		while(i<v.size())
		{
			if (v[i].substr(0,2)==first)
			{
				s+=v[i]+' ';
				i++;
				break;
			}
			i++;
		}
		
		while (i<v.size())
		{
			if (!findInString(v[i],last))
			{
				s+=v[i]+' ';
			}
			else
			{
				s+=v[i];
				return s;
			}
			i++;
		}
		return s;
	}


	bool findInString(string s, char c)
	{
		for(unsigned int i=0;i<s.size();i++)
			if (s[i]==c)
				return true;
		return false;
	}
	vector<string> vectorToLower(vector<string> vec)
	{
		for(unsigned int i=0; i<vec.size();i++)
		{
			vec[i]=strToLower(vec[i]);
		}
		return vec;
	}
	int findPos(string s,char e)
{
	for(unsigned int i=0; i<s.size();i++)
	{
			if (s[i]==e)
			{
				return i;
			}
	}
	return -1;

}

}
