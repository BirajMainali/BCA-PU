#include <stdio.h>
int main()
{
    int arr[5],negativeArr[5],i,j;

    printf("Enter the Number's: \n");
    for(i=0; i<5; i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("Negative Number's are :");
    for(j=0; j<5; j++)
    {
        if(arr[j]<0)
        {
            printf("%d \t",arr[j]);
        }
    }

    return 0;
}
