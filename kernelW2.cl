__kernel void 
run(__global int *a,
	__global int *answer,
	int brdDim,
	int sizeX,
	int x,
	int y
	)
{
	int gid = get_global_id(0);
	int pos=(sizeX * (y + (brdDim)))+ (x) + (brdDim);
	if(gid==pos)
		//REPLACE//	
	else
		answer[gid]=a[gid];
}
