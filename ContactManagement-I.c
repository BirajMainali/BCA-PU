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


const int True = 1;
const int False = 0;

struct Contact {
    int Id;
    char FirstName[max];
    char LastName[max];
    char Email[max];
    char Address[max];
    long Number;
    int IsFavourite;
    char CreatedAt[max];
}contact;

struct Admin {
    char UserName[max];
    char Password[max];
    char ConfirmPassword[max];
};


void CreateInitialStore();
char* GetPassword();
void RegisterUser();
void Login();
void Dashboard();
void Create();
void Update();
int Remove(long contactNumber);
void MaskAsFavourite(long contactNumber);
void Queryable(char queryFirstName[]);
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
     default:
         printf("Invalid choice");
         goto top;
     }
    return 0;
}

void RegisterUser() {
	
    // [Todo] Validate password lenght min 5 character which include number,latter,symbols,uppercase latter.
    struct Admin admin;    
    char confirmPassword[max];
    
    printf("Enter username : ");
    scanf("%s", admin.UserName);
   strcpy(admin.Password, GetPassword());
    printf("Enter Confirm : ");
    strcpy(confirmPassword, GetPassword());
    EnsureUniqueUserName(admin.UserName);
    if (strcmp(admin.Password, confirmPassword) != 0) {
        printf("Confirm password is not matching");
        RegisterUser();
    }
    
    auth_fp = FileProvider(authStore, append);
    fwrite(&admin, sizeof(admin), 1, auth_fp);
    fclose(auth_fp);
    printf("%s successfully registered", admin.UserName);
    Login();
}

void EnsureUniqueUserName(char username[]) {
    struct Admin admin;
    auth_fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0) {
            Warning("user aleady exist");
			main();
        }
    }
    fclose(auth_fp);
}

void Login() {
    struct Admin admin;
    char username[max], password[max];
    top:
    printf("UserName :");
    scanf("%s", username);
    strcpy(password, GetPassword());
    auth_fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0 && strcmp(admin.Password, password) == 0) {
        	fclose(auth_fp);
            Dashboard();
        }
    }
     printf("Invalid UserName or password");
     fclose(auth_fp);
     goto top;
}

void Dashboard() {
    int Choice;
    char query[max];
    Menu:
    printf("\n\n-----------------Menu------------------\n");
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
            Queryable("");
            break;
        case 3:
            printf("Enter name to filter : ");
            scanf("%s", query);
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
            printf("Contact Number:");
            scanf("%ld", & ContactNumber);
            MaskAsFavourite(ContactNumber);
            break;
        default:
            Warning("Invalid Choice");
            break;
    }
}


// [todo] create new Contact structure for create.
// [todo] Add IsFavourite while adding new contact. Y denotes for yes. N denotes for no.
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
    printf("Favourite : ");
    scanf("%d", contact.IsFavourite);
    SaveChanges(contact);
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
        Remove((*FoundContact).Number);
        printf("Successfully updated.");
        Queryable("");
    } else {
        Warning("Contact not found");
        Dashboard();
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
        main();
    }
}

void MaskAsFavourite(long contactNumber) {
    struct Contact * existingContact = FindByContact(contactNumber);
    if (existingContact != NULL) {
        struct Contact * editable = existingContact;
        ( * editable).IsFavourite = 'Y';
        Remove((*existingContact).Id);
        SaveChanges( * editable);
    } else {
        printf("\nContact not found");
    }
}

void Queryable(char queryFirstName[]) {
    int i = 0;
    int c = 0;
    struct Contact item;
    struct Contact contacts[10000];
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
}

int SaveChanges(struct Contact ReqContact) {
    printf("%ld", ReqContact.Number);
    if (EnsureUniqueContact(ReqContact.Number) == 1) {
        Warning("Duplicate contact number");
    }
    strcpy(ReqContact.CreatedAt,GetCurrentDate());
    ReqContact.Id = rand();
    fp = FileProvider(store, append);
    fwrite( & ReqContact, sizeof(ReqContact), 1, fp);
    fclose(fp);
    Queryable("");
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

void CreateInitialStore(){
	fp = FileProvider(store, append);
    fclose(fp);
    auth_fp = FileProvider(authStore, append);
    fclose(auth_fp);
}
char* GetPassword()
{
    char password[55];
    printf("password:");
    int p=0;
    do{
        password[p]=getch();
        if(password[p]!='\r'){
            printf("*");
        }
        p++;
    } while(password[p-1]!='\r');
    password[p-1]='\0';
    return password;
}
