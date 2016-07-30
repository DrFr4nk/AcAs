__kernel void 
run(__global int *a,
	__global int *answer,
	int brdDim,
	int x
	)
{
	int gid = get_global_id(0);
	if((gid>=brdDim)&&(gid<(x-brdDim)))
	{
		//REPLACE//
	}
	else
	{
		answer[gid]=a[gid];
	}
}
