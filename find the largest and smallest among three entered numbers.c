#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num1,num2,num3,max,min;
    printf("Enter three numbers:\t");
    scanf("%d %d %d",&num1,&num2,&num3);

    if(num1<num2 && num1<num3)
    {

        printf("\n%d is the smallest",num1);
        min = num1;

    }
    else if(num2<num3)
    {

        printf("\n%d is the smallest",num2);
        min = num2;
    }
    else
    {
        printf("\n%d is the smallest",num3);
        min = num3;
    }
    if(num1>num2 && num1>num3)
    {

        printf("\n%d is largest",num1);
        max = num1;
    }
    else if(num2>num3)
    {

        printf("\n%d is largest",num2);
        max = num2;
    }
    else
    {
        printf("\n%d is largest",num3);
        max = num3;
    }

    if(min%2==0)
    {
        printf("\nSmallest Number is Even Number \n");
    }
    else
    {
        printf("Smallest Number is Odd Number \n");
    }
    if(max%2==0)
    {
        printf("Largest Number is Even Number\n");
    }
    else
    {
        printf("Largest Number is Odd Number\n");
    }


    getch();
    return 0;
}
