/*
    11. Write a C program to find factorial of any number using recursion.
*/
#include<stdio.h>

int fact(int);

int main()
{
    int n,result;

    printf("Enter a number to find its factorial: ");
    scanf("%d",&n);

    result=fact(n);
    printf("FACTORIAL OF %d = %d\n",n,result);

}

int fact (int x)
{
    if(x==1 || x==0)
        return 1;
    else
        return  x * fact(x-1);
}
