#include<stdio.h>

int main()
{
    int num,i=1,sum;
    printf("Enter any positive number:\t");
    scanf("%d",&num);

    while(i<=num)
    {
        if(i%2==0)
        {
            sum += i;
            i++;
            printf("%d",sum);
        }

    }

    return 0;
}
