#include<stdio.h>

void PrintArray(int a[], int Size);

int main()
{
    int Size, i, a[10], Even[10], Odd[10];
    int Even_Count = 0, Odd_Count = 0;

    printf("\n Please Enter the Size of an Array :  ");
    scanf("%d", &Size);

    printf("\n Please Enter the Array Elements  :   ");
    for(i = 0; i < Size; i++)
    {
        scanf("%d", &a[i]);
    }

    for(i = 0; i < Size; i ++)
    {
        if(a[i] % 2 == 0)
        {
            Even[Even_Count] = a[i];
            Even_Count++;
        }
        else
        {
            Odd[Odd_Count] = a[i];
            Odd_Count++;
        }
    }

    printf("\n Total Number of Even Numbers in this Array = %d ", Even_Count);
    printf("\n Array Elements in Even Array  :  ");
    PrintArray(Even, Even_Count);

    printf("\n Total Number of Odd Numbers in this Array = %d ", Odd_Count);
    printf("\n Array Elements in Odd Array  : ");
    PrintArray(Odd, Odd_Count);
    return 0;
}
void PrintArray(int a[], int Size)
{
    int i;
    for(i = 0; i < Size; i++)
    {
        printf("%d \t ", a[i]);
    }
    printf("\n");
}
