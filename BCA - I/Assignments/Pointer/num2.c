///2. Write a C program to add two numbers using pointers.
#include<stdio.h>
int main()
{
    int num1,num2,*a,*b,sum=0;

    printf("Enter two numbers : ");
    scanf("%d%d",&num1,&num2);

    a=&num1;
    b=&num2;

    sum=*a+*b;

    printf("%d + %d = %d",*a,*b,sum);
}
