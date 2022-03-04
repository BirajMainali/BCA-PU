#include<stdio.h>

int main()
{
    int arr[5];
    int i,sum=0;

    printf("Enter five number's to find the sum :\n");
    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }

    for(i=0; i<5; i++)
    {
        sum += arr[i];
    }
    printf("sum of array %d",sum);

}
