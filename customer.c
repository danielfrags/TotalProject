#include "customer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// ������� ������ ���� ���
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

// ������� ������ ���� ��� ������ �������
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

// ������� ������ ����� ������� �����
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

// ������� ������ ������ �� �� ����� �������
void freeList(Customer* head) {
    Customer* current = head;
    while (current != NULL) {
        Customer* temp = current;
        current = current->next;
        free(temp);
    }
}

// ������� ������ ����� ���� ��� ���� �������
void inputCustomerData(Customer** head) {
    char name[100];
    struct tm joinDate = { 0 };

    // ��� �� ����� �� �����
    while (1) {
        printf("Enter customer's name (only English letters and spaces allowed): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';  // ���� �� ���� ����

        if (isValidName(name)) {
            break; // �� ����
        }
        else {
            printf("Invalid name. Please enter only English letters and spaces.\n");
        }
    }

    // ��� ����� ������� �� �����
    while (1) {
        char date[20];
        printf("Enter join date (DD/MM/YYYY format, e.g., 15/07/2021): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0'; // ���� �� ���� ����

        if (isValidDate(date)) {
            sscanf_s(date, "%d/%d/%d", &joinDate.tm_mday, &joinDate.tm_mon, &joinDate.tm_year);
            joinDate.tm_mon--; // ����� ��� �� ��� 0 �-11
            break;
        }
        else {
            printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
        }
    }

    // ����� ���� ��� ������ ������
    Customer* newCustomer = createCustomer(name, &joinDate);
    addCustomer(head, newCustomer);
}

// ������� ������ �� �����
int isValidName(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != ' ') {
            return 0; // �� �� ����
        }
    }
    return 1; // �� ����
}

// ������� ������ ����� �������
int isValidDate(const char* date) {
    int day, month, year;
    return sscanf_s(date, "%d/%d/%d", &day, &month, &year) == 3 &&
        day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900;
}

// ������� ����� ���� �������
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
