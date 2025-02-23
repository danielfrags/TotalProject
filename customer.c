#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"



// פונקציה ליצירת לקוח חדש
Customer* createCustomer(const char* name, const struct tm* joinDate) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(newCustomer->name, name);
    newCustomer->joinDate = *joinDate;
    newCustomer->next = NULL;
    return newCustomer;
}

// פונקציה להוספת לקוח חדש לרשימה המקושרת
void addCustomer(Customer** head, Customer* newCustomer) {
    if (*head == NULL) {
        *head = newCustomer;
    }
    else {
        Customer* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

// פונקציה לשמירת נתוני הלקוחות לקובץ
void saveCustomerData(const char* filename, Customer* head) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Unable to open the file for writing.\n");
        return;
    }

    Customer* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->name);
        fprintf(file, "%d/%d/%d\n", current->joinDate.tm_mday, current->joinDate.tm_mon + 1, current->joinDate.tm_year + 1900);
        current = current->next;
    }

    fclose(file);
}

// פונקציה לשחרור זיכרון של כל רשימת הלקוחות
void freeList(Customer* head) {
    Customer* current = head;
    while (current != NULL) {
        Customer* temp = current;
        current = current->next;
        free(temp);
    }
}

// פונקציה להכניס נתוני לקוח דרך הקלט מהמשתמש
void inputCustomerData(Customer** head) {
    char name[100];
    struct tm joinDate = { 0 };

    // קלט שם הלקוח עם הגבלה
    while (1) {
        printf("Enter customer's name (only English letters and spaces allowed): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';  // הסרת תו סיום שורה

        if (isValidName_customer(name)) {
            break; // שם תקין
        }
        else {
            printf("Invalid name. Please enter only English letters and spaces.\n");
        }
    }

    // קלט תאריך הצטרפות עם הגבלה
    while (1) {
        char date[20];
        printf("Enter join date (DD/MM/YYYY format, e.g., 15/07/2021): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0'; // הסרת תו סיום שורה

        if (isValidDate_cusromer(date)) {
            sscanf_s(date, "%d/%d/%d", &joinDate.tm_mday, &joinDate.tm_mon, &joinDate.tm_year);
            joinDate.tm_mon--; // חודשי שנה הם בין 0 ל-11
            break;
        }
        else {
            printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
        }
    }

    // יצירת לקוח חדש והוספה לרשימה
    Customer* newCustomer = createCustomer(name, &joinDate);
    addCustomer(head, newCustomer);
}

// פונקציה לאימות שם הלקוח
int isValidName_customer(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != ' ') {
            return 0; // שם לא תקין
        }
    }
    return 1; // שם תקין
}

// פונקציה לאימות תאריך הצטרפות
int isValidDate_cusromer(const char* date) {
    int day, month, year;
    return sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3 &&
        day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900;
}

// פונקציה להצגת פרטי הלקוחות
void viewCustomers(Customer* head) {
    if (head == NULL) {
        printf("No customers available.\n");
        return;
    }
    Customer* current = head;
    while (current != NULL) {
        printf("\nName: %s\n", current->name);
        printf("Join Date: %d/%d/%d\n", current->joinDate.tm_mday, current->joinDate.tm_mon + 1, current->joinDate.tm_year + 1900);
        current = current->next;
    }
}

void cusromer_menu() {
    Customer* head = NULL;

    // תפריט המשתמש
    int choice_customer;
    char buffer[10];

    //printf("\nCustomers Menu's:\n");
    //printf("1. Add New Customer\n");
    //printf("2. View Customers\n");
    //printf("3. Save Customer Data to File\n");
    //printf("4. Exit\n");
    //printf("Enter your choice: ");

    do {
        printf("\nCustomers Menu's:\n");
        printf("1. Add New Customer\n");
        printf("2. View Customers\n");
        printf("3. Save Customer Data to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf_s(buffer, "%d", &choice_customer);

        switch (choice_customer) {
        case 1:
            inputCustomerData(&head);
            break;
        case 2:
            viewCustomers(head);
            break;
        case 3:
            saveCustomerData("customers.txt", head);
            break;
        case 4:
            freeList(head);
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice_customer != 4);

    return 0;
}

