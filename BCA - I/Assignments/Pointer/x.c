#include<stdio.h>
#include<stdlib.h>
#define row 2
#define col 2

int inputArray(int mat[][col]);
int product(int mat1[][col],int mat2[][col],int res[][col]);
int printArray(int arr[][col]);
int i,j;

int main()
{
    int a[row][col],b[row][col],mul[row][col];

    printf("Enter first matrix: \n");
    inputArray(a);

    printf("\nEnter second matrix: \n");
    inputArray(b);

    product(a,b,mul);

    system("cls");
    printf("First Matrix: \n");
    printArray(a);
    printf("\n");
    printf("Second Matrix: \n");
    printArray(b);
    printf("\n");
    printf("Product : \n");
    printArray(mul);
}

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

int product(int mat1[][col],int mat2[][col],int res[][col])
{
    int k,sum;

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            sum = 0;
            for(k =0;k<col;k++)
            {
                sum += *(*(mat1+i)+k) * *(*(mat2+k)+j);
            }

            *(*(res+i)+j) = sum; //storing it in res[]
        }
    }
}

int printArray(int arr[][col])
{
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%d\t",*(*(arr+i)+j));
        }
        printf("\n");
    }
}
