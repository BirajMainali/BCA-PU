#include <stdio.h>
#include <string.h>

int main()
{
    char s[1000];
    int  i,j;

    printf("Enter the string : ");
    gets(s);

    printf("Before trimming leading white spaces :%s",s);
    for(i=0; s[i]==' '||s[i]=='\t'; i++);

    for(j=0; s[i]; i++)
    {
        s[j++]=s[i];
    }
    s[j]='\0';
    printf("\nAfter trimming leading white spaces:%s",s);
}
