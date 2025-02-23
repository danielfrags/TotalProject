#define CUSTOMER_H

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

// ���� ����
typedef struct Customer {
    char name[100];            // �� �����
    struct tm joinDate;       // ����� ������� (������ struct tm)
    struct Customer* next;    // ����� ����� ��� ������ �������
} Customer;

// ����� ��������
Customer* createCustomer(const char* name, const struct tm* joinDate);
void loadCustomerData(const char* filename, Customer** head);
void saveCustomerData(const char* filename, Customer* head);
void addCustomer(Customer** head, Customer* newCustomer);
void freeList(Customer* head);
void inputCustomerData(Customer** head);  // ������� ����� ������ ���� ���� ���

// �������� ������ ������
int isValidName_customer(const char* name);       // ����� �� �� ����� ���� (�� ������ �������)
int isValidDate_cusromer(const char* date);       // ����� �� ������ ���� (����� DD/MM/YYYY)

// ������� ����� ���� �������
void viewCustomers(Customer* head);

void cusromer_menu();
