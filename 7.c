/*
    7. Write a C program to print all strong numbers between given interval using functions.
*/
#include<stdio.h>

int fact(int);
int strongNum(int,int);

int main()
{
    int start,end;
    printf("Enter the intervals: ");
    scanf("%d%d",&start,&end);

    strongNum(start,end);

}

int fact(int x)
{
    if(x==0 || x==1)
        return 1;
    else
        return x* fact(x-1);
}

int strongNum(int num1,int num2)
{
    int i,j,rem,sum,temp;

    printf("Strong numbers: ");
    for(i=num1; i<=num2; i++)
    {

        for(j=1; j<=i; j++)
        {
            temp=i;
            while(temp!=0)
            {
                rem=temp%10;
                sum+= fact(rem);
                temp=temp/10;
            }
            if(sum==i)
            {
                printf("%d ",i);

            }
            sum=0;
            break;
        }
    }
}
