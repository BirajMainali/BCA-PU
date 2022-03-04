#include<stdio.h>
#define size 5

void main()
{
    int arr[size] = {1, 2, 3, 4, 5};
    int i, idx;

    for(i=0; i<5; i++)
    {
        printf("%d \t",arr[i]);
    }

    printf("\nEnter the Index to remove: \t");
    scanf("%d",&idx);

    for(i = idx; i < size - 1; i++)
    {
        arr[i] = arr[i+1];
    }

    printf("New : ");

    for(i = 0; i < size - 1; i++)
    {
        printf("%d ",arr[i]);
    }

}
