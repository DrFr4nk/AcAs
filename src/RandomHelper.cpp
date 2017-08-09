#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "RandomHelper.h"
namespace RandomHelper
{
	double unifRand()
	{
		return rand()/(double)RAND_MAX;    
	}
	int rndBetween(int min,int max)
	{
		return rand()%(max - min+1)+min;
	}
}
