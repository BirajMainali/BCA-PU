#include <stdio.h>
#define max 100

void main()

{

    int numbers[max], i, num;

    printf("Enter the size of an numbers \n");

    scanf("%d", &num);

    printf("Enter the elements of the numbers \n");

    for (i = 0; i < num; i++)
    {

        scanf("%d", &numbers[i]);
    }

    printf("Even numbers in the array are :\t");

    for (i = 0; i < num; i++)

    {

        if (numbers[i] % 2 == 0)

        {

            printf("%d \t", numbers[i]);

        }
    }

    printf("\n Odd numbers in the array are :\t");

    for (i = 0; i < num; i++)

    {

        if (numbers[i] % 2 != 0)

        {

            printf("%d \t", numbers[i]);

        }

    }

}
