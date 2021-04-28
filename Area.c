#include <stdio.h>
int main(void)
{
    float lenght;
    float Breadth;
    float Area;
    float Perimeter;

    printf("Enter the length:\t");
    scanf("%f",&lenght);
    printf("Enter the Breadth:\t");
    scanf("%f",&Breadth);
    Area = lenght * Breadth;
    Perimeter = (lenght * 2) + (Breadth * 2);
    printf("Area is :\t %f",Area);
    printf("\n Perimeter is:\t %f",Perimeter);
    return 0;
}
