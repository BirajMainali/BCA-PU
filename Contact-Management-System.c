#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<conio.h>

#define _max 100
#define write "w"
#define read "r"
#define append "a"
#define store "contact.bat"
#define temp_store "contact_temp.bat"
#define authStore "auth.bat"

struct Contact {
    int Id;
    char Number[_max];
    bool IsFavorite;
    char FirstName[_max];
    char LastName[_max];
    char Email[_max];
    char Address[_max];
    char CreatedAt[_max];
    char RecUserName[_max];
    bool IsValid;
};

struct Admin {
    char UserName[_max];
    char Password[_max];
};
void RegisterUser();

void Login();

void Dashboard();

void CreateContactDetail();

void UpdateContactDetail();

void CurrnetUserContcatList();

void Details(struct Contact contact);

int RemoveContact(char contactNumber[]);

void MarkFavorite(long contactNumber);

void ViewContactList(char queryFirstName[]);

int SaveChanges(struct Contact Reqcontact);

struct Contact FindByContact(char contactNumber[]);

int EnsureUniqueContact(char newNumber[]);

char *GetCurrentDate();

void Warning(char message[]);

void EnsureUniqueUserName(char username[]);

void Next();

void Display(char text[]);

void CreateInitialStore();

char *GetPassword();


FILE *FileProvider(char fileName[], char mode[]);

FILE *fp;

FILE *auth_fp;
char Username[_max];
char ContactNumber[];
int Favorite;

