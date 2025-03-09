#ifndef CUSTOMER_H
#define CUSTOMER_H

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

// מבנה רכישה – מייצג ספר שנרכש על ידי לקוח
typedef struct Purchase {
    char bookTitle[100];
    char purchaseDate[11];  // DD/MM/YYYY
    struct Purchase* next;
} Purchase;

// מבנה לקוח
typedef struct Customer {
    char name[100];            // שם הלקוח
    struct tm joinDate;        // תאריך ההצטרפות (מבנה struct tm)
    Purchase* purchases;       // רשימת הספרים שנרכשו על ידי הלקוח
    struct Customer* next;     // מצביע ללקוח הבא ברשימה המקושרת
} Customer;

// פרוטוטייפים לפונקציות הקשורות לניהול לקוחות
Customer* createCustomer(const char* name, const struct tm* joinDate);
void loadCustomerData(const char* filename, Customer** head); // במידת הצורך
void saveCustomerData(const char* filename, Customer* head);
void addCustomer(Customer** head, Customer* newCustomer);
void freeList(Customer* head);
void inputCustomerData(Customer** head);
void cusromer_menu();

// פונקציות בדיקה לקלט
int isValidName_customer(const char* name);       // בדיקת שם לקוח תקין (אותיות אנגלית ורווחים בלבד)
int isValidDate_cusromer(const char* date);         // בדיקת תאריך תקין (פורמט DD/MM/YYYY)

// פונקציות להצגת לקוחות וניהול רכישות
void viewCustomers(Customer* head);
int addPurchase(Customer* customer, const char* bookTitle, const char* purchaseDate);
void purchaseBookForCustomer(Customer** head);

int refundBook(Customer* customer, const char* bookTitle, const char* refundDate);
void refundBookForCustomer(Customer** head);

#endif

