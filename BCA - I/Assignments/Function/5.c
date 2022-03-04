/*
    5. Write a C program to check whether a number is prime, Armstrong or perfect number using
       functions.
*/
#include<stdio.h>
#include<math.h>
int isprime(int);
int isperfect(int);
int isarmstrong(int);
int i,j,count=0;

int main()
{
    int num=0;

    printf("Enter a number : ");
    scanf("%d",&num);

    isprime(num);
    isperfect(num);
    isarmstrong(num);
}

int isprime(int n)
{

    for(i=1; i<=n; i++)
    {
        if(n%i==0)
            count++;
    }

    if(count==1)
        printf("%d is a prime number\n",n);
    else
        printf("%d is not a prime number\n",n);
}

int isperfect(int n)
{
    int i,sum=0;

    for(i=1; i<n; i++)
    {
        if(n%i==0)
        {
            sum+= i;
        }
    }

    if(sum==n)
        printf("%d is a perfect number\n",n);
    else
        printf("%d is not a perfect number\n",n);

}
int isarmstrong(int num)
{
    int n,i,digit=0,sum=0,rem,Originalnum;

    n=num;
    Originalnum=num;
    while(n!=0)
    {
        n=n/10;
        digit++;
    }

    while(num!=0)
    {
        rem=num%10;
        sum+=pow(rem,digit);
        num=num/10;
    }

    if(Originalnum==sum)
    {
        printf("%d is an Armstrong number\n",Originalnum);
    }
    else
    {
        printf("%d is not an Armstrong number\n",Originalnum);
    }
}
