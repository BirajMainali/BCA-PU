#include <stdio.h>
#define max 5
int main()
{
    int arr[max],i,j;

    printf("enter Any 5 Number");
    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }

    printf("entered array are ");
    for(j=0; j<5; j++)
    {
        printf("%d",arr[j]);
    }

    return 0;
}
