__kernel void 
run(__global int *a,
	__global int *answer,
	int brdDim,
	int sizeX,
	int sizeY,
	int x,
	int y,
	int z
	)
{

	int gid = get_global_id(0);
	int pos=(sizeX * (sizeY) * (z + (brdDim)))+(sizeX * (y + (brdDim)))+ (x) + (brdDim);
	if(gid==pos)
		//REPLACE//	
	else
		answer[gid]=a[gid];
}
