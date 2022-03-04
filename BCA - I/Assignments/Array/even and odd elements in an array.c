#include<stdio.h>
#define max 100

int main()
{
    int arr[5]= {1,2,3,4,5};
    int odd=0,even=0, i;

    for(i=0; i<5; i++)
    {
        if(arr[i]%2==0)
        {
            odd ++;
        }
        else
        {
            even ++;
        }
    }

    printf("Odd count : %d  Even count :%d",odd,even);

    return 0;
}
