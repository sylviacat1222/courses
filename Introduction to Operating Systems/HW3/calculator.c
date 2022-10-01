#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//ADD ADDITIONAL DEFINES HERE
#define init_module(module_image, len, param_values) syscall(__NR_init_module, module_image, len, param_values)
#define finit_module(fd, param_values, flags) syscall(__NR_finit_module, fd, param_values, flags)
#define delete_module(name, flags) syscall(__NR_delete_module, name, flags)

int addition(long* result, int input1, int input2);
int substraction(long* result, int input1, int input2);
int multiplication(long* result, int input1, int input2);

int LoadModule(const char* params);
int UnLoadModule();
void SetParamString(char* parm, int input1, int input2, const char* op);
long GetResult();

// StudentID = 0816057 // replace with your student ID

// ADD ADDITIONAL VARIABLES HERE
int fd, use_finit;
size_t image_size;
struct stat st;
void *image;
// You must load and unload the "calculatorModule.ko" module.
const char *moduleName = "calculatorModule.ko";
const char *moduleNameNoExtension = "calculatorModule";
//const char *paramsNew = "studentId=816057";   // Use your StudentID without leading 0

int main(int argc, char** argv)
{
	long result = -9999999;
	long resultError = -9999999;

	if (argc != 4) {
		printf("%ld\n", resultError);
		return resultError;
	}

	int param01 = atoi(argv[1]);
	int param02 = atoi(argv[2]);
	int operationError = 1;

	if (strcmp(argv[3], "add") == 0) {
		operationError = addition(&result, param01, param02);
	}
	else if (strcmp(argv[3], "sub") == 0) {
		operationError = substraction(&result, param01, param02);
	}
	else if (strcmp(argv[3], "mul") == 0) {
		operationError = multiplication(&result, param01, param02);
	}

	if (operationError == EXIT_SUCCESS) {
		printf("%ld\n", result);
	}
	else {
		printf("%ld\n", resultError);
	}

	return 0;
}


int addition(long* result, int input1, int input2)
{
	*result = 0;
	int operationError = 0;

	//INSERT YOUR CODE HERE
	// Your code must call SetParamString, LoadModule and UnLoadModule.
	// It also must return 0 if success, or EXIT_FAILURE if failure.
	// The result of the operation must be stored in the variable *result.
	char* params = malloc(sizeof(char)*1000);
	char* op = "operationParam=add";
	SetParamString(params, input1, input2, op);
	if(LoadModule(params) != 0){
		return EXIT_FAILURE;
	}
	*result = GetResult();
	if(UnLoadModule() != 0){
		return EXIT_FAILURE;
	}

	return operationError;
}

int substraction(long* result, int input1, int input2)
{
	*result = 0;
	int operationError = 0;

	//INSERT YOUR CODE HERE
	// Your code must call SetParamString, LoadModule and UnLoadModule.
	// It also must return 0 if success, or EXIT_FAILURE if failure.
	// The result of the operation must be stored in the variable *result.
	char* params = malloc(sizeof(char)*1000);
	char* op = "operationParam=sub";
	SetParamString(params, input1, input2, op);
	if(LoadModule(params) != 0){
		return EXIT_FAILURE;
	}
	*result = GetResult();
	if(UnLoadModule() != 0){
		return EXIT_FAILURE;
	}
	
	return operationError;
}

int multiplication(long* result, int input1, int input2)
{
	*result = 0;
	int operationError = 0;

	//INSERT YOUR CODE HERE
	// Your code must call SetParamString, LoadModule and UnLoadModule.
	// It also must return 0 if success, or EXIT_FAILURE if failure.
	// The result of the operation must be stored in the variable *result.
	char* params = malloc(sizeof(char)*1000);
	char* op = "operationParam=mul";
	SetParamString(params, input1, input2, op);
	if(LoadModule(params) != 0){
		return EXIT_FAILURE;
	}
	*result = GetResult();
	if(UnLoadModule() != 0){
		return EXIT_FAILURE;
	}
	
	return operationError;
}

void SetParamString(char* parm, int input1, int input2, const char* op) {
	//INSERT YOUR CODE HERE
	// Your code must concatenate the parameters in the params variable.
	// Read calculatorModule.c to see how you must send the parameters.
	char *p1 = "firstParam=";
	char *p2 = "secondParam=";
	char a[10];
    	char b[10];
    	char* c = " ";
    	sprintf(a, "%d", input1);
    	sprintf(b, "%d", input2);
    	strcat(parm, p1);
    	strcat(parm, a);
    	strcat(parm, c);
    	strcat(parm, p2);
    	strcat(parm, b);
    	strcat(parm, c);
    	strcat(parm, op);
}

int LoadModule(const char* params) {
	//INSERT YOUR CODE HERE
	// Your code must load the module "calculatorModule.ko" and send the parameters params.
	// Read calculatorModule.c to see how you must send the parameters.
	// This function must return EXIT_FAILURE if failure, or 0 if success.
	fd = open(moduleName, O_RDONLY);

    	//printf("Loading module [%s] with parameters [%s]...\n",moduleNameNoExtension, params);

    	fstat(fd, &st);
    	image_size = st.st_size;
    	image = malloc(image_size);
    	read(fd, image, image_size);
    	if (init_module(image, image_size, params) != 0) {
        	perror("init_module");
        	return EXIT_FAILURE;
    	}
    	
	
    	//printf("Module is mounted!\n");
	return 0;
}

long GetResult() {
	long result = 0;

	//INSERT YOUR CODE HERE
	// Your code must read the result from the /sys/module/calculatorModule/ folder.
	// Read calculatorModule.c to know which variable to read.
	// This function must return the result as long.
	// REMEMBER TO CLOSE THE FILE AFTER USING IT.
	FILE *file;
	file = fopen("/sys/module/calculatorModule/parameters/resultParam", "r");
	fscanf(file, "%ld", &result);
	fclose(file);
	return result;
}

int UnLoadModule() {
	//INSERT YOUR CODE HERE
	// Your code must unload the module "calculatorModule.ko".
	// This function must return EXIT_FAILURE if failure, or 0 if success.
	//printf("Unmounting module...\n");

    	if (delete_module(moduleNameNoExtension, O_NONBLOCK) != 0) {
        	perror("delete_module");
        	return EXIT_FAILURE;
    	}

    	close(fd);
    	//printf("Module is unmounted!\n");
    	//printf("Cleaning...\n");

    	free(image);
    	
    	//printf("Done!\n");
	return 0;
}
