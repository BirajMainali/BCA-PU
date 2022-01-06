#include<stdio.h>

#include<stdlib.h>

#include <time.h>

#include<string.h>

#define max 100
#define write "w"
#define read "r"
#define append "a"
#define store "contact.txt"
#define authStore "auth.txt"
#define temp_store "contact_temp.txt"

const int True = 1;
const int False = 0;

struct Contact {
    int Id;
    char FirstName[max];
    char LastName[max];
    char Email[max];
    char Address[max];
    long Number;
    char IsFavourite;
    char CreatedAt;
}
        contact;

struct Admin {
    char UserName[max];
    char Password[max];
    char ConfirmPassword[max];
};

void RegisterUser();
void Login();
void Dashboard()
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

        FILE * fp;
        long ContactNumber;
                int main() {
    fp = FileProvider(store, append);
    fclose(fp);
    fp = FileProvider(authStore, append);
    fclose(fp);
    int choice;
    printf("======================================");
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
            AdminLayout();
    }
    return 0;
}

void RegisterUser() {
    struct Admin admin;
    char confirmPassword[max];
    printf("Enter username : ");
    scanf("%s", admin.UserName);
    printf("Enter username : ");
    scanf("%s", admin.Password);
    printf("Enter username : ");
    scanf("%s", & ConfirmPassword);
    EnsureUniqueUserName(admin.UserName);
    if (strcmp(admin.password, confirmPassword) == 0) {
        printf("Confirm password is not matching");
        RegisterUser();
    }
    fp = FileProvider(authStore, append);
    fwrite( & admin, sizeof(admin), 1, fp);
    fclose(fp);
    printf("%s successfully registered", admin.UserName);
}

void EnsureUniqueUserName(char username[]) {
    struct Admin admin;
    fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, fp)) {
        if (strcmp(admin.UserName, username) != 0) {
            Warning("user aleady exist");
            AdminLayout();
        }
    }
    fclose(fp);
}

void Login() {
    struct Admin admin;
    char username[max], password[max];
    printf("UserName :");
    scanf("%s", username);
    printf("UserName :");
    scanf("%s", password);
    fp = FileProvider(authStore, read);
    while (fread( & admin, sizeof(admin), 1, fp)) {
        if (strcmp(admin.UserName, username) == 0 && strcmp(admin.Password, password) == 0) {
            Dashboard();
        }
        printf("Invalid UserName or password");
        Login();
    }
}

void Dashboard() {
    int Choice;
    char query[max];
    Menu:
    printf("-----------------Menu------------------\n");
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

void Create() {
    system("cls");
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
    SaveChanges(contact);
}

void Update() {
    long contactNumber;
    printf("Enter contact number to update:");
    scanf("%ld", & contactNumber);
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
        gets(( * WorkableContact).Address);
        SaveChanges( * WorkableContact);
        Remove(( * FoundContact).Number);
        printf("Successfully updated.");
        Queryable("");
    } else {
        Warning("Contact not found");
        main();
    }
}

int Remove(long ContactNumber) {
    int flag = 0;
    FILE * fp_temp;
    struct Contact * removable = FindByContact(ContactNumber);
    fp = FileProvider(store, read);
    fp_temp = FileProvider(store, append);
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
    }
}

void MaskAsFavourite(long contactNumber) {
    struct Contact * existingContact = FindByContact(contactNumber);
    if (existingContact != NULL) {
        struct Contact * editable = existingContact;
        ( * editable).IsFavourite = 'Y';
        Remove(( * existingContact).Id);
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
    printf("\n\n======================================\n\n");
    for (c = 0; c < i; ++c) {
        printf("FullName : %s %s", contacts[i].FirstName, contacts[i].LastName);
        printf("\nNumber: %ld", contacts[i].Number);
        printf("\nEmail: %s", contacts[i].Email);
        printf("\nCreatedAt: %s", contacts[i].CreatedAt);
        printf("\nAddress : %s", contacts[i].Address);
        if (contacts[i].IsFavourite == Active) {
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
    ReqContact.CreatedAt = GetCurrentDate();
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
