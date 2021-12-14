#include<stdio.h>

#include<stdlib.h>

#include <time.h>

#include<string.h>

#define max 100
#define ContactFile "contact.txt"
#define TempContactFile "contact_temp.txt"
#define write "w"
#define read "r"
#define append "a"

struct Contact {
   int Id;
   char FirstName[max];
   char LastName[max];
   char Email[max];
   long Number;
   char Address[max];
   char * CreatedAt;
}
contact;

FILE * FileProvider(char fileName[], char mode[]);
char * GetCurrentDate();
int EnsureUniqueContact(long newNumber);
void Warning(char message[]);
void GetAllContacts(char queryFirstName[]);
void AddContact(struct Contact newcontact);
void RemoveContact(long ContactNumber);
void UpdateContact(long ContactNumber);

FILE * fp;

int main() {
   char SearchQuery[] = "";
   int Choice;
   long ContactNumber;
   Menu:
   printf("-----------------Menu------------------\n");
   printf("1. Add Contact\n");
   printf("2. View Contact\n");
   printf("3. Search Contact\n");
   printf("4. Update Contact\n");
   printf("5. Delete Contact\n");
   printf("Enter your choice: ");
   scanf("%d",&Choice);
   switch (Choice) {
   case 1:
      system("cls");
      top:
      printf("Enter FirstName : ");
      scanf("%s", contact.FirstName);
      printf("Enter LastName : ");
      scanf("%s", contact.LastName);
      printf("Enter Email : ");
      scanf("%s", contact.Email);
      printf("Enter Contact No : ");
      scanf("%ld", & contact.Number);
      if(EnsureUniqueContact(contact.Number) == 1) {
         Warning("Duplicate Contcat Number");
         goto top;
      }
      printf("Enter Address : ");
      gets(contact.Address);
      AddContact(contact);
      break;
   case 2:
      GetAllContacts(SearchQuery);
      break;
   case 3:
      printf("Enter First Name To Find Contact: ");
      scanf("%s", SearchQuery);
      GetAllContacts(SearchQuery);
      break;
   case 4:
      printf("Enter Contact Number To Update : ");
      scanf("%ld", & ContactNumber);
      UpdateContact(ContactNumber);
      break;
   case 5:
      printf("Enter Contact Number To Update : ");
      scanf("%ld", & ContactNumber);
      RemoveContact(ContactNumber);
      break;
   default:
      Warning("Invalid Choice");
      break;
   }

   return 0;
}

void AddContact(struct Contact newcontact) {
   newcontact.CreatedAt = GetCurrentDate();
   newcontact.Id = rand();
   fp = FileProvider(ContactFile, append);
   fwrite(&newcontact, sizeof(newcontact), 1, fp);
   fwrite != 0 ? printf("Contact Added Successfully") : printf("Contact Not Added");
   fclose(fp);

}

void RemoveContact(long ContactNumber) {
   int flag = 0;
   FILE * fp_temp;
   fp = FileProvider(ContactFile, read);
   fp_temp = FileProvider(TempContactFile, append);
   while (fread( & contact, sizeof(contact), 1, fp)) {
      if (ContactNumber == contact.Number) {
         fwrite( & contact, sizeof(contact), 1, fp_temp);
      } else {
         flag = 1;
      }
   }
   fclose(fp);
   fclose(fp_temp);
   remove(ContactFile);
   rename(TempContactFile, ContactFile);
   flag == 1 ? printf("Contact Removed sucessfully") : printf("Record Not Delete");

}

void UpdateContact(long contactNumber) {
   FILE * f_temp;
   int flag = 0;
   fp = FileProvider(ContactFile, read);
   f_temp = FileProvider(TempContactFile, append);
   while (fread( & contact, sizeof(contact), 1, fp)) {
      if (contact.Number == contactNumber ==) {
         top: printf("Enter FirstName : ");
         scanf("%s", contact.FirstName);
         printf("Enter LastName : ");
         scanf("%s", contact.LastName);
         printf("Enter Email : ");
         scanf("%s", contact.Email);
         printf("Enter Contact No : ");
         scanf("%ld", & contact.Number);
         if (EnsureUniqueContact(contact.Number) == 1) {
            Warning("Duplicate Contact Number");
            goto top;
         }
         printf("Enter Address : ");
         gets(contact.Address);
         fwrite( & contact, sizeof(contact), 1, f_temp);
      }
      else {
         fwrite( & contact, sizeof(contact), 1, f_temp);
         flag = 1;
      }
   }
   fclose(fp);
   fclose(f_temp);
   remove(ContactFile);
   rename(TempContactFile, ContactFile);
   if (flag != 1) {
      printf("Successfully Updated");
       goto top;
   } else {
      printf("\n Contact Not Found \n");
      goto top;
   }
}

int EnsureUniqueContact(long newNumber) {
   fp = FileProvider(ContactFile, append);
   fclose(fp);
   fp = FileProvider(ContactFile, read);
   while (fread( & contact, sizeof(contact), 1, fp)) {
      if (contact.Number == newNumber) {
         fclose(fp);
         return 1;
      }
   }
   return 0;
}

void GetAllContacts(char queryFirstName[]) {
   fp = FileProvider(ContactFile, read);
   if (strlen(queryFirstName) > 1) {
      printf("\nFullName \t\tNumber\t\tEmail \t\tCreatedAt\t\t\t Address\n\n");
      while (fread(&contact, sizeof(contact), 1, fp)) {
         if (strcmp(contact.FirstName, queryFirstName) == 0) {
            printf("%s %s",contact.FirstName,contact.LastName);
            printf("\t\t%ld", contact.Number);
            printf("\t\t%s", contact.Email);
            printf("\t\t%s", contact.CreatedAt);
            printf("%s\n\n", contact.Address);
         }
      }
   } else {
      printf("\nFullName\t\tNumber \t\t\tEmail \t\t\tCreatedAt\t\t\t Address\n\n");
      while (fread(&contact, sizeof(contact), 1, fp)) {
          	printf("%s %s",contact.FirstName,contact.LastName);
		    printf("\t\t%ld", contact.Number);
		    printf("\t%s", contact.Email);
		    printf("\t\t%s", contact.CreatedAt);
		    printf("%s\n\n", contact.Address);
      }
   }
   fclose(fp);
}

char * GetCurrentDate() {
   time_t rawtime;
   struct tm * timeinfo;
   time( & rawtime);
   timeinfo = localtime( & rawtime);
   return asctime(timeinfo);
}

void Warning(char message[]) {
   system("cls");
   system("color e");
   printf("\n%s\n", message);
}

FILE * FileProvider(char fileName[], char mode[]) {
   FILE * fptr;
   fptr = fopen(fileName, mode);
   if (fptr == NULL) {
      fptr = fopen(fileName, mode);
    }
return fptr;
}
