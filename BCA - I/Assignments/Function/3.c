/*
    3. Write a C program to find maximum and minimum between two numbers using functions.
*/
#include<stdio.h>
float comp(float, float);

int main()
{
    float num1,num2,res;

    printf("Enter any two numbers : ");
    scanf("%f%f",&num1,&num2);
    res = comp(num1,num2);

    if(res==1)
    {
        printf("Max = %0.2f and Min = %0.2f",num1,num2);
    }
    else
        printf("Max = %0.2f and Min = %0.2f",num2,num1);

}

float comp(float x, float y)
{
    int isMax=1;
    if(x>y)
    {
        isMax = 1;
    }
    else
        isMax=0;

    return isMax;
}
