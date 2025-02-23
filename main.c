#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "employee.h"
#include "book.h"
#include "customer.h"

int main() {
    Employee employees[MAX_USERS];
    int employeeCount = 0;
    char username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    int permissionLevel;
    int attempts = 0;

    load_books();
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
                if (choice == 3 && permissionLevel == 1) {
                    addEmployee(employees, &employeeCount);
                }
                else if (choice == 4 && permissionLevel == 1) {
                    removeEmployee(employees, &employeeCount);
                }
                else if (choice == 1) {
                    books_menu(permissionLevel);
                }
                else if (choice == 2) {
                    cusromer_menu();
                }
                else if (choice == 5) {
                    printf("Saved\n");
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