int main() {
    system("Color F2");
    CreateInitialStore();
    SetConsoleTitle("Contact Management System");
    int choice;
    top:
    Display("Welcome to CMS");
    printf("\t\t\t[1] Login\n");
    printf("\t\t\t[2] Register\n");
    printf("\t\t\tEnter your choice :: ");
    scanf("%d", &choice);
    switch (choice) {
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

void RegisterUser() {
    struct Admin admin;
    char confirmPassword[_max];
    Display("Register User");
    printf("\t\t\tEnter username : ");
    scanf("%s", admin.UserName);
    printf("\t\t\tEnter Password :");
    strcpy(admin.Password, GetPassword());
    printf("\n\t\t\tEnter ConfirmPassword :");
    strcpy(confirmPassword, GetPassword());
    EnsureUniqueUserName(admin.UserName);
    if (strcmp(admin.Password, confirmPassword) != 0) {
        printf("\t\t\tConfirm password is not matching");
        RegisterUser();
    }
    auth_fp = FileProvider(authStore, append);
    fwrite(&admin, sizeof(admin), 1, auth_fp);
    fclose(auth_fp);
    printf("%s\n\t\t\tsuccessfully registered\n\n", admin.UserName);
    Login();
}

void EnsureUniqueUserName(char username[]) {
	struct Admin admin;
    auth_fp = FileProvider(authStore, read);
    while (fread(&admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0) {
            Warning("\t\t\tuser aleady exist");
            RegisterUser();
        }
    }
    fclose(auth_fp);
}

void Login() {
	struct Admin admin;
    char username[_max], password[_max];
    top:
    Display("Login");
    printf("\t\t\tUserName :: ");
    scanf("%s", username);
    printf("\t\t\tPasswords:: ");
    strcpy(password, GetPassword());
    auth_fp = FileProvider(authStore, read);
    while (fread(&admin, sizeof(admin), 1, auth_fp)) {
        if (strcmp(admin.UserName, username) == 0 && strcmp(admin.Password, password) == 0) {
            fclose(auth_fp);
            strcpy(Username, username);
            Dashboard();
        }
    }
    system("cls");
    printf("\nInvalid username or password\n");
    fclose(auth_fp);
    goto top;
}

void Dashboard() {
    system("cls");
    int Choice;
    char query[_max];
    Menu:
    Display("Contact Management system");
    printf("\t\t\t\t\t1. Add Contact\n");
    printf("\t\t\t\t\t2. View Contact\n");
    printf("\t\t\t\t\t3. Search Contact\n");
    printf("\t\t\t\t\t4. Update Contact\n");
    printf("\t\t\t\t\t5. Delete Contact\n");
    printf("\t\t\t\t\t6. Favorite\n");
    printf("\t\t\t\t\t7. View my Contact\n");
    printf("\t\t\t\t\t8. Logout\n\n");
    printf("\t\t\t\t\tEnter your choice: ");
    scanf("%d", &Choice);
    switch (Choice) {
        case 1:
            CreateContactDetail();
            break;
        case 2:
            ViewContactList("");
            break;
        case 3:
            system("cls");
            Display("Sort contact list by name");
            printf("\t\t\t\t\t Name : ");
            scanf("%s", query);
            ViewContactList(query);
            break;
        case 4:
            system("cls");
            Display("Update Contact");
            UpdateContactDetail();
            break;
        case 5:
            system("cls");
            Display("Remove contact");
            printf("\t\t\t\tEnter contact number to remove: ");
            scanf("%s", ContactNumber);
            struct Contact info = FindByContact(ContactNumber);
            if (info.IsValid) {
                Details(info);
                printf("\t\t\t\t\tPress[Y] to Remove :: ");
                int command = getch();
                if(command == 89){
                	RemoveContact(info.Number);
                	printf("\n\t\t\tContact removed successfully");
				}
				else {
					goto Menu;	
				}
            } else {
                printf("\n\t\t\tContact not found");
            }
        case 6:
            system("cls");
            Display("Mark as favorite");
            printf("\t\t\tContact Number:");
            scanf("%s", &ContactNumber);
            MarkFavorite(ContactNumber);
            break;
        case 7:
        	Display("My contact list");
			CurrnetUserContcatList();    
			Next();
			break;
		  case 8:
        	main();
			break;	
        default:
            Warning("Invalid Choice");
            goto Menu;
            break;
    }
}

void CreateContactDetail() {
	struct Contact contact;
    Display("Add new contact");
    printf("\t\t\tEnter First Name : ");
    scanf("%s", contact.FirstName);
    fflush(stdin);
    printf("\t\t\tEnter Last Name : ");
    scanf("%s", contact.LastName);
    fflush(stdin);
    printf("\t\t\tEnter Email : ");
    scanf("%s", contact.Email);
    fflush(stdin);
    printf("\t\t\tEnter Contact No : ");
    scanf("%[^\n]s", &contact.Number);
    fflush(stdin);
    printf("\t\t\tEnter Address : ");
    scanf("%[^\n]s", &contact.Address);
    fflush(stdin);
    printf("\t\t\tIs Favorite : ");
    scanf("%d", &Favorite);
    fflush(stdin);
    contact.IsFavorite = Favorite;
    if (SaveChanges(contact) == 0) {
        printf("\t\t\tContact added successfully\n");
    } else {
        printf("\t\t\tContact not added\n");
    }
    Next();
}

void UpdateContactDetail() {
	struct Contact contact;
    long contactNumber;
    printf("\t\t\tEnter contact number to update: ");
    scanf("%s", &contactNumber);
    struct Contact FoundContact = FindByContact(contactNumber);
    if (FoundContact.IsValid) {
        struct Contact Copied = FoundContact;
        printf("\t\t\tEnter First Name : ");
        scanf("%s", contact.FirstName);
        fflush(stdin);
        printf("\t\t\tEnter Last Name : ");
        scanf("%s", contact.LastName);
        fflush(stdin);
        printf("\t\t\tEnter Email : ");
        scanf("%s", contact.Email);
        fflush(stdin);
        printf("\t\t\tEnter Contact No : ");
        scanf("%[^\n]s", &contact.Number);
        fflush(stdin);
        printf("\t\t\tEnter Address : ");
        scanf("%[^\n]s", &contact.Address);
        fflush(stdin);
        printf("\t\t\tIs Favorite : ");
        scanf("%d", &Favorite);
        fflush(stdin);
        contact.IsFavorite = Favorite;
        SaveChanges(Copied);
        if (RemoveContact(FoundContact.Number) == 0) {
            printf("\t\t\tSuccessfully updated.");
        }
        Details(Copied);
    } else {
        Warning("\t\t\tContact not found");
        Next();
    }
}

int RemoveContact(char ContactNumber[]) {
    int flag = 0;
    struct Contact contact;
    FILE *fp_temp = FileProvider(temp_store, append);
    FILE *fp = FileProvider(store, read);
    struct Contact removable = FindByContact(ContactNumber);
    if (removable.IsValid) {
        while (fread(&contact, sizeof(contact), 1, fp)) {
            if (removable.Id != contact.Id) {
                fwrite(&contact, sizeof(contact), 1, fp_temp);
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

void MarkFavorite(long contactNumber) {
    struct Contact existingContact = FindByContact(contactNumber);
    if (existingContact.IsValid) {
        struct Contact editable = existingContact;
        editable.IsFavorite = 1;
        RemoveContact(existingContact.Number);
        SaveChanges(editable);
    } else {
        printf("\n\t\t\tContact not found\n");
    }
    Next();
}

void ViewContactList(char queryFirstName[]) {
    Display("Contact List");
    FILE *fp = FileProvider(store, read);
    struct Contact item;
    if (strlen(queryFirstName) > 1) {
        while (fread(&item, sizeof(item), 1, fp)) {
            if (strcmp(item.FirstName, queryFirstName) == 0) {
                Details(item);
            }
        }
    } else {
        while (fread(&item, sizeof(item), 1, fp)) {
        	Details(item);
        }
    }
    fclose(fp);
    Next();
}

void CurrnetUserContcatList() {
	FILE *fp = FileProvider(store, read);
	struct Contact authContact;
	while(fread(&authContact, sizeof(authContact),1,fp)){
		if(strcmp(Username,authContact.RecUserName) == 0) {
			Details(authContact);
		}
	}
	fclose(fp);
}


void Details(struct Contact contact) {

    printf("\n\t\t\t\tFullName : %s %s ", contact.FirstName, contact.LastName);
    if (contact.IsFavorite) {
        printf("#Favorite");
    }
    printf("\n\t\t\t\tNumber: %s ", contact.Number);
    printf("\n\t\t\t\tEmail: %s ", contact.Email);
    printf("\n\t\t\t\tAddress : %s ", contact.Address);
    printf("\n\t\t\t\tCreated By: %s ", contact.RecUserName);
    printf("\n\t\t\t\tCreatedAt: %s ", contact.CreatedAt);
    printf("\n\n\t\t\t\t------------------------------------------------\n");
}

int SaveChanges(struct Contact ReqContact) {
    FILE *fp = FileProvider(store, append);
    if (EnsureUniqueContact(ReqContact.Number) == 1) {
        Warning("Duplicate contact number");
        return -1;
    }
    strcpy(ReqContact.CreatedAt, GetCurrentDate());
    ReqContact.IsValid = 1;
    strcpy(ReqContact.RecUserName, Username);
    ReqContact.Id = rand();
    fwrite(&ReqContact, sizeof(ReqContact), 1, fp);
    fclose(fp);
    return 0;
}

struct Contact FindByContact(char contactNumber[]) {
    FILE *fp = FileProvider(store, read);
    struct Contact info;
    while (fread(&info, sizeof(info), 1, fp)) {
    	if(strcmp(info.Number,contactNumber)==0){
    		fclose(fp);
            return info;
		}
    }
    fclose(fp);
    info.IsValid = 0;
    return info;
}

int EnsureUniqueContact(char newNumber[]) {
    if (FindByContact(newNumber).IsValid) {
        return 1;
    }
    return 0;
}

FILE *FileProvider(char fileName[], char mode[]) {
    FILE *fptr;
    fptr = fopen(fileName, mode);
    if (fptr == NULL) {
        fptr = fopen(fileName, mode);
    }
    return fptr;
}

char *GetCurrentDate() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return asctime(timeinfo);
}

void Warning(char message[]) {
    system("cls");
    printf("\n\t\t\t%s\n", message);
}

char *GetPassword() {
    char password[50];
    int i = 0;
    int c;
    for (;;) {
        c = getch();
        if (c == 13) break;
        if (c == 8) continue;
        password[i] = c;
        i++;
        printf("*");
    }
    password[i] = '\0';
    return password;
}

void CreateInitialStore() {
    fp = FileProvider(store, append);
    fclose(fp);
    auth_fp = FileProvider(authStore, append);
    fclose(auth_fp);
}

void Display(char text[]) {
    system("cls");
    printf("\t\t\t-------------------------------------------------------------\n");
    printf("\t\t\t\t[ %s - Login: %s ]\n", text, Username);
    printf("\t\t\t-------------------------------------------------------------\n\n");
}
void Next() {
    printf("\n\t\t\tPress[Enter] to continue :: ");
    int command = getch();
    command == 13 ? Dashboard() : exit(1);
}
