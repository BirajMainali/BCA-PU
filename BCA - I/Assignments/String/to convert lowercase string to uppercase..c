#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100 // Maximum string size


int main()
{
    char str[MAX_SIZE];

    printf("Enter your text : ");
    gets(str);

    strupr(str);

    printf("Uppercase string : %s", str);

    return 0;
}
