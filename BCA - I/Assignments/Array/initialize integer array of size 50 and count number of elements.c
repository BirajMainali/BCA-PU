#include<stdio.h>

int main()
{
    int arr[50], count, i;

    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }

    for(i=0; i<5; i++)
    {
        if(arr[i]%5==0 && arr[i]>15)
        {
            count ++;
        }
    }

    printf("Count is %d",count);
}
