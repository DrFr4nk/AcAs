__kernel void 
run(__global int *a,
	__global int *answer,
	__global float *prob,
	float sill,
	int brdDim,
	int x,
	int y
	)
{
	int gid = get_global_id(0);
	int posX=gid% x;
	int posY= (gid/ x) % y;
	if((posX>= brdDim)&&(posX< x- brdDim)&&(posY>= brdDim)&&(posY< y - brdDim)&&(prob[gid]<sill))
	{
				//REPLACE//
	}
	else
		{
			answer[gid]=a[gid];
		}
}
