#include <stdio.h>
#include <ctype.h>
#define MAX_SIZE  32
#define FILE_NAME "aticleworldx.txt"

void toggleFileData(FILE *fptr)
{
    FILE *fpTmp = NULL;
    int ch = 0;

    fpTmp = fopen("tmp.txt", "w");
    if(fpTmp == NULL) {
        printf("Error in creating tmp file\n");
        fclose(fptr);
        exit(1);
    }

    while ( (ch = fgetc(fptr)) != EOF) {

        ch = (isupper(ch))? tolower(ch):toupper(ch);

        fputc(ch, fpTmp);
    }

    fclose(fptr);
    fclose(fpTmp);

    remove(FILE_NAME);
    rename("tmp.txt", FILE_NAME);
}
int main()
{

    FILE *fp = NULL;

    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        printf("Error in creating the file\n");
        exit(1);
    }

    toggleFileData(fp);
    return 0;
}
