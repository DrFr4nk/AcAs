#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "StateGenerator.h"
#include "SynchronousD2.h"
#include "SynchronousD1.h"
#include "SynchronousD3.h"
#include "ProbabilisticD1.h"
#include "ProbabilisticD2.h"
#include "ProbabilisticD3.h"
#include "WalkD1.h"
#include "WalkD2.h"
#include "WalkD3.h"
#include <sys/stat.h>
#include "FileParser.h"
#include "timer.h"
#include "StringHelper.h"
#include "InterfaceAC.h"
using namespace std;
using namespace StringHelper;
using namespace FileParser;

namespace InterfaceAC
{
	void runSimulator(char* fileName)
	{
		int i=0;
		vector<string> v=readFromFile(fileName);
		vector<string> tmp=stringSplit(v[0],' ');
		cout<<"execution of a cellular automata simulator "<<tmp[0]<<" of dimension "<<tmp[1]<<endl;
		ivllib::Timer t;	
		t.start();
		for(int i=0;i<v.size();i++)
			if (v[i][0]=='S')
				cout<<v[i]<<endl;
		if(tmp[0]=="synchronous")
		{
			if(stringToInt(tmp[1])==1)
			{
				SynchronousD1 simSD1(fileName);
				simSD1.run();
				i=1;
			}
			if(stringToInt(tmp[1])==2)
			{
				SynchronousD2 simSD2(fileName);
				simSD2.run();
				i=1;
			}
			if(stringToInt(tmp[1])==3)
			{
				SynchronousD3 simSD3(fileName);
				simSD3.run();
				i=1;
			}
		}
		if(tmp[0]=="probabilistic")
		{
			if(stringToInt(tmp[1])==1)
			{
				ProbabilisticD1 simPD1(fileName);
				simPD1.run();
				i=1;
			}
			if(stringToInt(tmp[1])==2)
			{
				ProbabilisticD2 simPD2(fileName);
				simPD2.run();
				i=1;
			}
			if(stringToInt(tmp[1])==3)
			{
				ProbabilisticD3 simPD3(fileName);
				simPD3.run();
				i=1;
			}
		}
		if(tmp[0]=="walk")
		{
			if(stringToInt(tmp[1])==1)
			{
				WalkD1 simWD1(fileName);
				simWD1.run();
				i=1;
			}
			if(stringToInt(tmp[1])==2)
			{
				WalkD2 simWD2(fileName);
				simWD2.run();
				i=1;
			}
			if(stringToInt(tmp[1])==3)
			{
				WalkD3 simWD3(fileName);
				simWD3.run();
				i=1;
			}
		}
		t.stop();
		if (t.getElapsedTime()>60)
		{
			int min=t.getElapsedTime()/60;
			double sec=t.getElapsedTime()-min*60;
			printf("Tempo esecuzione Totale: %d minuti %f secondi\n", min,sec);
		}
		else
			printf("Tempo esecuzione Totale: %f secondi\n", t.getElapsedTime());
		if(i==0) cout<<"Errore nell'intestazione";
	}
}
