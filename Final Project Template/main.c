#include "employees.h"
#include "menu.h"
#include <stdio.h>

int main() {
    if (!checkIfEmployeeFileExists()) {
        createDefaultAdmin();
    }

    Employee currentEmployee = login();
    if (currentEmployee.level == 0) {
        printf("Login failed. Try again later..\n");
        return 0;
    }

    showMenu(currentEmployee.level);
    return 0;
}
