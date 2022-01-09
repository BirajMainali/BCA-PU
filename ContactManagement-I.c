#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include<conio.h>

#define max 100

#define write "w"
#define read "r"
#define append "a"

#define store "contact.txt"
#define temp_store "contact_temp.txt"
#define authStore "auth.txt"

struct Contact {
    int Id;
    long Number;
    int IsFavourite;
    char FirstName[max];
    char LastName[max];
    char Email[max];
    char Address[max];
    char CreatedAt[max];
}contact;

struct Admin {
    char UserName[max];
    char Password[max];
    char ConfirmPassword[max];
};

void Next();
void CreateInitialStore();
char* GetPassword();
void RegisterUser();
void Login();
void Dashboard();
void Create();
void Update();
int Remove(long contactNumber);
void MaskAsFavourite(long contactNumber);
void View(char queryFirstName[]);
int SaveChanges(struct Contact Reqcontact);
struct Contact * FindByContact(long contactNumber);
int EnsureUniqueContact(long newNumber);
char * GetCurrentDate();
void Warning(char message[]);
void EnsureUniqueUserName(char username[]);
FILE* FileProvider(char fileName[], char mode[]);

FILE * fp;

FILE *auth_fp;
long ContactNumber;
int main() {
	system("color a");
	CreateInitialStore();
     int choice;
     top:
     printf("======================================\n");
     printf("[1] Login\n");
     printf("[2] Register\n");
     printf("Enter your choice :: ");
     scanf("%d", & choice);
     switch (choice) {
     case 1:
         Login();
         break;
     case 2:
         RegisterUser();
         break;
     default:
         printf("Invalid choice");
         goto top;
     }
    return 0;
}

void RegisterUser() {
    struct Admin admin;    
    char confirmPassword[max];
    printf("Enter username : ");
    scanf("%s", admin.UserName);
    printf("Enter Password :");
   strcpy(admin.Password, GetPassword());
    printf("\nEnter ConfirmPassword :");
    strcpy(confirmPassword, GetPassword());
    EnsureUniqueUserName(admin.UserName);
    if (strcmp(admin.Password, confirmPassword) != 0) {
        printf("Confirm password is not matching");
        RegisterUser();
    }
    
    auth_fp = FileProvider(authStore, append);
    fwrite(&admin, sizeof(admin), 1, auth_fp);
    fclose(auth_fp);
    printf("%s successfully registered\n\n", admin.UserName);
    Login();
}

void EnsureUniqueUserName(char username[]) {
    struct Admin admin;
    auth_fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0) {
            Warning("user aleady exist");
			RegisterUser();
        }
    }
    fclose(auth_fp);
}

void Login() {
    struct Admin admin;
    char username[max], password[max];
    top:
    printf("UserName :: ");
    scanf("%s", username);
    printf("Passwords:: ");
    strcpy(password, GetPassword());
    auth_fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0 && strcmp(admin.Password, password) == 0) {
        	fclose(auth_fp);
            Dashboard();
        }
    }
    system("cls");
     printf("Invalid username or password\n");
     fclose(auth_fp);
     goto top;
}

void Dashboard() {
	system("cls");
    int Choice;
    char query[max];
    Menu:
    printf("\n==========================================================\n");
    printf("\n========================:: Menu ::=======================\n");
    printf("\n==========================================================\n\n");
    printf("1. Add Contact\n");
    printf("2. View Contact\n");
    printf("3. Search Contact\n");
    printf("4. Update Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Favorite\n");
    printf("Enter your choice: ");
    scanf("%d", & Choice);
    switch (Choice) {
        case 1:
            Create();
            break;
        case 2:
            View("");
            break;
        case 3:
            printf("Enter name to filter : ");
            scanf("%s", query);
            View(query);
            break;
        case 4:
            Update();
            break;
        case 5:
            printf("Enter contact number to remove:");
            scanf("%ld", & ContactNumber);
            if (Remove(ContactNumber) == 0) {
                printf("Contact removed successfully");
            } else {
                printf("Contact not found");
            }
        case 6:
            printf("Contact Number:");
            scanf("%ld", & ContactNumber);
            MaskAsFavourite(ContactNumber);
            break;
        default:
            Warning("Invalid Choice");
            goto Menu;
            break;
    }
}

void Create() {
    system("cls");
    printf("[1] For Favourite");
    printf("\n*********************************\n");
    printf("FirstName : ");
    scanf("%s", contact.FirstName);
    printf("LastName : ");
    scanf("%s", contact.LastName);
    printf("Email : ");
    scanf("%s", contact.Email);
    printf("Contact No : ");
    scanf("%ld", & contact.Number);
    printf("Address : ");
    scanf("%s", & contact.Address);
    printf("Favorite : ");
    scanf("%d", &contact.IsFavourite);
    if(SaveChanges(contact) == 0){
        printf("Contact added successfully");
    }
    else {
        printf("Contact not added");
        
    }
	Next();
}

