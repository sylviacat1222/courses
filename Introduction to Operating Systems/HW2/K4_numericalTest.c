#include <linux/syscalls.h>
#include <linux/kernel.h>

//STUDENT ID: 0816057

int returnValue(int studentId, int a, int b){
	printk("[%d][Ker-4.19.148] syscalltest_returnIndividualValues : [%d][%d]\n", studentId, a, b);
	return 0;
}

int minimum(int studentId, int a, int b, int c){
	int d = a;
	if(b < d) d = b;
	if(c < d) d = c;
	printk("[%d][Ker-4.19.148] syscalltest_minimum : [%d][%d][%d] - [%d]\n", studentId, a, b, c, d);
        return d;
}

int maximum(int studentId, int a, int b, int c){
        int d = a;
        if(b > d) d = b;
        if(c > d) d = c;
        printk("[%d][Ker-4.19.148] syscalltest_maximum : [%d][%d][%d] - [%d]\n", studentId, a, b, c, d);
        return d;
}

int displayDatatypes(int studentId){
	printk("[%d][Ker-4.19.148] size of unsigned int : [%d] bytes\n", studentId, sizeof(unsigned int));
	printk("[%d][Ker-4.19.148] size of signed int : [%d] bytes\n", studentId, sizeof(signed int));
	printk("[%d][Ker-4.19.148] size of unsigned long : [%d] bytes\n", studentId, sizeof(unsigned long));
	printk("[%d][Ker-4.19.148] size of signed long : [%d] bytes\n", studentId, sizeof(signed long));
	printk("[%d][Ker-4.19.148] size of unsigned long long : [%d] bytes\n", studentId, sizeof(unsigned long long));
	printk("[%d][Ker-4.19.148] size of signed long long : [%d] bytes\n", studentId, sizeof(signed long long));
	printk("[%d][Ker-4.19.148] size of double : [%d] bytes\n", studentId, sizeof(double));
	printk("[%d][Ker-4.19.148] size of char : [%d] bytes\n", studentId, sizeof(char));
        return 0;
}

SYSCALL_DEFINE3(syscalltest_returnIndividualValues, int, studentId, int, a, int, b){
	return returnValue(studentId, a, b);
}


SYSCALL_DEFINE4(syscalltest_minimum, int, studentId, int, a, int, b, int, c){ 
        return minimum(studentId, a, b, c);
}

SYSCALL_DEFINE4(syscalltest_maximum, int, studentId, int, a, int, b, int, c){ 
        return maximum(studentId, a, b, c);
}

SYSCALL_DEFINE1(syscalltest_dataTypes, int, studentId){ 
        return displayDatatypes(studentId);
}