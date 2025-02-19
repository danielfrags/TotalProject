#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book.h"

int main() {
    load_books();//טוען ספרים מהקובץ
    int choice;
    do {
        printf("\nBookstore Menu:\n1. Add Book\n2. Display Books\n3. Edit/Remove Book\n4. Save & Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: add_book(); break;
        case 2: display_books(); break;
        case 3: edit_or_remove_book(); break;
        case 4: save_books(); printf("Data saved. Exiting.\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
    return 0;
}
