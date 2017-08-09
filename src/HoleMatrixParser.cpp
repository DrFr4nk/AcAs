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
#include "HoleMatrixParser.h"
#include "VectorQueue.h"
#include "SubMatrix.h"
#include "BorderMatrix.h"
using namespace std;
using namespace StringHelper;

namespace HoleMatrixParser
{
	BorderMatrix matrix2DFinder(int** matrix, int sizeX,int sizeY, int ignValue, int radius)
	{
		BorderMatrix bm;
		VectorQueue vctQ,tmpQ;
		SubMatrix sb;
		sb.radius=radius;
		int xMax,yMax,xMin,yMin;
		vector<SubMatrix> subMatrixVect;
		int i,j,k;
		i=j=k=0;
		while(i<sizeY)
		{
			while(j<sizeX)
			{
				if((matrix[j][i]!= ignValue) && (matrix[j][i]>0))
				{
					while(!vctQ.isEmpty())
						vctQ.pop();
					vctQ.push(j,i,0);

					matrix[j][i]-=2*matrix[j][i];
					tmpQ=neighbour2D(matrix,ignValue, radius,vctQ, sizeX,sizeY);
					xMax=sb.getMax(tmpQ.x);
					yMax=sb.getMax(tmpQ.y);
					xMin=sb.getMin(tmpQ.x);
					yMin=sb.getMin(tmpQ.y);
					bm.push(xMax,xMin,yMax,yMin,0,0);	
					k++;
				}
				++j;
			}
			j=0;
			++i;
		}
		BorderMatrix tmp;
		for(int l=0;l<k;l++)
		{
			tmp.push(bm.xMax.front(),bm.xMin.front(),bm.yMax.front(),bm.yMin.front(),0,0);
			matrixAbs2D(matrix,bm.xMax.front(),bm.xMin.front(),bm.yMax.front(),bm.yMin.front(), 2*radius);
			bm.pop();

		}
		return tmp;
	}

	vector<SubMatrix> matrix3DFinder(int*** matrix, int sizeX,int sizeY, int sizeZ, int ignValue, int radius)
	{
		VectorQueue vctQ,tmpQ;
		SubMatrix sb;
		int xMax,yMax,zMax,xMin,yMin,zMin;
		vector<SubMatrix> subMatrixVect;
		int i,j,k;
		i=j=k=0;
		int subSizeX;
		int subSizeY;
		int subSizeZ;
		while (k<sizeZ)
		{
			while(i<sizeY)
			{
				while(j<sizeX)
				{
					if((matrix[j][i][k]!= ignValue) && (matrix[j][i][k]>0))
					{
						while(!vctQ.isEmpty())
							vctQ.pop();
						vctQ.push(j,i,k);

						matrix[j][i][k]-=2*matrix[j][i][k];
						tmpQ=neighbour3D(matrix,ignValue, radius,vctQ);
						xMax=sb.getMax(tmpQ.x);
						yMax=sb.getMax(tmpQ.y);
						zMax=sb.getMax(tmpQ.z);
						xMin=sb.getMin(tmpQ.x);
						yMin=sb.getMin(tmpQ.y);
						zMin=sb.getMin(tmpQ.z);
						sb.xPos=xMin;
						sb.yPos=yMin;
						sb.zPos=zMin;
						subSizeX=xMax-xMin+1+2*radius;
						subSizeY=yMax-yMin+1+2*radius;
						subSizeZ=zMax-zMin+1+2*radius;
						sb.size=subSizeX*subSizeY*subSizeZ;
						sb.xSize=subSizeX;
						sb.ySize=subSizeY;
						sb.zSize=subSizeZ;
						sb.subMatrixCreation3D(matrix,subSizeX,subSizeY,subSizeZ,xMin,yMin,zMin,tmpQ,ignValue,radius);
						subMatrixVect.push_back(sb);
					}
					++j;
				}
				j=0;
				++i;
			}
			i=0;
			k++;
		}
		return subMatrixVect;
	}

	VectorQueue neighbour2D(int** matrix,int ignValue, int radius, VectorQueue vctQ,int sizeX, int sizeY)
	{
		int xLimitSup,xLimitInf,yLimitSup,yLimitInf;
		VectorQueue tmpQ;
		tmpQ.push(vctQ.x.front(),vctQ.y.front(),0);
		while(!vctQ.isEmpty())
		{
			xLimitSup=vctQ.x.front()+2*radius+1;
			xLimitInf= vctQ.x.front()-2*radius-1;
			if(xLimitInf<1)xLimitInf=1;
			if (xLimitSup>=sizeX-1) xLimitSup=sizeX-1;
			for(int i=xLimitInf;i<=xLimitSup;i++)
			{
				yLimitSup=vctQ.y.front()+2*radius+1;
				yLimitInf= vctQ.y.front()-2*radius-1;
				if(yLimitInf<1) yLimitInf=1;
				yLimitSup=vctQ.y.front()+2*radius;
				if (yLimitSup>=sizeY-1) yLimitSup=sizeY-1;
				for(int j=yLimitInf;j<=yLimitSup;j++)
				{
					if((matrix[i][j]!=ignValue)&&(matrix[i][j]>0))
					{
						vctQ.push(i,j,0);
						tmpQ.push(i,j,0);
						matrix[i][j]-=2*matrix[i][j];
					}
				}
			}
			vctQ.pop();
		}

		return tmpQ;
	}

