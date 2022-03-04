/*
    1. Write a C program to find cube of any number using function.
*/
#include<stdio.h>
float cube(float);

int main()
{
    float number,r;

    printf("Enter a number to find its cube: ");
    scanf("%f",&number);
    r=cube(n);
    printf("Cube of %0.2f = %0.2f",n,r);
}

float cube(float a)
{
    return a*a*a;
}
