#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define _max 100
#define write "w"
#define read "r"
#define append "a"
#define store "contact.txt"
#define temp_store "contact_temp.txt"
#define authStore "auth.txt"

struct Contact
{
   int Id;
   long Number;
   bool IsFavorite;
   char FirstName[_max];
   char LastName[_max];
   char Email[_max];
   char Address[_max];
   char CreatedAt[_max];
   char RecUserName[_max];
   bool IsValid;
}
contact;

struct Admin
{
   char UserName[_max];
   char Password[_max];
   char ConfirmPassword[_max];
}
admin;

void Next();
void Display(char text[]);
void CreateInitialStore();
char *GetPassword();
void RegisterUser();
void Login();
void Dashboard();
void Create();
void Update();
int Remove(long contactNumber);
void MarkFavorite(long contactNumber);
void View(char queryFirstName[]);
int SaveChanges(struct Contact Reqcontact);
struct Contact FindByContact(long contactNumber);
int EnsureUniqueContact(long newNumber);
char *GetCurrentDate();
void Warning(char message[]);
void EnsureUniqueUserName(char username[]);
void Title(char title[]);
FILE* FileProvider(char fileName[], char mode[]);

FILE * fp;

FILE * auth_fp;
long ContactNumber;
int Favorite;
int main()
{
   system("color a");
   CreateInitialStore();
   Title("Authentication");
   int choice;
   top:
      printf("\t\t\t======================================\n");
   printf("\t\t\t[1] Login\n");
   printf("\t\t\t[2] Register\n");
   printf("\t\t\tEnter your choice :: ");
   scanf("%d", &choice);
   switch (choice)
   {
      case 1:
         Login();
         break;
      case 2:
         RegisterUser();
         break;
      default:
         printf("\t\t\tInvalid choice");
         goto top;
   }
   return 0;
}

void RegisterUser()
{
   struct Admin admin;
   char confirmPassword[_max];
   system("cls");
   printf("\t\t\tEnter username : ");
   scanf("%s", admin.UserName);
   printf("\t\t\tEnter Password :");
   strcpy(admin.Password, GetPassword());
   printf("\n\t\t\tEnter ConfirmPassword :");
   strcpy(confirmPassword, GetPassword());
   EnsureUniqueUserName(admin.UserName);
   if (strcmp(admin.Password, confirmPassword) != 0)
   {
      printf("\t\t\tConfirm password is not matching");
      RegisterUser();
   }
   auth_fp = FileProvider(authStore, append);
   fwrite(&admin, sizeof(admin), 1, auth_fp);
   fclose(auth_fp);
   printf("%s\t\t\tsuccessfully registered\n\n", admin.UserName);
   Login();
}

void EnsureUniqueUserName(char username[])
{
   auth_fp = FileProvider(authStore, read);
   while (fread(&admin, sizeof(admin), 1, auth_fp))
   {
      if (strcmp(admin.UserName, username) == 0)
      {
         Warning("\t\t\tuser aleady exist");
         RegisterUser();
      }
   }
   fclose(auth_fp);
}

void Login()
{
   char username[_max], password[_max];
   top:
      system("cls");
   printf("UserName :: ");
   scanf("%s", username);
   printf("Passwords:: ");
   strcpy(password, GetPassword());
   auth_fp = FileProvider(authStore, read);
   while (fread(&admin, sizeof(admin), 1, auth_fp))
   {
      if (strcmp(admin.UserName, username) == 0 && strcmp(admin.Password, password) == 0)
      {
         fclose(auth_fp);
         Dashboard();
      }
   }
   system("cls");
   printf("Invalid username or password\n");
   fclose(auth_fp);
   goto top;
}

