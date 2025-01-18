#pragma once

typedef struct employee {
    char username[20];
    char firstname[10];
    char password[10];
    unsigned int level; // 1 - admin, 2 - employee, 3 - practicioner
} Employee;


int checkIfEmployeeFileExists();
void createDefaultAdmin();
Employee login();