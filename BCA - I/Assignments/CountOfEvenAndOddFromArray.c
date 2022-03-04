#include <stdio.h>

void main()

{



    int array[100], i, num, oddcount=0,evencount=0;

    printf("Enter the size of an array \n");

    scanf("%d", &num);

    printf("Enter the elements of the array \n");



    for (i = 0; i < num; i++)

    {
        scanf("%d", &array[i]);
    }

    for (i = 0; i < num; i++)

    {
        if (array[i] % 2 == 0)

        {

            evencount ++;
        }
    }
    for (i = 0; i < num; i++)
    {

        if (array[i] % 2 != 0)
        {
            oddcount ++;

        }
    }

    printf(" Odd Number's count %d\n",oddcount);
    printf(" Even Number's count %d\n",evencount);


}
