#include<stdio.h>
#define max 100
void main()
{
    int numbers[max];
    int Even[]= {};
    int Odd[]= {};
    int EvenLength = 0;
    int OddLength = 0;
    int i,j,k,l,count=5 ;

    printf("Enter any five number:\n");
    for(i=0; i<count; i++)
    {
        scanf("%d",&numbers[i]);
    }
    for(j=0; j<count; j++)
    {
        if(numbers[j]%2==0)
        {
            Even[EvenLength]=numbers[j];
            EvenLength ++;
        }
        else
        {
            Odd[OddLength]=numbers[j];
            OddLength ++;
        }
    }

    printf("Even Number's are:\n");
    for(k=0; k<EvenLength; k++)
    {
        printf("%d \t",Even[k]);
    }
    printf("\n***********************************\n\n");
    printf("Odd Number's are:\n");
    for(l=0; l<OddLength; l++)
    {
        printf("%d \t",Odd[l]);
    }

}
