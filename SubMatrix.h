#ifndef _SubMatrix_h_included_
#define _SubMatrix_h_included_
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "VectorQueue.h"
using namespace std;

class SubMatrix
{
public:
	int** matrix2D;
	int*** matrix3D;
	int xPos,yPos,zPos,size,xSize,ySize,zSize, radius;
	SubMatrix();
	void matrixAbs3D();
	int getMax(queue<int> v);
	int getMin(queue<int> v);
	void subMatrixCreation3D(int*** mtr,int sizeX,int sizeY,int sizeZ,int xMin,int yMin, int zMin,VectorQueue point,int ignValue, int radius);
	void subMatrixCreation2D(int** mtr,int xMin,int yMin,VectorQueue point,int ignValue);
	void matrixAbs2D();
	
};
#endif
