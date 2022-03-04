#include<stdio.h>
int main()
{
    int marks[5],i;
    for ( i = 0; i < 5; i++)
    {
        scanf("%d",&marks[i]);

    }

    printf("displaying marks\n");
    for ( i = 0; i < 5; i++)
    {

        printf("%d\n",marks[i]);
    }

    return 0;

}
