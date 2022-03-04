/*
    10. Write a C program to find power of any number using recursion.
*/
#include<stdio.h>
int power(int,int);

int main()
{
    int p,bse,result;

    printf("Enter the base and power : ");
    scanf("%d%d",&bse,&p);

    result=power(bse,p);
    printf("%d raised to power %d is %d\n",bse,p,result);
}

int power(int x,int y)
{
    if(y==0)
        return 1;
    else if(y==1)
        return x;
    else
        return x * power(x,y-1);
}
