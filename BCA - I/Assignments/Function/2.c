/*
    2. Write a C program to find diameter, circumference and area of circle using functions.
*/
#include<stdio.h>
#define PI 3.14
float diameter(float);
float circum(float);
float area(float);

int main()
{
    float radius,d,C,A;

    printf("Enter the radius of a circle : ");
    scanf("%f",&radius);
    d=diameter(radius);
    C=circum(radius);
    A=area(radius);
    printf("Diameter = %0.2f,  Circumference = %0.2f,  Area = %0.2f square unit\n",d,C,A);

    getch();
}

float diameter(float r)
{
    return 2*r;
}
float circum(float r)
{
    return 2*PI*r;
}
float area(float r)
{
    return PI*r*r;
}
