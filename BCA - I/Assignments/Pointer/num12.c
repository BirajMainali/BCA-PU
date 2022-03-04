///12. Write a C program to transpose a matrix using pointer.
#include<stdio.h>
#include<stdlib.h>
#define row 3
#define col 3

int main()
{
    int arr[row][col],transpose[row][col],i,j;

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("Enter matrix(%d%d):  ",i,j);
            scanf("%d",*(arr+i)+j);
        }
    }

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            *(*(transpose+j)+i) = *(*(arr+i)+j);
        }

    }
    system("cls");
    printf("The entered matrix: \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%d\t",*(*(arr+i)+j));
        }
        printf("\n");
    }

    printf("\nThe transpose matrix: \n");
    for(i=0;i<col;i++)
    {
        for(j=0;j<row;j++)
        {
            printf("%d\t",*(*(transpose+i)+j));
        }
        printf("\n");
    }

}
