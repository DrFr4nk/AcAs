__kernel void 
run(__global int *a,
	__global int *answer,
	int brdDim,
	int x,
	int y,
	int z
	)
{

	int gid = get_global_id(0);
	int posX=gid% x;
	int posY= (gid/ x) % y;
	int posZ= (gid/  (x * y)) % z;
	if((posX>= brdDim)&&(posX< x- brdDim)&&(posY>= brdDim)&&(posY< y - brdDim)&&(posZ>= brdDim)&&(posZ< z - brdDim))
	//REPLACE//
	else
		answer[gid]=a[gid];
}
