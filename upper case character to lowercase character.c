#include<stdio.h>
#include<ctype.h>
#define max 100
void main()
{
    char character;
    printf("Enter Any Character:\t");
    scanf("%c",&character);

    if(islower(character))
    {
        printf("%c",toupper(character));
    }
    else
    {
        printf("%c",tolower(character));
    }
}
