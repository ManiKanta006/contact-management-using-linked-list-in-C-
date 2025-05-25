#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Contact {
    long ph;
    char name[20], add[20], email[30];
    struct Contact *next;
};
struct Contact *head = NULL;
int isValidPhone(long ph) {
    int count = 0;
    while (ph) {
        ph /= 10;
        count++;
    }
    return count == 10;
}
int isValidEmail(char *email) {
    return strchr(email, '@') != NULL;
}
void addContact() {
    struct Contact *newContact = (struct Contact*)malloc(sizeof(struct Contact));
    getchar();
    printf("\nEnter Name: ");
    fgets(newContact->name, sizeof(newContact->name), stdin);
    newContact->name[strcspn(newContact->name, "\n")] = 0;
    printf("Contact (10-digit number): ");
    scanf("%ld", &newContact->ph);
    while (!isValidPhone(newContact->ph)) {
        printf("Invalid phone number! Enter 10 digits: ");
        scanf("%ld", &newContact->ph);
    }
    getchar();  // Clear newline after number input
    printf("Address: ");
    fgets(newContact->add, sizeof(newContact->add), stdin);
    newContact->add[strcspn(newContact->add, "\n")] = 0;
    printf("Email: ");
    fgets(newContact->email, sizeof(newContact->email), stdin);
    newContact->email[strcspn(newContact->email, "\n")] = 0;
    while (!isValidEmail(newContact->email)) {
        printf("Invalid email! It must contain '@'.\nEnter Email: ");
        fgets(newContact->email, sizeof(newContact->email), stdin);
        newContact->email[strcspn(newContact->email, "\n")] = 0;
    }
    newContact->next = head;
    head = newContact;
    printf("Contact added successfully.\n");
}
void sortContactsByName() {
    struct Contact *i, *j;
    char tempName[20], tempAdd[20], tempEmail[30];
    long tempPh;
    if (head == NULL || head->next == NULL) return;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcasecmp(i->name, j->name) > 0) {
                // Swap name
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
                // Swap phone
                tempPh = i->ph;
                i->ph = j->ph;
                j->ph = tempPh;
                // Swap address
                strcpy(tempAdd, i->add);
                strcpy(i->add, j->add);
                strcpy(j->add, tempAdd);
                // Swap email
                strcpy(tempEmail, i->email);
                strcpy(i->email, j->email);
                strcpy(j->email, tempEmail);
            }
        }
    }
}
void listContacts() {
    struct Contact *temp = head;
    if (!temp) {
        printf("\nNo contacts to display.\n");
        return;
    }
    sortContactsByName();
    printf("\n--- Contact List (Alphabetical Order) ---\n");
    int index = 1;
    while (temp) {
        printf("\n[%d] Name   : %s\n", index++, temp->name);
        printf("     Phone  : %ld\n", temp->ph);
        printf("     Address: %s\n", temp->add);
        printf("     Email  : %s\n", temp->email);
        printf("----------------------------------------");
        temp = temp->next;
    }
    printf("\n");
}
void searchContact() {
    char searchName[20];
    int found = 0;
    getchar();
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    struct Contact *temp = head;
    while (temp) {
        if (strcasecmp(temp->name, searchName) == 0) {
            printf("\nName   : %s\nPhone  : %ld\nAddress: %s\nEmail  : %s\n",
                temp->name, temp->ph, temp->add, temp->email);
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        printf("Contact not found.\n");
}
void deleteContact() {
    char delName[20];
    getchar();
    printf("Enter name to delete: ");
    fgets(delName, sizeof(delName), stdin);
    delName[strcspn(delName, "\n")] = 0;
    struct Contact *temp = head, *prev = NULL;
    while (temp) {
        if (strcasecmp(temp->name, delName) == 0) {
            if (prev)
                prev->next = temp->next;
            else
                head = temp->next;
            free(temp);
            printf("Contact deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Contact not found.\n");
}
void editContact() {
    char editName[20];
    getchar();
    printf("Enter name to edit: ");
    fgets(editName, sizeof(editName), stdin);
    editName[strcspn(editName, "\n")] = 0;
    struct Contact *temp = head;
    while (temp) {
        if (strcasecmp(temp->name, editName) == 0) {
            printf("\nEnter new details:\n");
            printf("Name: ");
            fgets(temp->name, sizeof(temp->name), stdin);
            temp->name[strcspn(temp->name, "\n")] = 0;
            printf("Contact (10-digit): ");
            scanf("%ld", &temp->ph);
            while (!isValidPhone(temp->ph)) {
                printf("Invalid! Enter 10-digit number: ");
                scanf("%ld", &temp->ph);
            }
            getchar();
            printf("Address: ");
            fgets(temp->add, sizeof(temp->add), stdin);
            temp->add[strcspn(temp->add, "\n")] = 0;
            printf("Email: ");
            fgets(temp->email, sizeof(temp->email), stdin);
            temp->email[strcspn(temp->email, "\n")] = 0;
            while (!isValidEmail(temp->email)) {
                printf("Invalid email! Try again: ");
                fgets(temp->email, sizeof(temp->email), stdin);
                temp->email[strcspn(temp->email, "\n")] = 0;
            }
            printf("Contact updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Contact not found.\n");
}
int main() {
    int choice;
    do {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n2. List Contacts\n3. Search Contact\n");
        printf("4. Edit Contact\n5. Delete Contact\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addContact(); break;
            case 2: listContacts(); break;
            case 3: searchContact(); break;
            case 4: editContact(); break;
            case 5: deleteContact(); break;
            case 0: printf("Exiting... Goodbye!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
    return 0;
}