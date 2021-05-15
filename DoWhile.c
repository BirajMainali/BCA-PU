#include<stdio.h>

void forLoop();
void DoWhile();
void While();

int number=1;
int Multiplication=0;

int main()
{
    forLoop();
    // DoWhile();
   // While();

    return 0;
}


void forLoop()
{
    printf("Enter a Number:\t");
    scanf("%d",&Multiplication);

    for(int number=1; number<10; number++)
    {
        printf("%d * %d = %d\n",Multiplication,number,number*Multiplication);
    }
}


void DoWhile()
{
    printf("Enter a Number:\t");
    scanf("%d",&Multiplication);
    do
    {
        printf("%d * %d = %d\n",Multiplication,number,number*Multiplication);
        number++;
    }
    while(number<=10);
}

void While()
{
    printf("Enter a Number:\t");
    scanf("%d",&Multiplication);

    while(number<10)
    {
        printf("%d * %d = %d\n",Multiplication,number,number*Multiplication);
        number ++;
    }

}
