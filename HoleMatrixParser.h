#ifndef _HoleMatrixParser_h_included_
#define _HoleMatrixParser_h_included_
#include <string>
#include <fstream>
#include "BorderMatrix.h"
#include "SubMatrix.h"
#include <vector>

#include "VectorQueue.h"
using namespace std;

namespace HoleMatrixParser
{
	void matrixAbs2D(int** matrix,int xMax,int xMin,int yMax, int yMin,int radius);
	int lookAroundD2(int** mat,int x, int y, int radius,int d);
	BorderMatrix matrix2DFinder(int** matrix, int sizeX,int sizeY, int ignValue, int radius);
	VectorQueue neighbour2D(int** matrix,int ignValue, int radius, VectorQueue vctQ, int sizeX, int sizeY);
	vector<SubMatrix> matrixRebuild2D(vector<int**> v,VectorQueue pos);
	int** matrixRebuild2D(vector<SubMatrix> v, int sizeX, int sizeY,int ignValue,int radius);
	vector<SubMatrix> order(vector<SubMatrix> v);
	int*** matrixRebuild3D(vector<SubMatrix> v, int sizeX, int sizeY,int sizeZ,int radius);
	VectorQueue neighbour3D(int*** matrix,int ignValue, int radius, VectorQueue vctQ);
	vector<SubMatrix> matrix3DFinder(int*** matrix, int sizeX,int sizeY, int sizeZ, int ignValue, int radius);
};
#endif