#include <stdio.h>
#include "customer.h"

#define _CRT_SECURE_NO_WARNINGS

int main() {
    Customer* head = NULL;

    // ����� ������
    int choice;
    char buffer[10];

    do {
        printf("\nMenu:\n");
        printf("1. Add New Customer\n");
        printf("2. View Customers\n");
        printf("3. Save Customer Data to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf_s(buffer, "%d", &choice);

        switch (choice) {
        case 1:
            inputCustomerData(&head);
            break;
        case 2:
            viewCustomers(head);
            break;
        case 3:
            saveCustomerData("customers.txt", head);
            break;
        case 4:
            freeList(head);
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