void Dashboard()
{
   system("cls");
   int Choice;
   char query[_max];
   Menu:
      printf("\t\t\t*************************************************************\n");
   printf("\t\t\t\t\tContact Management\n");
   printf("\t\t\t*************************************************************\n");
   printf("\t\t\t\t\t1. Add Contact\n");
   printf("\t\t\t\t\t2. View Contact\n");
   printf("\t\t\t\t\t3. Search Contact\n");
   printf("\t\t\t\t\t4. Update Contact\n");
   printf("\t\t\t\t\t5. Delete Contact\n");
   printf("\t\t\t\t\t6. Favorite\n");
   printf("\t\t\t\t\tEnter your choice: ");
   scanf("%d", &Choice);
   switch (Choice)
   {
      case 1:
         Create();
         break;
      case 2:
         View("");
         break;
      case 3:
         system("cls");
         Display("Sort contact list by name");
         printf("\t\t\t\t\t Name : ");
         scanf("%s", query);
         View(query);
         break;
      case 4:
         system("cls");
         Display("Update Contact");
         Update();
         break;
      case 5:
         system("cls");
         Display("Remove contact");
         printf("\t\t\t\t\tEnter contact number to remove:");
         scanf("%ld", &ContactNumber);
         struct Contact info = FindByContact(ContactNumber);
         if (info.IsValid)
         {
            printf("\n\n\t\t\t\t.....................................................\n\n");
            printf("\t\t\t\t\tFullName : %s %s", info.FirstName, info.LastName);
            if (info.IsFavorite)
            {
               printf(" ??");
            }
            printf("\n\t\t\t\t\tNumber: %ld", info.Number);
            printf("\n\t\t\t\t\tEmail: %s", info.Email);
            printf("\n\t\t\t\t\tAddress : %s", info.Address);
            printf("\n\t\t\t\t\tCreated By: %s", info.RecUserName);
            printf("\n\t\t\t\t\tCreatedAt: %s", info.CreatedAt);
            printf("\n\n\t\t\t\t.....................................................\n\n");
            printf("\t\t\t\t\tPress[Enter] to Remove :: ");
            int command = getch();
            command == 13 ? Remove(info.Number) : Dashboard();
            printf("\n\t\t\tContact removed successfully");
         }
         else
         {
            printf("\t\t\tContact not found");
         }

      case 6:
         system("cls");
         Display("Mark as favorite");
         printf("\t\t\tContact Number:");
         scanf("%ld", &ContactNumber);
         MarkFavorite(ContactNumber);
         break;
      default:
         Warning("Invalid Choice");
         goto Menu;
         break;
   }
}

void Create()
{
   system("cls");
   Display("Add new contact");
   printf("\t\t\t\t\tFirstName : ");
   scanf("%s", contact.FirstName);
   printf("\t\t\t\t\tLastName : ");
   scanf("%s", contact.LastName);
   printf("\t\t\t\t\tEmail : ");
   scanf("%s", contact.Email);
   printf("\t\t\t\t\tContact No : ");
   scanf("%ld", &contact.Number);
   printf("\t\t\t\t\tAddress : ");
   scanf("%s", &contact.Address);
   printf("\t\t\t\t\tFavorite : ");
   scanf("%d", &Favorite);
   contact.IsFavorite = Favorite;
   if (SaveChanges(contact) == 0)
   {
      printf("\t\t\t\t\tContact added successfully\n");
   }
   else
   {
      printf("\t\t\t\t\tContact not added");
   }
   Next();
}

void Update()
{
   long contactNumber;
   printf("\t\t\tEnter contact number to update:");
   scanf("%ld", &contactNumber);
   struct Contact FoundContact = FindByContact(contactNumber);
   if (FoundContact.IsValid)
   {
      struct Contact Copied = FoundContact;
      printf("\t\t\tFirstName : ");
      scanf("%s", Copied.FirstName);
      printf("\t\t\tLastName : ");
      scanf("%s", Copied.LastName);
      printf("\t\t\tEmail : ");
      scanf("%s", Copied.Email);
      printf("\t\t\tContact No : ");
      scanf("%ld", &Copied.Number);
      printf("\t\t\t\t\tFavorite : ");
      scanf("%d", &Favorite);
      contact.IsFavorite = Favorite;
      printf("\t\t\tAddress : ");
      scanf("%s", Copied.Address);
      SaveChanges(Copied);
      if (Remove(FoundContact.Number) == 0)
      {
         printf("\t\t\tSuccessfully updated.");
      }
      View(Copied.FirstName);
   }
   else
   {
      Warning("\t\t\tContact not found");
      Next();
   }
}

int Remove(long ContactNumber)
{
   int flag = 0;
   FILE *fp_temp = FileProvider(temp_store, append);
   FILE *fp = FileProvider(store, read);
   struct Contact removable = FindByContact(ContactNumber);
   if (removable.IsValid)
   {
      while (fread(&contact, sizeof(contact), 1, fp))
      {
         if (removable.Id != contact.Id)
         {
            fwrite(&contact, sizeof(contact), 1, fp_temp);
         }
         else
         {
            flag = 1;
         }
      }
      fclose(fp);
      fclose(fp_temp);
      remove(store);
      rename(temp_store, store);
      return 0;
   }
   return -1;
}

