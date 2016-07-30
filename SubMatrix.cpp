#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include <queue>
#include <sys/stat.h>
#include "StringHelper.h"
#include "SubMatrix.h"
#include "VectorQueue.h"
using namespace std;
using namespace StringHelper;


SubMatrix::SubMatrix()
	{
	}
	int SubMatrix::getMax(queue<int> v)
	{
		int i=-1;
		while(!v.empty())
		{
			if(v.front()>i)
				i=v.front();
			v.pop();
		}
		return i;
	}
	int SubMatrix::getMin(queue<int> v)
	{
		int i=2147483647;
		while(!v.empty())
		{
			if(v.front()<i)
				i=v.front();
			v.pop();
		}
		return i;
	}

	void SubMatrix::subMatrixCreation2D(int** mtr,int xMin,int yMin,VectorQueue point,int ignValue)
	{

		int** sMatrix=new int* [xSize];
		for(int i=0;i<xSize;i++)
		{
			sMatrix[i]=new int[ySize];
			for(int j=0;j<ySize;j++)
				sMatrix[i][j]=ignValue;
		}
		while(!point.isEmpty())
		{
			sMatrix[point.x.front()-xPos+2*radius][point.y.front()-yPos+2*radius]=mtr[point.x.front()][point.y.front()];
			point.pop();
		}
		matrix2D=sMatrix;
		matrixAbs2D();
	}

	void SubMatrix::subMatrixCreation3D(int*** mtr,int sizeX,int sizeY,int sizeZ,int xMin,int yMin, int zMin,VectorQueue point,int ignValue, int radius)
	{

		int*** sMatrix=new int**[sizeX];
		for(int i=0;i<sizeX;i++)
		{
			sMatrix[i]=new int*[sizeY];
			for(int j=0;j<sizeY;j++)
			{
				sMatrix[i][j]=new int[sizeZ];
				for(int k=0;k<sizeZ;k++)
					sMatrix[i][j][k]=ignValue;
			}
		}
		while(!point.isEmpty())
		{
			sMatrix[point.x.front()-xMin+radius][point.y.front()-yMin+radius][point.z.front()-zMin+radius]=mtr[point.x.front()][point.y.front()][point.z.front()];
			point.pop();
		}
		matrix3D=sMatrix;
		matrixAbs3D();
	}

	void SubMatrix::matrixAbs2D()
	{
		for (int i=0;i<xSize;i++)
			for(int j=0;j<ySize;j++)
				if(matrix2D[i][j]<0)
					matrix2D[i][j]-=2*matrix2D[i][j];
	}

	void SubMatrix::matrixAbs3D()
	{
		for (int i=0;i<xSize;i++)
			for(int j=0;j<ySize;j++)
				for(int k=0;k<zSize;k++)
					if(matrix3D[i][j][k]<0)
						matrix3D[i][j][k]-=2*matrix3D[i][j][k];
	}
