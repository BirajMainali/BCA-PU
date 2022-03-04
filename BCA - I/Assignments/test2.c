#include<stdio.h>

void main()
{
    int i,j,k;

    for(i=1; i<=6; i++)
    {
        for(j=6; j>=i; j--)
        {
            printf(" ");
        }
        for(k=1; k<=j; k++)
        {
            printf("%d",k);
        }
        printf("\n");
    }

}

