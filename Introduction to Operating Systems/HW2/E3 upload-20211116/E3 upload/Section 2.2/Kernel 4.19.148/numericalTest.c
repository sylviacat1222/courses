#include <linux/syscalls.h>
#include <linux/kernel.h>

//STUDENT ID: 012345 (With leading 0)

int returnValue(int studentId, int a, int b){
	printk("[%d][Ker-4.19.148] syscalltest_returnIndividualValues : [%d][%d]\n", studentId, a, b);
	return 0;
}

int minimum(int studentId, int a, int b, int c){
	//	Delete these lines, and insert your code here
	//	This function should return the minimum of three values: a,b,c, and output
	//		in kernel log a message of the form:
	//	[12345][Ker-4.19.148] syscalltest_minimum : [30][20][50] - [20]\n

		
}

int maximum(int studentId, int a, int b, int c){
	//	Delete these lines, and insert your code here
	//	This function should return the maximum of three values: a,b,c, and output
	//		in kernel log a message of the form:
	//	[12345][Ker-4.19.148] syscalltest_maximum : [30][20][50] - [50]\n

	
}

int displayDatatypes(int studentId) {
	//	Delete these lines, and insert your code here
	//	This function should return 0, and output in kernel log a message 
	//		of the form:
	//	[12345][Ker-4.19.148] size of unsigned int : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of signed int : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of unsigned long : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of signed long : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of unsigned long long : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of signed long long : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of double : [%d] bytes\n
	//	[12345][Ker-4.19.148] size of char : [%d] bytes\n
	//	where you must get in runtime the value in bytes of the sizes of 
	//		each datatype.	
}


SYSCALL_DEFINE3(syscalltest_returnIndividualValues, int, studentId, int, a, int, b){
	return returnValue(studentId, a, b);
}

//	Delete these lines, and insert your code here
//	You must create the three system calls:
//	1. syscalltest_minimum
//		- Inputs: int studentId, int a, int b, int c
//		- Outputs: return the value obtained by the minimum function above.
// 
//	2. syscalltest_maximum
//		- Inputs: int studentId, int a, int b, int c
//		- Outputs: return the value obtained by the maximum function above.
// 
//	3. syscalltest_dataTypes
//		- Inputs: int studentId
//		- Outputs: return the value obtained by the displayDatatypes function above.