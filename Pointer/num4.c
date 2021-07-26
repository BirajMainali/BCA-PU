///4. Write a C program to input and print array elements using pointer.
#include<stdio.h>
#define n 5
int main()
{
    int a[n],*ptr,i;

    ptr = a; //pointing to first element of array a[0]

      for(i=0;i<n;i++)
    {
        printf("Enter element%d: ",i+1);
        scanf("%d",ptr+i);
    }

    printf("\nThe elements are:\n");
    for(i=0;i<n;i++)
    {
        printf("%d\n",*(ptr+i));
    }
}
