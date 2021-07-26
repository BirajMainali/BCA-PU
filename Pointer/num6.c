///6. Write a C program to swap two arrays using pointers.
#include<stdio.h>
#define n 5
int main()
{
    int a[n],b[n],temp[n],*a_ptr,*b_ptr,*temp_ptr,i;

    a_ptr = a;
    b_ptr = b;
    temp_ptr =temp;

    printf("Enter the elements of First Array : \n");
    for(i=0;i<n;i++)
    {
        printf("Enter element%d: ",i+1);
        scanf("%d",(a_ptr+i));
    }
    printf("\nEnter the elements of Second Array : \n");
    for(i=0;i<n;i++)
    {
        printf("Enter element%d: ",i+1);
        scanf("%d",(b_ptr+i));
    }


    for(i=0;i<n;i++)
    {
        *(temp_ptr+i)=*(a_ptr+i);
    }

    printf("\n\nElements of First Array after swapping: \n");
    for(i=0;i<n;i++)
    {
        *(a_ptr+i)=*(b_ptr+i);
        printf("%d\n",*(a_ptr+i));
    }

  
     printf("\n\nElements of Second Array after swapping: \n");
    for(i=0;i<n;i++)
    {
        *(b_ptr+i)=*(temp+i);
        printf("%d\n",*(b_ptr+i));
    }

}
