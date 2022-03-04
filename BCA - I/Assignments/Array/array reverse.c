#include <stdio.h>
#define max 10
int ElementCount = 0;
int original[max];
int Reverse[max];

int main()
{
    printf("enter the count of array \n");
    scanf("%d", &ElementCount);

    printf("Please Enter the array Element \n");

    for (int j = 0; j <ElementCount; j++)
    {

        scanf("%d", &original[j]);
    }
    for(int i = 0 ; i<ElementCount; i++)
    {
        Reverse[i] = original[ElementCount-1-i];
        printf("\n %d \t",Reverse[i]);
    }

    return 0;
}