void MarkFavorite(long contactNumber)
{
   struct Contact existingContact = FindByContact(contactNumber);
   if (existingContact.IsValid)
   {
      struct Contact editable = existingContact;
      editable.IsFavorite = 1;
      Remove(existingContact.Number);
      SaveChanges(editable);
   }
   else
   {
      printf("\n\t\t\tContact not found\n");
   }
   Next();
}

void View(char queryFirstName[])
{
   int i = 0;
   int c = 0;
   FILE *fp = FileProvider(store, read);
   struct Contact item;
   struct Contact contacts[] = {};
   if (strlen(queryFirstName) > 1)
   {
      while (fread(&item, sizeof(item), 1, fp))
      {
         if (strcmp(item.FirstName, queryFirstName) == 0)
         {
            contacts[i] = item;
            i++;
         }
      }
   }
   else
   {
      while (fread(&item, sizeof(item), 1, fp))
      {
         contacts[i] = item;
         i++;
      }
   }
   fclose(fp);
   system("cls");
   printf("\t\t\t\t-------------------------------------------------------------\n");
   printf("\t\t\t\t\t\t[ Contact list  - %s ]\n", queryFirstName);
   printf("\t\t\t\t-------------------------------------------------------------\n");
   printf("\n\n\t\t\t\t.....................................................\n\n");
   for (c = 0; c < i; ++c)
   {
      printf("\t\t\t\t\tFullName : %s %s", contacts[c].FirstName, contacts[c].LastName);
      if (contacts[c].IsFavorite)
      {
         printf(" ??");
      }
      printf("\n\t\t\t\t\tNumber: %ld", contacts[c].Number);
      printf("\n\t\t\t\t\tEmail: %s", contacts[c].Email);
      printf("\n\t\t\t\t\tAddress : %s", contacts[c].Address);
      printf("\n\t\t\t\t\tCreated By: %s", contacts[c].RecUserName);
      printf("\n\t\t\t\t\tCreatedAt: %s", contacts[c].CreatedAt);
      printf("\n\n\t\t\t\t.....................................................\n\n");
   }
   Next();
}

int SaveChanges(struct Contact ReqContact)
{
   FILE *fp = FileProvider(store, append);
   if (EnsureUniqueContact(ReqContact.Number) == 1)
   {
      Warning("Duplicate contact number");
      return -1;
   }
   strcpy(ReqContact.CreatedAt, GetCurrentDate());
   ReqContact.IsValid = 1;
   strcpy(ReqContact.RecUserName, admin.UserName);
   ReqContact.Id = rand();
   fwrite(&ReqContact, sizeof(ReqContact), 1, fp);
   fclose(fp);
   return 0;
}

struct Contact FindByContact(long contactNumber)
{
   FILE *fp = FileProvider(store, read);
   struct Contact info;
   while (fread(&info, sizeof(info), 1, fp))
   {
      if (info.Number == contactNumber)
      {
         fclose(fp);
         return info;
      }
   }
   fclose(fp);
   info.IsValid = 0;
   return info;
}

int EnsureUniqueContact(long newNumber)
{
   if (FindByContact(newNumber).IsValid)
   {
      return 1;
   }
   return 0;
}

FILE* FileProvider(char fileName[], char mode[])
{
   FILE * fptr;
   fptr = fopen(fileName, mode);
   if (fptr == NULL)
   {
      fptr = fopen(fileName, mode);
   }
   return fptr;
}

char *GetCurrentDate()
{
   time_t rawtime;
   struct tm * timeinfo;
   time(&rawtime);
   timeinfo = localtime(&rawtime);
   return asctime(timeinfo);
}

void Warning(char message[])
{
   system("cls");
   system("color e");
   printf("\n\t\t\t\t\t%s\n", message);
}

char *GetPassword()
{
   char password[55];
   int p = 0;
   do {
      password[p] = getch();
      if (password[p] != '\r')
      {
         printf("*");
      }
      p++;
   } while (password[p - 1] != '\r');
   password[p - 1] = '\0';
   return password;
}

void CreateInitialStore()
{
   fp = FileProvider(store, append);
   fclose(fp);
   auth_fp = FileProvider(authStore, append);
   fclose(auth_fp);
}
void Title(char title[])
{
   SetConsoleTitle("Contact Management System");
}
void Display(char text[])
{
   printf("\t\t\t-------------------------------------------------------------\n");
   printf("\t\t\t\t\t\t[ %s ]\n", text);
   printf("\t\t\t-------------------------------------------------------------\n");
}
void Next()
{
   printf("\t\t\t\t\tPress[Enter] to continue :: ");
   int command = getch();
   command == 13 ? Dashboard() : exit(1);
}
