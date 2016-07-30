#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <CL/opencl.h>
#include <sys/stat.h>
#include <sstream>
#include <cassert>
#include <string.h>
#include "timer.h"
#include "StringHelper.h"
#include "Kernel.h"
#include "RandomHelper.h"
#include "Kernel.h"
using namespace StringHelper;
using namespace RandomHelper;
using namespace std;

Kernel::Kernel(char* fileName, string rle, int tpe, int sttDim,int sze, int** pthIndex)
{
	cpu = NULL;
	device = NULL;
	err = 0;
	returned_size = 0;
	asynCount=0;
	count=0;
	clSelectedPlatformID = NULL;
	kernelName=fileName;
	rule=rle;
	type=tpe;
	stateDim=sttDim;
	size=sze;
	pathIndex=pthIndex;
}

void Kernel::connect()
{

	//vendor_name= new cl_char[1024] {0};
	assert(err == CL_SUCCESS);
	//get the number of available platforms
	clGetPlatformIDs(0, NULL, &numPlatforms);
	//alloc memory so we can get the whole list
	clSelectedPlatformID = (cl_platform_id*)malloc(sizeof(cl_platform_id)*numPlatforms);
	//get the list of available platforms
	err = clGetPlatformIDs(numPlatforms, clSelectedPlatformID, NULL);
	// Find the CPU CL device, as a fallback
	err = clGetDeviceIDs(*clSelectedPlatformID, CL_DEVICE_TYPE_ALL, 0, NULL, &ciDeviceCount);
	assert(err == CL_SUCCESS);
	// Find the GPU CL device, this is what we really want
	// If there is no GPU device is CL capable, fall back to CPU
	err = clGetDeviceIDs(*clSelectedPlatformID, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != CL_SUCCESS) err = clGetDeviceIDs(*clSelectedPlatformID, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
	assert(device);

	// Get some information about the returned device
	err = clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor_name), 
						  vendor_name, &returned_size);
	err |= clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(device_name), 
						  device_name, &returned_size);
	assert(err == CL_SUCCESS);
	printf("Connecting to %s %s...\n", vendor_name, device_name);

	// Now create a context to perform our calculation with the 
	// specified device 
	context = clCreateContext(0, 1, &device, NULL, NULL, &err);
	assert(err == CL_SUCCESS);
	
	// And also a command queue for the context
	cmd_queue = clCreateCommandQueue(context, device, 0, NULL);

	// Load the program source from disk
	// The kernel/program is the project directory and in Xcode the executable
	// is set to launch from that directory hence we use a relative path
	char *program_source = load_program_source(kernelName);
	program_source=kernelReplace(program_source, "//REPLACE//",rule);
	program[0] = clCreateProgramWithSource(context, 1, (const char**)&program_source,
										   NULL, &err);
	assert(err == CL_SUCCESS);
	
	err = clBuildProgram(program[0], 0, NULL, NULL, NULL, NULL);

	assert(err == CL_SUCCESS);
	
	// Now create the kernel "objects" that we want to use in the example file 
	kernel[0] = clCreateKernel(program[0], "run", &err);

}

