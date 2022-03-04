#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000


int countOccurrences(FILE *fptr, const char *word);


int main()
{
    FILE *fptr;
    char path[100];

    char word[50];

    int wCount;

    printf("Enter file path: ");
    scanf("%s", path);


    printf("Enter word to search in file: ");
    scanf("%s", word);

    fptr = fopen(path, "r");

    if (fptr == NULL) {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }


    wCount = countOccurrences(fptr, word);

    printf("'%s' is found %d times in file.", word, wCount);

    fclose(fptr);

    return 0;
}


int countOccurrences(FILE *fptr, const char *word)
{
    char str[BUFFER_SIZE];
    char *pos;

    int index, count;

    count = 0;


    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL) {
        index = 0;


        while ((pos = strstr(str + index, word)) != NULL) {

            index = (pos - str) + 1;

            count++;
        }
    }

    return count;
}
