#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"
#include "book.h"

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

void loadCustomerData(const char* filename, Customer** head) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing customer data found.\n");
        return;
    }

    char name[100], bookTitle[100], purchaseDate[11];
    int day, month, year, purchaseCount;

    while (fgets(name, sizeof(name), file)) {
        name[strcspn(name, "\n")] = '\0';  // הסרת תו סוף שורה

        if (fscanf(file, "%d/%d/%d\n", &day, &month, &year) != 3) {
            printf("Error reading date from file.\n");
            continue;
        }

        struct tm joinDate = { 0 };
        joinDate.tm_mday = day;
        joinDate.tm_mon = month - 1;
        joinDate.tm_year = year - 1900;

        Customer* newCustomer = createCustomer(name, &joinDate);
        addCustomer(head, newCustomer);

        // ✅ קריאה תקינה של מספר הרכישות
        if (fscanf(file, "%d", &purchaseCount) != 1) {
            printf("Error reading purchase count.\n");
            continue;
        }
        fgetc(file);  // מנקה את ה-`\n` אחרי `fscanf` 

        // ✅ קריאה בטוחה של רכישות
        for (int i = 0; i < purchaseCount; i++) {
            if (!fgets(bookTitle, sizeof(bookTitle), file)) {
                printf("Error reading book title.\n");
                continue;
            }
            bookTitle[strcspn(bookTitle, "\n")] = '\0';

            if (!fgets(purchaseDate, sizeof(purchaseDate), file)) {
                printf("Error reading purchase date for book: %s.\n", bookTitle);
                continue;
            }
            purchaseDate[strcspn(purchaseDate, "\n")] = '\0';

            // ✅ מניעת הכנסה של מחרוזות ריקות
            if (strlen(bookTitle) == 0 || strlen(purchaseDate) == 0) {
                printf("Skipping invalid entry: bookTitle='%s', purchaseDate='%s'\n", bookTitle, purchaseDate);
                continue;
            }

            printf("DEBUG: Loaded purchase -> Book: %s, Date: %s\n", bookTitle, purchaseDate);
            addPurchase(newCustomer, bookTitle, purchaseDate);
        }
    }

    fclose(file);
}



// הוספת לקוח לרשימה המקושרת
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

// שמירת נתוני לקוחות לקובץ
void saveCustomerData(const char* filename, Customer* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file for writing.\n");
        return;
    }

    Customer* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->name);
        fprintf(file, "%02d/%02d/%04d\n", current->joinDate.tm_mday,
            current->joinDate.tm_mon + 1, current->joinDate.tm_year + 1900);

        // שמירת מספר הרכישות
        int purchaseCount = 0;
        Purchase* temp = current->purchases;
        while (temp) {
            purchaseCount++;
            temp = temp->next;
        }
        fprintf(file, "%d\n", purchaseCount);

        // ✅ שמירת שמות הספרים שנרכשו יחד עם תאריך הרכישה
        temp = current->purchases;
        while (temp) {
            fprintf(file, "%s\n%s\n", temp->bookTitle, temp->purchaseDate);
            temp = temp->next;
        }

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
    struct tm joinDate = { 0 };

    // קלט שם הלקוח
    while (1) {
        printf("Enter customer's name (only English letters and spaces allowed): ");
        scanf(" %99[^\n]", name);

        if (isValidName_customer(name)) {
            break;
        }
        else {
            printf("Invalid name. Please enter only English letters and spaces.\n");
        }
    }

    // ניקוי ה-buffer לפני קריאת התאריך
    while (getchar() != '\n');

    // קלט תאריך הצטרפות
    while (1) {
        char date[20];
        printf("Enter join date (DD/MM/YYYY format, e.g., 15/07/2021): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0'; // הסרת תו סוף שורה

        if (isValidDate_cusromer(date)) {
            int day, month, year;
            if (sscanf(date, "%d/%d/%d", &day, &month, &year) == 3) {
                joinDate.tm_mday = day;
                joinDate.tm_mon = month - 1; // התאמת החודש לטווח 0-11
                joinDate.tm_year = year; // התאמת השנה לטווח של `struct tm`
                break;
            }
        }
        printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
    }

    // יצירת הלקוח החדש והוספתו לרשימה
    Customer* newCustomer = createCustomer(name, &joinDate);
    if (newCustomer) {
        addCustomer(head, newCustomer);
        printf("Customer added successfully!\n");
    }
    else {
        printf("Failed to create customer.\n");
    }
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
int addPurchase(Customer* customer, const char* bookTitle, const char* purchaseDate) {
    if (customer == NULL) return 0;

    // ספירת מספר הספרים שנרכשו באותו תאריך
    int count = 0;
    Purchase* temp = customer->purchases;
    while (temp != NULL) {
        if (strcmp(temp->purchaseDate, purchaseDate) == 0) {
            count++;
            if (count >= 3) {
                printf("Customer has already purchased 3 books on this date.\n");
                return 0;  // כישלון - לא ניתן לרכוש ספר נוסף
            }
        }
        temp = temp->next;
    }

    // יצירת רכישה חדשה
    Purchase* newPurchase = (Purchase*)malloc(sizeof(Purchase));
    if (!newPurchase) {
        printf("Memory allocation failed for purchase.\n");
        return 0;
    }
    strcpy(newPurchase->bookTitle, bookTitle);
    strcpy(newPurchase->purchaseDate, purchaseDate);
    newPurchase->next = NULL;

    // הוספת הרכישה לרשימה המקושרת
    if (customer->purchases == NULL) {
        customer->purchases = newPurchase;
    }
    else {
        temp = customer->purchases;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPurchase;
    }
        
    return 1; // הצלחה
}



// תהליך רכישת ספר עבור לקוח קיים – המשתמש מזין את שם הלקוח ושם הספר
void purchaseBookForCustomer(Customer** head) {
    if (*head == NULL) {
        printf("No customers available. Please add a customer first.\n");
        return;
    }

    char customerName[100], bookTitle[100], purchaseDate[11];

    printf("Enter the name of the customer: ");
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

    printf("Enter the title of the book to purchase: ");
    scanf(" %99[^\n]", bookTitle);

    printf("Enter purchase date (DD/MM/YYYY): ");
    scanf(" %10[^\n]", purchaseDate);

    // בדיקת תקינות תאריך
    if (!isValidDate_cusromer(purchaseDate)) {
        printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
        return;
    }

    // הדפסת DEBUG לראות שהתאריך עובר נכון
    printf("DEBUG: Purchase Date Saved -> %s\n", purchaseDate);

    purchaseBook(curr, bookTitle, purchaseDate);
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
        printf("Join Date: %02d/%02d/%04d\n", current->joinDate.tm_mday,
            current->joinDate.tm_mon + 1, current->joinDate.tm_year + 1900);
        printf("Purchased Books:\n");

        if (current->purchases != NULL) {
            Purchase* p = current->purchases;
            while (p != NULL) {
                printf(" - %s (Date: %s)\n", p->bookTitle, p->purchaseDate);
                p = p->next;
            }
        }
        else {
            printf("None\n");
        }
        printf("\n");
        current = current->next;
    }
}