void Kernel::loadParameter(int * initialState, int dimension, int borderDim,float sill, int sizeX, int sizeY, int sizeZ)
{

	buffer_size = sizeof(int) * size;
	results=new int[size];
	global_work_size=size;
	// Input array initialState
	initialState_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, buffer_size, NULL, NULL);
	err = clEnqueueWriteBuffer(cmd_queue, initialState_mem, CL_TRUE, 0, buffer_size,
							   (void*)initialState, 0, NULL, NULL);
	
	// Results array
	ans_mem	= clCreateBuffer(context, CL_MEM_READ_WRITE, buffer_size, NULL, NULL);
	
	// Get all of the stuff written and allocated 
	clFinish(cmd_queue);

	// Now setup the arguments to our kernel
	err  = clSetKernelArg(kernel[0],  count++, sizeof(cl_mem), &initialState_mem);
	err |= clSetKernelArg(kernel[0],  count++, sizeof(cl_mem), &ans_mem);
	if (type==1)
	{
		vec=new float[size];
		for(int i=0;i<size;i++)
			vec[i]=(float)unifRand();
		prob_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * size, NULL, NULL);
		err = clEnqueueWriteBuffer(cmd_queue, prob_mem, CL_TRUE, 0, sizeof(float) * size,(void*)vec, 0, NULL, NULL);
		prob_pos=count;
		err |= clSetKernelArg(kernel[0],  count++, sizeof(cl_mem), &prob_mem);
		err |= clSetKernelArg(kernel[0],  count++, sizeof(float), &sill);
	}
	err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &borderDim);
	if (type==2)
	{
		if(stateDim>1) 
		{
			err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &sizeX);
		}
		if(stateDim>2) 
		{
			err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &sizeY);
		}
	}
	else
	{
		err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &sizeX);
		if(stateDim>1) 
			err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &sizeY);
		if(stateDim>2) 
			err |= clSetKernelArg(kernel[0],  count++, sizeof(int), &sizeZ);
	}
	assert(err == CL_SUCCESS);

}


int* Kernel::run()
{

	if (type==2)
	{
		if (stateDim==1)
			err |= clSetKernelArg(kernel[0],  count, sizeof(int), &pathIndex[asynCount++][0]);
		if (stateDim==2)
		{
			err |= clSetKernelArg(kernel[0],  count, sizeof(int), &pathIndex[asynCount][0]);
			err |= clSetKernelArg(kernel[0],  count+1, sizeof(int), &pathIndex[asynCount++][1]);
		}
		if (stateDim==3)
		{
			err |= clSetKernelArg(kernel[0],  count, sizeof(int), &pathIndex[asynCount][0]);
			err |= clSetKernelArg(kernel[0],  count+1, sizeof(int), &pathIndex[asynCount][1]);
			err |= clSetKernelArg(kernel[0],  count+2, sizeof(int), &pathIndex[asynCount++][2]);
		}
	}
	err = clEnqueueNDRangeKernel(cmd_queue, kernel[0], 1, NULL, &global_work_size, NULL, 0, NULL, NULL);
	assert(err == CL_SUCCESS);
	clFinish(cmd_queue);
	err = clEnqueueReadBuffer(cmd_queue, ans_mem, CL_TRUE, 0, buffer_size, results, 0, NULL, NULL);
	assert(err == CL_SUCCESS);
	clFinish(cmd_queue);
	if(type==1)
	{
		for(int i=0;i<size;i++)
			vec[i]=unifRand();
		err = clEnqueueWriteBuffer(cmd_queue, prob_mem, CL_TRUE, 0, sizeof(float)*size,
							   (void*)vec, 0, NULL, NULL);
		err = clSetKernelArg(kernel[0],  prob_pos, sizeof(cl_mem), &prob_mem);
	}
	err = clEnqueueWriteBuffer(cmd_queue, initialState_mem, CL_TRUE, 0, buffer_size,(void*)results, 0, NULL, NULL);
	err  = clSetKernelArg(kernel[0],  0, sizeof(cl_mem), &initialState_mem);
	return results;

}

void Kernel::disconnect()
{

	clReleaseMemObject(initialState_mem);
	clReleaseMemObject(ans_mem);
	
	clReleaseCommandQueue(cmd_queue);
	clReleaseContext(context);

}


char* Kernel::kernelReplace(char* source,string toReplace, string newString)
{
	string app;
	int i=0;
	while(source[i])
	{
		app+=source[i];
		i++;
	}
	app=myReplace(app,toReplace,newString);
	char* rpl=new char[app.length() + 1];
	strcpy(rpl, app.c_str());
	return rpl;
}

char * Kernel::load_program_source(const char *filename)
{
	struct stat statbuf;
	FILE *fh; 
	char *source; 
	
	fh = fopen(filename, "r");
	if (fh == 0)
		return 0; 
	
	stat(filename, &statbuf);
	source = (char *) malloc(statbuf.st_size + 1);
	size_t t=fread(source, statbuf.st_size, 1, fh);
	source[statbuf.st_size] = '\0'; 
	return source; 
}
