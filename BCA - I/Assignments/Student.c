#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 100

void addStudentRecord();
void viewStudentRecord();
void hasPassword();
struct student {
    int Id;
    char Address[max];
    char Name[max];
    float Percentage;
};

FILE *fp;
int main() {

    char username[max],password[max];
    int choice;
top:
    printf("UserName : ");
    gets(username);
    printf("Password :");
    gets(password);
    if(strcmp(username,"x")==0 && strcmp(password,"x")==0) {
menu:
        system("cls");
        printf("[1] > Add Record\n");
        printf("[2] > View Record\n");
        printf("[3] > Update Record\n");
        printf("\n\n Enter your choice [1-3] :");
        scanf("%d",&choice);
        system("cls");
        switch(choice) {
        case 1 :
            addStudentRecord();
            break;

        case 2 :
            viewStudentRecord();
            goto menu;
            break;
        case 3 :
            printf("Not Implemented exception");
            break;
        default:
            system("cls");
            printf("Invalid Choice\n\n");
            goto menu;
            break;
        }
    } else {
        system("cls");
        printf("Invalid Login :\n\n");
        goto top;
    }
    return 0;
}
void addStudentRecord() {
    struct student std;
newRecord:
    printf("Enter Id :");
    scanf("%d",&std.Id);
    fflush(stdin);
    printf("Enter Name :");
    fflush(stdin);
    gets(std.Name);
    printf("Enter Address :");
    gets(std.Address);
    printf("Enter Percentage: ");
    scanf("%f",&std.Percentage);
    fp=fopen("student.txt","a");
    fwrite(&std,sizeof(std),1,fp);
    if(fwrite!=0) {
        printf("success...\n\n");

    } else {
        printf("some things went wrong");
        system("cls");
        goto newRecord;

    }
    fclose(fp);
}
void viewStudentRecord() {
    struct student std;
    printf("List of Record: \n\n");
    printf("--------------------------------------------\n\n");
    fp=fopen("student.txt","r");
    if(fp == NULL) {
        system("cls");
        printf("No Record Found \n");
        addStudentRecord();
    }

    printf("\tId\tName\t\tAddress\\tPercentage");
    while(fread(&std,sizeof(std),1,fp)) {
        printf("%d",std.Id);
        printf("\t%s",std.Name);
        printf("\\t%s",std.Address);
        printf("\\t%f",std.Percentage);
        getchar();
    }
    fclose(fp);
}
