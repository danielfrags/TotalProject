#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "employee.h"

int main() {
    Employee employees[MAX_USERS];
    int employeeCount = 0;
    char username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    int permissionLevel;
    int attempts = 0;

    loadEmployees(employees, &employeeCount);

    while (attempts < 3) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        permissionLevel = authenticate(employees, employeeCount, username, password);

        if (permissionLevel) {
            printf("Login successful! Welcome, %s\n", username);
            while (1) {
                showMenu(permissionLevel);
                int choice;
                printf("Select an option: ");
                scanf("%d", &choice);
                if (choice == 4 && permissionLevel == 1) {
                    addEmployee(employees, &employeeCount);
                }
                else if (choice == 5 && permissionLevel == 1) {
                    removeEmployee(employees, &employeeCount);
                }
                else if (choice == 6) {
                    printf("Logging out...\n");
                    break;
                }
                else {
                    printf("Invalid option or insufficient permission.\n");
                }
            }
            return 0;
        }
        else {
            printf("Invalid username or password.\n");
            attempts++;
        }
    }

    printf("Too many failed login attempts. Exiting...\n");
    return 1;
}