	int lookAroundD2(int** mat,int x, int y, int radius, int d)
	{
		int count=0;
		for(int i=x-d;i<x+d;i++)
			for(int j=y-d;j<y-d+radius;j++)
				if ((mat[i][j]!=0)&&(mat[i][j]>0))
				{
					count=1;
					mat[i][j]-=2*mat[i][j];
				}
		for(int i=x-d;i<x-d+radius;i++)
			for(int j=y-d+radius;j<y+d;j++)
				if (mat[i][j]!=0)
					if ((mat[i][j]!=0)&&(mat[i][j]>0))
					{
						count++;
						mat[i][j]-=2*mat[i][j];
					}
		for(int i=x+d-radius+1;i<x+d;i++)
			for(int j=y-d+radius;j<y+d;j++)
				if (mat[i][j]!=0) 
					if ((mat[i][j]!=0)&&(mat[i][j]>0))
					{
						count++;
						mat[i][j]-=2*mat[i][j];
					}
		for(int i=x-d+radius;i<=x+d-radius;i++)
			for(int j=y+d-radius+1;j<y+d;j++)
				if ((mat[x][j]!=0)&&(mat[x][j]>0)) 
					if ((mat[i][j]!=0)&&(mat[i][j]>0))
					{
						count++;
						mat[i][j]-=2*mat[i][j];
					}
		if (count!=0) return true;
		return false;
	}
	VectorQueue neighbour3D(int*** matrix,int ignValue, int radius, VectorQueue vctQ)
	{
		VectorQueue tmpQ;
		tmpQ.push(vctQ.x.front(),vctQ.y.front(),vctQ.z.front());
		while(!vctQ.isEmpty())
		{
			for(int k=vctQ.z.front()-radius;k<=vctQ.z.front()+radius;k++)
			{
				for(int i=vctQ.y.front()-radius;i<=vctQ.y.front()+radius;i++)
				{
					for(int j=vctQ.x.front()-radius;j<=vctQ.x.front()+radius;j++)
						if((matrix[j][i][k]!=ignValue)&&(matrix[j][i][k]>0))
						{
							vctQ.push(j,i,k);
							tmpQ.push(j,i,k);
							matrix[j][i][k]-=2*matrix[j][i][k];
						}
				}
			}
			vctQ.pop();
		}

		return tmpQ;
	}

	vector<SubMatrix> order(vector<SubMatrix> v)
	{
		SubMatrix tmp;
		for(int i=0;i<v.size()-1;i++)
			for(int j=i+1;j<v.size();j++)
			{
				if(v[i].size<v[j].size)
				{
					tmp=v[j];
					v[j]=v[i];
					v[i]=tmp;
				}
			}
		return v;
	}

		void matrixAbs2D(int** matrix,int xMax, int xMin ,int yMax,int yMin, int radius)
	{
		for (int i=xMin-radius ;i<xMax+radius;i++)
			for(int j=yMin-radius;j<yMax+radius;j++)
				if(matrix[i][j]<0)
					matrix[i][j]-=2*matrix[i][j];
	}


	int** matrixRebuild2D(vector<SubMatrix> v, int sizeX, int sizeY,int ignValue,int radius)
	{

		v=order(v);
		int** tmp=new int*[sizeX];
		for(int i=0;i<sizeX;i++)
		{
			tmp[i]=new int[sizeY];
			for(int j=0;j<sizeY;j++)
				tmp[i][j]=0;
		}


		for (int l=0;l<v.size();l++)
		{

			for(int i=radius;i<v[l].xSize-radius;i++)
				for(int j=radius;j<v[l].ySize-radius;j++)
				{
					if ((i+v[l].xPos-radius<sizeX)&&(j+v[l].yPos-radius<sizeY))
						if (tmp[i+v[l].xPos-radius][j+v[l].yPos-radius]==ignValue)
							tmp[i+v[l].xPos-radius][j+v[l].yPos-radius]=v[l].matrix2D[i][j]; 
				}
		}
		return tmp;
	}

	int*** matrixRebuild3D(vector<SubMatrix> v, int sizeX, int sizeY,int sizeZ,int radius)
	{

		v=order(v);
		int*** tmp=new int**[sizeX];
		for(int i=0;i<sizeX;i++)
		{
			tmp[i]=new int*[sizeY];
			for(int j=0;j<sizeY;j++)
			{
				tmp[i][j]=new int[sizeZ];
				for(int k=0;k<sizeZ;k++)
					tmp[i][j][k]=0;
			}
		}


		for (int l=0;l<v.size();l++)
		{

			for(int i=radius;i<v[l].xSize-radius;i++)
				for(int j=radius;j<v[l].ySize-radius;j++)
					for(int k=radius;k<v[l].zSize-radius;k++)
						tmp[i+v[l].xPos-radius][j+v[l].yPos-radius][k+v[l].zPos-radius]=v[l].matrix3D[i][j][k]; 
		}
		return tmp;
	}
	
}
