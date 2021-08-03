#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000


void
(char * str, const char * toRemove);


int main()
{
    FILE * fPtr;
    FILE * fTemp;
    char path[100];

    char toRemove[100];
    char buffer[1000];

    printf("Enter path of source file: ");
    scanf("%s", path);

    printf("Enter word to remove: ");
    scanf("%s", toRemove);


    fPtr  = fopen(path, "r");
    fTemp = fopen("delete.tmp", "w");

    if (fPtr == NULL || fTemp == NULL) {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }



    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
        removeAll(buffer, toRemove);
        fputs(buffer, fTemp);
    }



    fclose(fPtr);
    fclose(fTemp);

    remove(path);
    rename("delete.tmp", path);


    printf("\nAll occurrence of '%s' removed successfully.", toRemove);

    return 0;
}


void removeAll(char * str, const char * toRemove)
{
    int i, j, stringLen, toRemoveLen;
    int found;

    stringLen   = strlen(str);
    toRemoveLen = strlen(toRemove);


    for(i=0; i <= stringLen - toRemoveLen; i++)

        found = 1;
    for(j=0; j < toRemoveLen; j++) {
        if(str[i + j] != toRemove[j]) {
            found = 0;
            break;
        }
    }

    if(str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n' && str[i + j] != '\0') {
        found = 0;
    }


    if(found == 1) {
        for(j=i; j <= stringLen - toRemoveLen; j++) {
            str[j] = str[j + toRemoveLen];
        }

        stringLen = stringLen - toRemoveLen;

        i--;
    }
}
}
