#include<stdio.h>

int main()
{

    int arr[5]= {1,2,3,4,5};
    int max = arr[1], min = arr[1];
    int max2 = max, i;



    for(i=0; i<5; i++)
    {
        if(arr[i]<min)
        {
            min = arr[i];
        }
        if(arr[i]>max)
        {
            max = arr[i];
        }
    }

    for(i=0; i<5; i++)
    {
        if(arr[i] > max2 && arr[i] < max)
        {
            max2 = arr[i];
        }
    }

    printf("Second Largest Number is : %d",max2);
    return 0;
}
