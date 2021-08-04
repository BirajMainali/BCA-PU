/*
    9. Write a C program to print all perfect numbers between given interval using functions.
*/
#include<stdio.h>
int isperfect(int);
int printPerfectNum(int,int);

int main()
{
    int start,end;

    printf("Enter the intervals: ");
    scanf("%d%d",&start,&end);

    printPerfectNum(start,end);
}

int isperfect(int n)
{
    int i,sum=0;

    for(i=1;i<n;i++)
    {
        if(n%i==0)
        {
            sum+=i;
        }
    }

    if(sum==n)
        printf("%d ",n);
}

int printPerfectNum(int num1,int num2)
{
    while(num1<=num2)
    {
        int output;

        output=isperfect(num1);
        num1++;
    }
}