void Update() {
    long contactNumber;
    printf("Enter contact number to update:");
    scanf("%ld", &contactNumber);
    struct Contact * FoundContact = FindByContact(contactNumber);
    if (FoundContact != NULL) {
        struct Contact * WorkableContact = FoundContact;
        printf("FirstName : ");
        scanf("%s", ( * WorkableContact).FirstName);
        printf("LastName : ");
        scanf("%s", ( * WorkableContact).LastName);
        printf("Email : ");
        scanf("%s", ( * WorkableContact).Email);
        printf("Contact No : ");
        scanf("%ld", & ( * WorkableContact).Number);
        printf("Address : ");
        scanf("%s",( * WorkableContact).Address);
        SaveChanges(*WorkableContact);
        if(Remove((*FoundContact).Number)==0){
        	printf("Successfully updated.");
		}
        View("");
    } else {
        Warning("Contact not found");
        Next();
    }
}

int Remove(long ContactNumber) {
    int flag = 0;
    FILE * fp_temp;
    struct Contact * removable = FindByContact(ContactNumber);
    fp = FileProvider(store, read);
    fp_temp = FileProvider(temp_store, append);
    if (removable != NULL) {
        while (fread( & contact, sizeof(contact), 1, fp)) {
            if (( * removable).Id != contact.Id) {
                fwrite( & contact, sizeof(contact), 1, fp_temp);
            } else {
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

void MaskAsFavourite(long contactNumber) {
    struct Contact * existingContact = FindByContact(contactNumber);
    if (existingContact != NULL) {
        struct Contact * editable = existingContact;
        (*editable).IsFavourite = 1;
        Remove((*existingContact).Id);
        SaveChanges(*editable);
    } else {
        printf("\nContact not found");
    }
    Next();
}

void View(char queryFirstName[]) {
    int i = 0;
    int c = 0;
    struct Contact item;
    struct Contact contacts[] = {};
    fp = FileProvider(store, read);
    if (strlen(queryFirstName) > 1) {
        while (fread( & item, sizeof(item), 1, fp)) {
            if (strcmp(item.FirstName, queryFirstName) == 0) {
                contacts[i] = item;
                i++;
            }
        }
    } else {
        while (fread( & item, sizeof(item), 1, fp)) {
            contacts[i] = item;
            i++;
        }
    }
    fclose(fp);
    printf("\n\n======================================\n\n");
    for (c = 0; c < i; ++c) {
        printf("FullName : %s %s", contacts[c].FirstName, contacts[c].LastName);
        printf("\nNumber: %ld", contacts[c].Number);
        printf("\nEmail: %s", contacts[c].Email);
        printf("\nCreatedAt: %s", contacts[c].CreatedAt);
        printf("\nAddress : %s", contacts[c].Address);
        if (contacts[c].IsFavourite == 1) {
            printf("#");
        }
        printf("\n\n======================================\n\n");
    }
    Next();
}

int SaveChanges(struct Contact ReqContact) {
    if (EnsureUniqueContact(ReqContact.Number) == 1) {
        Warning("Duplicate contact number");
        return -1;
    }
    strcpy(ReqContact.CreatedAt,GetCurrentDate());
    ReqContact.Id = rand();
    fp = FileProvider(store, append);
    fwrite(&ReqContact, sizeof(ReqContact), 1, fp);
    fclose(fp);
    return 0;
}

struct Contact * FindByContact(long contactNumber) {
    fp = FileProvider(store, read);
    struct Contact x;
    while (fread( & x, sizeof(x), 1, fp)) {
        if (x.Number == contactNumber) {
            fclose(fp);
            return &x;
        }
    }
    fclose(fp);
    return NULL;
}

int EnsureUniqueContact(long newNumber) {
    if (FindByContact(newNumber) != NULL) {
        return 1;
    }
    return 0;
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

char* GetPassword() {
    char password[55];
    int p=0;
    do{
        password[p]=getch();
        if(password[p]!='\r') {
            printf("*");
        }
        p++;
    }while(password[p-1]!='\r');
    password[p-1]='\0';
    return password;
}

void CreateInitialStore(){
	fp = FileProvider(store, append);
    fclose(fp);
    auth_fp = FileProvider(authStore, append);
    fclose(auth_fp);
}
void Next() {
	printf("\n\nPress [Enter] to continue :: ");
	int command = getch();
	command == 13 ? Dashboard() : exit(1);
}
