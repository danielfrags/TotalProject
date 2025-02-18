#define _CRT_SECURE_NO_WARNINGS
#define MAX_USERS 100
#define MAX_ITEMS 100
#define MAX_NAME_LEN 50

// מבנה נתונים לעובדים
typedef struct {
    char username[MAX_NAME_LEN];
    char firstName[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int permissionLevel; // 1 - מנהל, 2 - עובד, 3 - מתלמד
} Employee;

void loadEmployees(Employee employees[], int* count);
int authenticate(Employee employees[], int count, char username[], char password[]);
void showMenu(int permissionLevel);
void addEmployee(Employee employees[], int* count);
void saveEmployees(Employee employees[], int count);


