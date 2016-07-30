#ifndef _Kernel_h_included_
#define _Kernel_h_included_
#include <string>
#include <fstream>
#include <vector>
#include "RuleAnalyzer.h"
#include "StateGenerator.h"
using namespace std;

class Kernel{
public:
	
	Kernel(char* fileName, string rule, int type, int sttDim, int size,int** pthIndex);
	//~Kernel();
	void run(int* results);
	void connect();
	void loadParameter(int * initialState, int dimension, int borderDim,float sill, int sizeX, int sizeY, int sizeZ);
	int* run();
	void disconnect();
protected:
	int count;
	int asynCount;
	int** pathIndex;
	int size;
	int prob_pos;
	int stateDim;
	int type;
	int* results;
	float* vec;
	ofstream myfile;
	cl_program program[1];
	cl_kernel kernel[1];
	cl_command_queue cmd_queue;
	cl_context   context;
	cl_device_id cpu,device;
	cl_int err;
	size_t returned_size;
	size_t buffer_size;
	cl_uint numPlatforms;
	cl_mem initialState_mem, ans_mem, prob_mem, sill_mem;
	size_t global_work_size;
	cl_platform_id* clSelectedPlatformID;
	cl_uint ciDeviceCount;
	cl_char vendor_name[1024];
	cl_char device_name[1024];
	char* program_source;
	char* kernelName;
	string rule;
	char * load_program_source(const char *filename);
	char* kernelReplace(char* source,string toReplace, string newString);

};
#endif
