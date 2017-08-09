#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <cctype>
#include <algorithm>
#include <functional>
#include <ctime>
#include <time.h>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include "StringHelper.h"
#include "FileParser.h"
#include "RuleAnalyzer.h"
using namespace std;
using namespace FileParser;
using namespace StringHelper;

RuleAnalyzer::RuleAnalyzer(char* fileName, int mod, int dim)
{
	vector<string> vec=readFromFile(fileName);
	rule=stringSplit(getMyLine(vec,"R=",'"','"'),' ');
	executionComprehension();
	ruleComprehension(mod,dim);
}
RuleAnalyzer::RuleAnalyzer(){}

void RuleAnalyzer::ruleComprehension(int rndSupLim, int dim)
{
	for (int l=0;l<rule.size();l++)	
	{
		switch(dim)
		{
			case(1):
				kernelRule+=comprehensionD1(rule[l],rndSupLim+1)+" ";
				break;
			case(2):
				kernelRule+=comprehensionD2(rule[l],rndSupLim+1)+" ";
				break;
			case(3):
				kernelRule+=comprehensionD3(rule[l],rndSupLim+1)+" ";
				break;
		}
	}
}


string RuleAnalyzer::comprehensionD1(string s, int mod)
{
	size_t found;
	string str="==";
	found=s.find(str);
	//if (found!=string::npos)
		s=myReplace(s,"x","gid");
	/*else
	{
		vector<string> v=stringSplit(s,'=');
		vector<string> app=stringSplit(v[0],'[');
		v[0]=myReplace(v[0],app[0],"answer");
		app[1]=between(v[0],'[',']');
		v[0]=myReplace(v[0],app[1],"gid");
		v[1]=myReplace(v[1],app[1],"gid");
		v[1]=myReplace(v[1],app[0],"a");
		s=v[0]+"="+v[1];
	}*/
	return s;
}
string RuleAnalyzer::comprehensionD2(string s, int mod)
{
	/*vector<string> v=stringSplit(s,'=');
	string s0=s.substr(0,findPos(s,'['));
	string s1=between(v[0],'[',']');
	string s2;
	int i=	findPos(v[0],'[');
	s2=v[0].substr(i+1,v[0].size()-1);
	s2=between(s2,'[',']');
	v[0]=myReplace(v[0],s0,"answer");
	v[0]=myReplace(v[0],s1,"xPos");
	v[0]=myReplace(v[0],s2,"yPos");
	v[1]=myReplace(v[1],s0,"a");
	v[1]=myReplace(v[1],s1,"xPos");
	v[1]=myReplace(v[1],s2,"yPos");*/
	string final=ruleD2revision(s);
	return final;
}

//double RuleAnalyzer::unifRand()
//{
//	double fd=(rand()*1)/(double)RAND_MAX;    
//}

string RuleAnalyzer::comprehensionD3(string s, int mod)
{
	//vector<string> v=stringSplit(s,'=');
	//string s0=s.substr(0,findPos(s,'['));
	//string s1=between(v[0],'[',']');
	//string s2,s3;
	//int i=	findPos(v[0],'[');
	//s2=v[0].substr(i+1,v[0].size()-1);
	//
	//
	//s2=between(s2,'[',']');
	//i=findPos(v[0],*s2.c_str());
	//s3=v[0].substr(i+1,v[0].size()-1);
	//s3=between(s3,'[',']');
	//v[0]=myReplace(v[0],s0,"answer");
	//v[0]=myReplace(v[0],s1,"xPos");
	//v[0]=myReplace(v[0],s2,"yPos");
	//v[0]=myReplace(v[0],s3,"zPos");
	//v[1]=myReplace(v[1],s0,"a");
	//v[1]=myReplace(v[1],s1,"xPos");
	//v[1]=myReplace(v[1],s2,"yPos");
	//v[1]=myReplace(v[1],s3,"zPos");
	string final=ruleD3revision(s);
	return final;
}

string RuleAnalyzer::ruleD2revision(string s)
{
	vector<string> v0;
	string tmp,final;
	int i=0;
	int j=0;
	while (i<(int)s.size())
	{
		if(s[i]=='[')
			j++;
		if (j!=0)
			tmp+=s[i];
		else
			final+=s[i];

		if(s[i]==']')
			j++;
		if (j==4)
		{
			j=0;
			final+=gidCalc2D(tmp);
			tmp="";
		}
		i++;
	}
	return final;
}

string RuleAnalyzer::ruleD3revision(string s)
{
	vector<string> v0;
	string tmp,final;
	int i=0;
	int j=0;
	while (i<(int)s.size())
	{
		if(s[i]=='[')
			j++;
		if (j!=0)
			tmp+=s[i];
		else
			final+=s[i];

		if(s[i]==']')
			j++;
		if (j==6)
		{
			j=0;
			final+=gidCalc3D(tmp);
			tmp="";
		}
		i++;
	}
	return final;
}

string RuleAnalyzer::gidCalc2D(string s)
{
	string final="[gid";
	//int pos;
	size_t found;
	string tmp=between(s,'[',']');
	string strPlus="+";
	found=tmp.find(strPlus);
	if (found!=string::npos)
				final+=tmp.substr(found);
	string strMinus="-";
	found=tmp.find(strMinus);
	if (found!=string::npos)
				final+=tmp.substr(found);
	found=s.find("]");
	tmp=s.substr(found+1);
	tmp=between(tmp,'[',']');
	found=tmp.find(strPlus);
	if (found!=string::npos)
	{
				final+=tmp.substr(found)+"*(x)]";
	}
	else
	{
		found=tmp.find(strMinus);
		if (found!=string::npos)
			final+=tmp.substr(found)+"*(x)]";
		else
			final+="]";
	}
	return final;
}

string RuleAnalyzer::gidCalc3D(string s)
{
	string final="[gid";
	size_t found;
	string tmp=between(s,'[',']');
	string strPlus="+";
	found=tmp.find(strPlus);
	if (found!=string::npos)
				final+=tmp.substr(found);
	string strMinus="-";
	found=tmp.find(strMinus);
	if (found!=string::npos)
				final+=tmp.substr(found);
	found=s.find("]");

	tmp=s.substr(found+1);
	tmp=between(tmp,'[',']');
	found=tmp.find(strPlus);
	if (found!=string::npos)
		final+=tmp.substr(found)+"*(x)";
	found=tmp.find(strMinus);
	if (found!=string::npos)
		final+=tmp.substr(found)+"*(x)";
	found=s.find("y");
	tmp=s.substr(found);
	tmp=between(tmp,'[',']');
	found=tmp.find(strPlus);
	if (found!=string::npos)
	{
		final+=tmp.substr(found)+"*(y*x)]";
	}
	else
	{
		found=tmp.find(strMinus);
		if (found!=string::npos)
			final+=tmp.substr(found)+"*(x*y)]";
		else
			final+="]";
	}
	return final;
}

void RuleAnalyzer::executionComprehension()
{
	
}

