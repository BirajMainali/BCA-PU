#include<stdio.h>
int main()
{
    int m,n,p,q,i,j,k,sum;
    int first[10][10],second[10][10],third[10][10];


    printf("Enter the number of rows and columns of first matrix\n");
    scanf("%d%d",&m,&n);


    printf("Enter the elements of first matrix \n");
    for(i=0; i<m ; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d",&first[i][j]);
        }
    }


    printf("Enter the number of rows and columns of Second matrix\n");
    scanf("%d%d",&p,&q);


    if(n!=p)
    {
        printf("Multiplication is not possible\n");
    }
    else
    {
        printf("Enter the elements of second matrix \n");
        for(i=0; i<p ; i++)
        {
            for(j=0; j<q; j++)
            {
                scanf("%d",&second[i][j]);
            }
        }


        for(i=0; i<m; i++)
        {
            for(j=0; j<q; j++)
            {
                sum=0;
                for(k=0; k<p; k++)
                {
                    sum=sum+first[i][k]*second[k][j];
                }
                third[i][j]=sum;


            }
        }


        for(i=0; i<m; i++)
        {
            for(j=0; j<q; j++)
            {
                printf("%d\t",third[i][j]);
            }
            printf("\n");
        }


    }
    return 0;
}
