#include <linux/syscalls.h>
#include <linux/kernel.h>

//STUDENT ID: 0816057

int returnValue(int studentId, int a, int b){
        printk("[%d][Ker-5.13.19] syscalltest_returnIndividualValues : [%d][%d]\n", studentId, a, b);
        return 0;
}

int addition(int studentId, int a, int b){ 
        printk("[%d][Ker-5.13.19] syscalltest_addition : [%d][%d][%d]\n", studentId, a, b, a+b);
        return a+b;
}

int multiplication(int studentId, int a, int b){ 
        printk("[%d][Ker-5.13.19] syscalltest_multiplication : [%d][%d][%d]\n", studentId, a, b, a*b);
        return a*b;
}

int displayDatatypes(int studentId){
        printk("[%d][Ker-5.13.19] size of unsigned int : [%d] bytes\n", studentId, sizeof(unsigned int));
        printk("[%d][Ker-5.13.19] size of signed int : [%d] bytes\n", studentId, sizeof(signed int));
        printk("[%d][Ker-5.13.19] size of unsigned long : [%d] bytes\n", studentId, sizeof(unsigned long));
        printk("[%d][Ker-5.13.19] size of signed long : [%d] bytes\n", studentId, sizeof(signed long));
        printk("[%d][Ker-5.13.19] size of unsigned long long : [%d] bytes\n", studentId, sizeof(unsigned long long));
        printk("[%d][Ker-5.13.19] size of signed long long : [%d] bytes\n", studentId, sizeof(signed long long));
        printk("[%d][Ker-5.13.19] size of double : [%d] bytes\n", studentId, sizeof(double));
        printk("[%d][Ker-5.13.19] size of char : [%d] bytes\n", studentId, sizeof(char));
        return 0;
}

SYSCALL_DEFINE3(syscalltest_returnIndividualValues, int, studentId, int, a, int, b){ 
        return returnValue(studentId, a, b);
}


SYSCALL_DEFINE3(syscalltest_addition, int, studentId, int, a, int, b){ 
        return addition(studentId, a, b);
}

SYSCALL_DEFINE3(syscalltest_multiplication, int, studentId, int, a, int, b){ 
        return multiplication(studentId, a, b);
}

SYSCALL_DEFINE1(syscalltest_dataTypes, int, studentId){ 
        return displayDatatypes(studentId);
}
