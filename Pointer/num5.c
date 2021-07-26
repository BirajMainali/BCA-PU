///5. Write a C program to copy one array to another using pointers.
#include<stdio.h>
#define n 5
int main()
{
    int a[n],b[n],*a_ptr,*b_ptr,i;

    a_ptr=a;

    printf("Enter the elements in First Array:\n");
    for(i=0;i<n;i++)
    {
        printf("Enter element%d : ",i+1);
        scanf("%d",a_ptr+i);
    }

    b_ptr=b;

    printf("\n\nThe copied elements in Second Array are: \n");
    for(i=0;i<n;i++)
    {
        *(b_ptr+i)=*(a_ptr+i);
        printf("%d\n",*(b_ptr+i));
    }
}
