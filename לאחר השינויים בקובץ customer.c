#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"

// יצירת לקוח חדש
Customer* createCustomer(const char* name, const struct tm* joinDate) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(newCustomer->name, name);
    newCustomer->joinDate = *joinDate;
    newCustomer->purchases = NULL; // אתחול רשימת רכישות
    newCustomer->next = NULL;
    return newCustomer;
}

// הוספת לקוח לרשימה המקושרת
void addCustomer(Customer** head, Customer* newCustomer) {
    if (*head == NULL) {
        *head = newCustomer;
    } else {
        Customer* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

// שמירת נתוני לקוחות לקובץ
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
        // כאן ניתן להוסיף שמירה של רשימת רכישות במידת הצורך
        current = current->next;
    }
    
    fclose(file);
}

// שחרור הזיכרון של רשימת הלקוחות ורשימת הרכישות עבור כל לקוח
void freeList(Customer* head) {
    Customer* current = head;
    while (current != NULL) {
        // שחרור רשימת הרכישות
        Purchase* p = current->purchases;
        while (p != NULL) {
            Purchase* tempP = p;
            p = p->next;
            free(tempP);
        }
        Customer* temp = current;
        current = current->next;
        free(temp);
    }
}

// קלט נתוני לקוח חדש מהמשתמש והוספתו לרשימה
void inputCustomerData(Customer** head) {
    char name[100];
    struct tm joinDate = {0};

    while (1) {
        printf("Enter customer's name (only English letters and spaces allowed): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';  // הסרת תו סוף שורה

        if (isValidName_customer(name)) {
            break;
        } else {
            printf("Invalid name. Please enter only English letters and spaces.\n");
        }
    }
    
    while (1) {
        char date[20];
        printf("Enter join date (DD/MM/YYYY format, e.g., 15/07/2021): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0';
        
        if (isValidDate_cusromer(date)) {
            sscanf_s(date, "%d/%d/%d", &joinDate.tm_mday, &joinDate.tm_mon, &joinDate.tm_year);
            joinDate.tm_mon--; // התאמת חודש (0-11)
            break;
        } else {
            printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
        }
    }
    
    Customer* newCustomer = createCustomer(name, &joinDate);
    addCustomer(head, newCustomer);
}

// בדיקת שם לקוח תקין (אותיות אנגלית ורווחים בלבד)
int isValidName_customer(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] < 'A' || name[i] > 'Z') &&
            (name[i] < 'a' || name[i] > 'z') &&
            name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// בדיקת תאריך תקין (פורמט DD/MM/YYYY)
int isValidDate_cusromer(const char* date) {
    int day, month, year;
    return sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3 &&
           day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900;
}

// הוספת רכישה ללקוח – הוספת שם הספר לרשימת הרכישות של הלקוח
void addPurchase(Customer* customer, const char* bookTitle) {
    if (customer == NULL) return;
    Purchase* newPurchase = (Purchase*)malloc(sizeof(Purchase));
    if (!newPurchase) {
        printf("Memory allocation failed for purchase.\n");
        return;
    }
    strcpy(newPurchase->bookTitle, bookTitle);
    newPurchase->next = NULL;
    
    if (customer->purchases == NULL) {
        customer->purchases = newPurchase;
    } else {
        Purchase* temp = customer->purchases;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPurchase;
    }
    printf("Purchase recorded: %s\n", bookTitle);
}

// תהליך רכישת ספר עבור לקוח קיים – המשתמש מזין את שם הלקוח ושם הספר
void purchaseBookForCustomer(Customer** head) {
    if (*head == NULL) {
        printf("No customers available. Please add a customer first.\n");
        return;
    }
    char customerName[100];
    printf("Enter the name of the customer who is purchasing: ");
    scanf(" %99[^\n]", customerName);
    
    Customer* curr = *head;
    while (curr != NULL) {
        if (strcmp(curr->name, customerName) == 0) {
            break;
        }
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Customer not found.\n");
        return;
    }
    
    char bookTitle[100];
    printf("Enter the title of the book to purchase (from search): ");
    scanf(" %99[^\n]", bookTitle);
    addPurchase(curr, bookTitle);
}

// תצוגת כל הלקוחות: מציג את שם הלקוח, תאריך ההצטרפות ורשימת שמות הספרים שנרכשו (מופרדים בפסיקים)
void viewCustomers(Customer* head) {
    if (head == NULL) {
        printf("No customers available.\n");
        return;
    }
    Customer* current = head;
    while (current != NULL) {
        printf("\nName: %s\n", current->name);
        printf("Join Date: %d/%d/%d\n", current->joinDate.tm_mday, 
               current->joinDate.tm_mon + 1, current->joinDate.tm_year + 1900);
        printf("Purchased Books: ");
        if (current->purchases != NULL) {
            Purchase* p = current->purchases;
            while (p != NULL) {
                printf("%s", p->bookTitle);
                if (p->next != NULL) {
                    printf(", ");
                }
                p = p->next;
            }
        } else {
            printf("None");
        }
        printf("\n");
        current = current->next;
    }
}

// תפריט הלקוחות – מאפשר לבצע פעולות: הוספת לקוח, תצוגה, רכישת ספר, שמירת נתונים ויציאה
void cusromer_menu() {
    Customer* head = NULL;
    int choice_customer;
    char buffer[10];

    do {
        printf("\nCustomers Menu's:\n");
        printf("1. Add New Customer\n");
        printf("2. View Customers\n");
        printf("3. Purchase Book\n");
        printf("4. Save Customer Data to File\n");
        printf("5. Exit\n");
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
                purchaseBookForCustomer(&head);
                break;
            case 4:
                saveCustomerData("customers.txt", head);
                break;
            case 5:
                freeList(head);
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice_customer != 5);
}

