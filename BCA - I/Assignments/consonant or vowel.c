#include<stdio.h>
#include<ctype.h>

int main()
{

    char character;
    printf("Enter the character to know consonant or vowel:\t");
    scanf("%c",&character);

    if(toupper(character) == 'A' || toupper(character) =='E' || toupper(character) =='I' || toupper(character) =='O' || toupper(character) =='U')
    {
        printf("vowel character");
    }
    else
    {
        printf("consonant character");
    }
    return 0;
}
