#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#define max 100
#define write "w"
#define read "r"
#define append "a"


const char InActive = 'Y';
const char Active = 'N';
const int True = 1;
const int False = 0;
const char store[max] = "contact.txt";
const char temp_store[max] = "contact_temp.txt";

struct Contact {
  int Id;
  char FirstName[max];
  char LastName[max];
  char Email[max];
  long Number;
  char Address[max];
  char IsFavourite;
  char * CreatedAt;
}
contact;

FILE * FileProvider(char fileName[], char mode[]);
char * GetCurrentDate();
int EnsureUniqueContact(long newNumber);
void Warning(char message[]);

void Create(struct Contact contact);
void Update();
int SaveChanges(struct Contact contact)
void Queryable(char queryFirstName[]);
struct Contact FindByContact(long contactNumber);
void MaskAsFavourite(long contactNumber);
int Remove(long contactNumber);
struct Contact FindByContact(long contactNumber);

FILE * fp;
long ContactNumber;
int main() {
  int Choice;
  char query[max];
  Menu:
  printf("-----------------Menu------------------\n");
  printf("1. Add Contact\n");
  printf("2. View Contact\n");
  printf("3. Search Contact\n");
  printf("4. Update Contact\n");
  printf("5. Delete Contact\n");
  printf("Enter your choice: ");
  scanf("%d", & Choice);
  switch (Choice) {
  case 1:
    Create();
    break;
  case 2:
      Queryable("");
    break;
  case 3:
      printf("Enter name to filter : ");
      scanf("%s",query);
      Queryable(query);
    break;
  case 4:
    Update();
    break;
  case 5:
    printf("Enter contact number to remove:");
    scanf("%ld", & ContactNumber);
    if (Remove(ContactNumber) != 200) {
      printf("Contact removed successfully");
    } else {
      printf("Somethings went wrong while removing the contact");
    }
    case 6:
      printf("Enter contact number to remove:");
      scanf("%ld", & ContactNumber);
      MaskAsFavourite(ContactNumber);
      break;
    default:
      Warning("Invalid Choice");
      break;
  }
  return 0;
}

void Create(struct Contact contact) {
  top: system("cls");
  printf("Enter FirstName : ");
  scanf("%s", contact.FirstName);
  printf("Enter LastName : ");
  scanf("%s", contact.LastName);
  printf("Enter Email : ");
  scanf("%s", contact.Email);
  printf("Enter Contact No : ");
  scanf("%ld", & contact.Number);
  printf("Enter Address : ");
  gets(contact.Address);
  if (EnsureUniqueContact(contact.Number) == 1) {
    Warning("Duplicate Contcat Number");
    goto top;
  }
  contact.CreatedAt = GetCurrentDate();
  contact.Id = rand();
  SaveChanges(contact);
}

void Update() {
    long contactNumber;
    printf("Enter contact number to update:");
    scanf("%ld", & contactNumber);
    struct Contact FoundContact = FindByContact(contactNumber);
    if(FoundContact != NUll) {
        struct Contact WorkableContact = FoundContact;
        printf("Enter FirstName : ");
        scanf("%s", WorkableContact.FirstName);
        printf("Enter LastName : ");
        scanf("%s", WorkableContact.LastName);
        printf("Enter Email : ");
        scanf("%s", WorkableContact.Email);
        printf("Enter Contact No : ");
        scanf("%ld", & WorkableContact.Number);
        printf("Enter Address : ");
        gets(WorkableContact.Address);
        WorkableContact.Id = rand();
        SaveChanges(WorkableContact);
        Remove(FoundContact.Number);
        printf("Successfully updated.");
        View();
    }else{
        Warning("Contact not found");
        main();
    }
}

void Queryable(char queryFirstName[]) {
    int i = 0;
    struct Contact contacts[10000];
    fp = FileProvider(store,read);
    if (strlen(queryFirstName) > 1) {
        while (fread(&contact, sizeof(contact), 1, fp)) {
            if (strcmp(contact.FirstName, queryFirstName) == 0) {
                contacts[i] = contact;
                i++;
            }
        }
    }else {
        while (fread(&contact, sizeof(contact), 1, fp)) {
            contacts[i] = contact;
            i++;
        }
    }
    fclose(fp);
    printf("\nFullName \t\tNumber\t\tEmail \t\tCreatedAt\t\t\t Address\t\t\t Favorite \n\n");
    for (int c = 0; c < i; ++c) {
        printf("%s %s", contacts[i].FirstName, contacts[i].LastName);
        printf("\t\t%ld", contacts[i].Number);
        printf("\t\t%s", contacts[i].Email);
        printf("\t\t%s", contacts[i].CreatedAt);
        printf("%s\n\n", contacts[i].Address);
        if(contacts[i].IsFavourite == Active){
            printf("💓");
        }
    }
}

void MaskAsFavourite(long contactNumber) {
    printf("Enter favourite contact Number");
    scanf("%ld", & contactNumber);
    struct Contact existingContact = FindByContact(contactNumber);
    if (existingContact != Null) {
        struct Contact editable = existingContact;
        editable.IsFavourite = Active;
        Remove(existingContact.Id);
        SaveChanges(editable);
    } else {
        printf("\nContact not found");
    }
}


int Remove(long ContactNumber) {
    int flag = 0;
    FILE * fp_temp;
    struct Contact removable = FindByContact(ContactNumber);
    fp = FileProvider(store, read);
    fp_temp = FileProvider(store, append);
    if(removable != Null) {
        while (fread( & contact, sizeof(contact), 1, fp)) {
            if (removable.Id != contact.Id) {
                fwrite( & contact, sizeof(contact), 1, fp_temp);
            } else {
                flag = 1;
            }
        }
        fclose(fp);
        fclose(fp_temp);
        remove(store);
        rename(temp_store, store);
    }
}

struct Contact FindByContact(long contactNumber) {
  struct Contact emptyContact;
  fp = FileProvider(store, read);
  while (fread( & contact, sizeof(contact), 1, fp)) {
    if (contact.Number == contactNumber) {
		fclose(fp);	
      return contact;
    }
  }
  fclose(fp);
  return emptyContact;
}

int EnsureUniqueContact(long newNumber) {
    struct Contact existing = FindByContact(newNumber);
    if (existing != Null) {
        return 1;
    }
    return 0;
}

int SaveChanges(struct Contact contact) {
    if(EnsureUniqueContact(contact.Number) == 1) {
        Warning("Duplicate contact number");
        main();
    }
    fp = FileProvider(store,append);
    fwrite( & contact, sizeof(contact), 1, fp);
    fclose(fp);
}

FILE * FileProvider(char fileName[], char mode[]) {
    FILE * fptr;
    fptr = fopen(fileName, mode);
    if (fptr == NULL) {
        fptr = fopen(fileName, mode);
    }
    return fptr;
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
}
