__kernel void 
run(__global int *a,
	__global int *answer,
	__global float *prob,
	float sill,
	int brdDim,
	int x
	)
{
	int gid = get_global_id(0);
	if((gid>=brdDim)&&(gid<((x)-(brdDim)))&&(prob[gid]<=sill))
	{
			//REPLACE//
	}
	else
	{
		answer[gid]=a[gid];
	}
}
