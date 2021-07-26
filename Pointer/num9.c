///9. Write a C program to add two matrix using pointers.
#include<stdio.h>
#define row 3
#define col 3

int inputArray(int mat[][col]);
int add(int mat1[][col],int mat2[][col],int res[][col]);
int i,j;

int main()
{
    int a[row][col],b[row][col],sum[row][col];

    printf("Enter first matrix: \n");
    inputArray(a);

    printf("\nEnter second matrix: \n");
    inputArray(b);

    add(a,b,sum);

}

//asking for input
int inputArray(int mat[][col])
{
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            scanf("%d",*(mat+i)+j);
        }
    }
}

int add(int mat1[][col],int mat2[][col],int res[][col])
{
    printf("\nThe sum of matrices : \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            *(*(res+i)+j) = *(*(mat1+i)+j) + *(*(mat2+i)+j);
            printf("%d\t",*(*(res+i)+j));
        }
        printf("\n");
    }
}