#include <time.h>  // לשימוש בחישובי תאריך

int refundBook(Customer* customer, const char* bookTitle, const char* refundDate) {
    if (!customer || !bookTitle || !refundDate) {
        printf("Invalid input.\n");
        return 0;
    }

    // בדיקת האם הספר קיים ברשימת הרכישות של הלקוח
    Purchase* temp = customer->purchases;
    Purchase* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->bookTitle, bookTitle) == 0) {
            // חישוב מספר הימים שעברו מהרכישה
            struct tm purchase_tm = { 0 }, refund_tm = { 0 };
            sscanf(temp->purchaseDate, "%d/%d/%d", &purchase_tm.tm_mday, &purchase_tm.tm_mon, &purchase_tm.tm_year);
            sscanf(refundDate, "%d/%d/%d", &refund_tm.tm_mday, &refund_tm.tm_mon, &refund_tm.tm_year);

            purchase_tm.tm_mon -= 1; // התאמת חודש (0-11)
            purchase_tm.tm_year -= 1900; // התאמת שנה
            refund_tm.tm_mon -= 1;
            refund_tm.tm_year -= 1900;

            time_t purchase_time = mktime(&purchase_tm);
            time_t refund_time = mktime(&refund_tm);
            double daysDiff = difftime(refund_time, purchase_time) / (60 * 60 * 24);

            printf("the daysdiff is: %d", daysDiff);
            // בדיקה אם עברו פחות מ-14 ימים
            if (daysDiff <= 14) {
                printf("Refund approved. '%s' will be removed from %s's purchases and returned to stock.\n", bookTitle, customer->name);

                // מחיקת הרכישה מרשימת הרכישות של הלקוח
                if (prev == NULL) {
                    customer->purchases = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                free(temp);

                // החזרת הספר למלאי
                Book* book = head;
                while (book) {
                    if (strcmp(book->title, bookTitle) == 0) {
                        book->stock++;
                        break;
                    }
                    book = book->next;
                }
                return 1; // הצלחה
            }
            else {
                printf("Refund denied. More than 14 days have passed since the purchase.\n");
                return 0; // כישלון - עברו 14 ימים
            }
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Refund failed. Book not found in customer's purchase history.\n");
    return 0;
}

void refundBookForCustomer(Customer** head) {
    if (*head == NULL) {
        printf("No customers available.\n");
        return;
    }

    char customerName[100], bookTitle[100], refundDate[11];

    printf("Enter the name of the customer: ");
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

    printf("Enter the title of the book to refund: ");
    scanf(" %99[^\n]", bookTitle);

    printf("Enter refund date (DD/MM/YYYY): ");
    scanf(" %10[^\n]", refundDate);

    // בדיקת תקינות התאריך
    if (!isValidDate_cusromer(refundDate)) {
        printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
        return;
    }

    refundBook(curr, bookTitle, refundDate);
}


// תפריט הלקוחות – מאפשר לבצע פעולות: הוספת לקוח, תצוגה, רכישת ספר, שמירת נתונים ויציאה
void cusromer_menu() {
    Customer* head = NULL;
    loadCustomerData("customers.txt", &head);

    int choice_customer;

    do {
        printf("\nCustomers Menu:\n");
        printf("1. Add New Customer\n");
        printf("2. View Customers\n");
        printf("3. Purchase Book\n");
        printf("4. Refund Book\n");  // נוספה אפשרות החזרה
        printf("5. Save Customer Data to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice_customer);

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
            refundBookForCustomer(&head);  // קריאה לפונקציה החדשה
            break;
        case 5:
            saveCustomerData("customers.txt", head);
            break;
        case 6:
            freeList(head);
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice_customer != 6);
}

