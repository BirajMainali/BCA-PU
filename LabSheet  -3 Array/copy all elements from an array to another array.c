#include<stdio.h>
#define max 100
int main()
{

    int arr[max], temp[max],i;
    printf("Enter the Number's :\n");
    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }

    for(i=0; i<5; i++)
    {
        temp[i]= arr[i];
    }

    printf("copied array are : ");
    for(i=0; i<5; i++)
    {
        printf("%d",temp[i]);
    }
    return 0;
}

