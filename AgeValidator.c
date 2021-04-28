#include <stdio.h>

void main()
{
    int Age, WaitAge;
    printf("Enter your Age:\t");
    scanf("%d",&Age);

    if(Age > 16)
    {
        printf("You are Eligible for Citizenship \n");
    }
    else
    {
        WaitAge = (16 - Age);
        printf("You are Not Eligible for Citizenship, you must wait %d Year",WaitAge);
    }

}
