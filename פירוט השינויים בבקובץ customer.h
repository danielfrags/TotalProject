
#ifndef CUSTOMER_H
#define CUSTOMER_H

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

// מבנה רכישה – מייצג ספר שנרכש על ידי לקוח
typedef struct Purchase {
    char bookTitle[100];
    struct Purchase* next;
} Purchase;

// מבנה לקוח
typedef struct Customer {
    char name[100];            // שם לקוח
    struct tm joinDate;        // תאריך הצטרפות (מבנה struct tm)
    Purchase *purchases;       // רשימת ספרים שנרכשו על ידי הלקוח
    struct Customer* next;     // מצביע ללקוח הבא ברשימה המקושרת
} Customer;

// פרוטוטייפים לפונקציות הקשורות ללקוח
Customer* createCustomer(const char* name, const struct tm* joinDate);
void loadCustomerData(const char* filename, Customer** head);
void saveCustomerData(const char* filename, Customer* head);
void addCustomer(Customer** head, Customer* newCustomer);
void freeList(Customer* head);
void inputCustomerData(Customer** head);  // קלט נתוני לקוח חדש

// פונקציות בדיקה
int isValidName_customer(const char* name);       // בדיקת שם לקוח תקין (אותיות אנגליות ורווחים בלבד)
int isValidDate_cusromer(const char* date);         // בדיקת תאריך תקין (פורמט DD/MM/YYYY)

// פונקציות תצוגה וניהול רכישות
void viewCustomers(Customer* head);
void purchaseBookForCustomer(Customer **head);     // פונקציה להזנת רכישת ספר ללקוח

#endif
