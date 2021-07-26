///8. Write a C program to search an element in array using pointers.
#include<stdio.h>
#define n 5
int main()
{
    int a[n],*ptr,i,choice,count=0;

    ptr =a;
    printf("Enter the elements of the Array:\n");
    for(i=0;i<n;i++)
    {
        printf("Elements%d: ",i+1);
        scanf("%d",(ptr+i));
    }

    printf("\nEnter the value of element you want to search: ");
    scanf("%d",&choice);

    for(i=0;i<n;i++)
    {
        if(*(ptr+i)==choice)
        {
            printf("Element Found!! ");
            printf("Lies in index %d, position in array = %d\n",i,i+1);
        }
        if(*(ptr+i)!=choice)
            count++;

        if(count==n)
            printf("\nElement does not exist in the array!!!!\n");
    }

}
