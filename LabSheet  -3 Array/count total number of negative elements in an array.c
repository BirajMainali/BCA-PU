#include<stdio.h>
#define max 1000

int main()
{
    int arr[max], negativeCount =0,i;

    printf("Enter the Number's : \n");
    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }

    for(i=0; i<5; i++)
    {
        if(arr[i]<0)
        {
            negativeCount ++;
        }
    }
    printf("Negative Number Count: %d",negativeCount);
}
