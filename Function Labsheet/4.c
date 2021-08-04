/*
    4. Write a C program to check whether a number is even or odd using functions.
*/
#include<stdio.h>

int check(int);

int main()
{
    int num,c;

    printf("Enter a number: ");
    scanf("%d",&num);

    check(num);

}
int check(int a)
{
    if(a%2==0)
    {
        return printf("%d is an Even number.",a);
    }
    else
        return printf("%d is an Odd number.",a);

}
