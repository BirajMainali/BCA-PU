#include <stdio.h>

int main()
{
    int ch = 97;

    printf("Alphabets from a - z are: \n");
    while(ch<=122)
    {
        printf("%c\n", ch);
        ch++;
    }

    return 0;
}
