#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "book.h"

int main() {
    load_books(); // טוען ספרים מהקובץ
    int choice;
    do {
        printf("\nBookstore Menu:\n1. Add Book\n2. Display Books\n3. Edit/Remove Book\n4. Search Book\n5. Save & Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add_book();
            break;
        case 2:
            display_books();
            break;
        case 3:
            edit_or_remove_book();
            break;
        case 4:
            printf("\nSearch Options:\n1. By Title or Author\n2. By Minimum Price\n3. By Bestseller\n4. By Publication Date\n5. By Maximum Price\n6. By Stock\nEnter choice: ");
            int search_choice;
            scanf("%d", &search_choice);
            char keyword[100];
            float price;

            switch (search_choice) {
            case 1:
                printf("Enter title or author keyword: ");
                scanf(" %99[^\n]", keyword);
                search_by_title_or_author(keyword);
                break;
            case 2:
                printf("Enter minimum price: ");
                scanf("%f", &price);
                search_by_min_price(price);
                break;
            case 3:
                search_by_bestseller();
                break;
            case 4:
                printf("Enter publication date (DD/MM/YYYY): ");
                scanf(" %10[^\n]", keyword);
                search_by_date(keyword);
                break;
            case 5:
                printf("Enter maximum price: ");
                scanf("%f", &price);
                search_by_max_price(price);
                break;
            case 6:
                search_by_stock();
                break;
            default:
                printf("Invalid search choice.\n");
            }
            break;
        case 5:
            save_books();
            printf("Data saved. Exiting.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
    return 0;
}
