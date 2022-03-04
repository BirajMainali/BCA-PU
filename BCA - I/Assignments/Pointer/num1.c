///1. Write a C program to create, initialize and use pointers.
#include<stdio.h>
int main()
{
    int a=10,*ptr;

    ptr = &a; 

    printf("The address of a is %d",ptr);
}
