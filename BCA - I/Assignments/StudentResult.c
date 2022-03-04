#include<stdio.h>

void main()
{
    float marks;
    printf("Enter Scored Marks:\t");
    scanf("%f",&marks);

    if(marks<50)
    {
        printf("F");
    }
    else if(marks>=50 && marks<60)
    {
        printf("C");
    }
    else if(marks>=60 && marks<70)
    {
        printf("B");
    }
    else if(marks>=70 && marks<80)
    {
        printf("B+");
    }
    else if(marks>=80 && marks<90)
    {
        printf("A");
    }
    else if(marks>=90 && marks<100)
    {
        printf("A+");
    }
    else
    {
        printf("Number cannot be smaller than 0 or greater than 100");
    }

}
