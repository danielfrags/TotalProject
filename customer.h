#define CUSTOMER_H

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

// מבנה לקוח
typedef struct Customer {
    char name[100];            // שם הלקוח
    struct tm joinDate;       // תאריך הצטרפות (בפורמט struct tm)
    struct Customer* next;    // מצביע ללקוח הבא ברשימה המקושרת
} Customer;

// הצהרת פונקציות
Customer* createCustomer(const char* name, const struct tm* joinDate);
void loadCustomerData(const char* filename, Customer** head);
void saveCustomerData(const char* filename, Customer* head);
void addCustomer(Customer** head, Customer* newCustomer);
void freeList(Customer* head);
void inputCustomerData(Customer** head);  // פונקציה להזנת נתונים עבור לקוח חדש

// פונקציות לאימות נתונים
int isValidName_customer(const char* name);       // לבדוק אם שם הלקוח תקין (רק אותיות באנגלית)
int isValidDate_cusromer(const char* date);       // לבדוק אם התאריך תקין (פורמט DD/MM/YYYY)

// פונקציה להצגת פרטי הלקוחות
void viewCustomers(Customer* head);

void cusromer_menu();
