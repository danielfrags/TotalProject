#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"



// פונקציה לטעינת עובדים מקובץ
void loadEmployees(Employee employees[], int* count) {
    FILE* file = fopen("employees.txt", "r");
    if (!file) {
        printf("Creating new employees file...\n");
        file = fopen("employees.txt", "w");
        if (file) {
            fprintf(file, "admin manager 12345678 1\n");
            fclose(file);
        }
    }
    else {
        *count = 0;
        while (fscanf(file, "%s %s %s %d", employees[*count].username, employees[*count].firstName, employees[*count].password, &employees[*count].permissionLevel) == 4) {
            (*count)++;
        }
        fclose(file);
    }
}

//פונקציה לשמירת משתמש
void saveEmployees(Employee employees[], int count) {
    FILE* file = fopen("employees.txt", "w");
    if (!file) {
        printf("Error saving employees!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %d\n", employees[i].username, employees[i].firstName, employees[i].password, employees[i].permissionLevel);
    }
    fclose(file);
}

//פונקציה להוספת עובד
void addEmployee(Employee employees[], int* count) {
    if (*count >= MAX_USERS) {
        printf("Cannot add more employees, limit reached.\n");
        return;
    }
    printf("Enter new employee username: ");
    scanf("%s", employees[*count].username);
    printf("Enter first name: ");
    scanf("%s", employees[*count].firstName);
    printf("Enter password: ");
    scanf("%s", employees[*count].password);
    printf("Enter permission level (1-Manager, 2-Worker, 3-Trainee): ");
    scanf("%d", &employees[*count].permissionLevel);
    (*count)++;
    saveEmployees(employees, *count);
    printf("Employee added successfully!\n");
}

// פונקציה להסרת עובד
void removeEmployee(Employee employees[], int* count) {
    char username[MAX_NAME_LEN];
    printf("Enter the username of the employee to remove: ");
    scanf("%s", username);

    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(employees[i].username, username) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        employees[i] = employees[i + 1];
    }
    (*count)--;
    saveEmployees(employees, *count);
    printf("Employee removed successfully!\n");
}


// פונקציה לאימות משתמש
int authenticate(Employee employees[], int count, char username[], char password[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0) {
            return employees[i].permissionLevel;
        }
    }
    return 0;
}

// תפריט בהתאם לרמת הרשאה
void showMenu(int permissionLevel) {
    printf("\nMenu:\n");
    printf("1. Books Menu's\n2. Custumers Menu's\n");
//    if (permissionLevel <= 2) {
//        printf("2. Update Item\n");
//    }
    if (permissionLevel == 1) {
        printf("3. Add Employee\n");
        printf("4. Remove Employee\n");
    }
//    printf("5. Add Item\n6. Search Book\n");
    printf("5. Save & Exit\n");
}