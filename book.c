#define _CRT_SECURE_NO_WARNINGS
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Book* head = NULL; // ����� ������ �� �����

void add_book() {
    Book* new_book = (Book*)malloc(sizeof(Book));
    if (!new_book) {
        printf("Memory allocation failed!\n");
        return;
    }

    char input[20];
    do {
        printf("Enter catalog number (numbers only): ");
        scanf("%s", input);
    } while (!isValidNumber(input));
    new_book->catalog_number = atoi(input);

    do {
        printf("Enter title: ");
        scanf(" %100[^\n]", new_book->title);
        if (!isValidName(new_book->title)) {
            printf("Invalid title! Only letters and spaces are allowed.\n");
        }
    } while (!isValidName(new_book->title));

    do {
        printf("Enter author: ");
        scanf(" %100[^\n]", new_book->author);
        if (!isValidName(new_book->author)) {
            printf("Invalid author name! Only letters and spaces are allowed.\n");
        }
    } while (!isValidName(new_book->author));

    do {
        printf("Enter price (numbers only): ");
        scanf("%s", input);
        if (!isValidNumber(input)) {
            printf("Invalid price! Enter a valid number.\n");
        }
    } while (!isValidNumber(input));
    new_book->price = atof(input);//atof ���� ������ �����

    printf("Is it Topsaler (1 for Yes, 0 for No): ");
    scanf("%d", (int*)&new_book->topsale);

    do {
        printf("Enter publication date (DD/MM/YYYY): ");
        scanf(" %11[^\n]", new_book->publication_date);
        if (!isValidDate(new_book->publication_date)) {
            printf("Invalid date! Please enter a valid date in format DD/MM/YYYY.\n");
        }
    } while (!isValidDate(new_book->publication_date));

    do {
        printf("Enter number of books in stock (numbers only): ");
        scanf("%s", input);
    } while (!isValidNumber(input));
    new_book->stock = atoi(input);

    new_book->next = head;
    head = new_book;

    sort_books(); // ���� ������ ���� �����
}



void display_books() {
    sort_books();  // ���� ������ ���� �����
    Book* temp = head;
    if (!temp) {
        printf("No books available.\n");
        return;
    }

    while (temp) {
        printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nbooks in stock: %d\n",
            temp->catalog_number, temp->title, temp->author, temp->price,
            temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
        temp = temp->next;
    }
}

void sort_books() {
    if (!head || !head->next) return; // �� ������ ���� �� ��� �� ��� ���, ��� ���� �����

    bool swapped;
    Book* ptr1, * prev, * temp_head = NULL;

    do {
        swapped = false;
        ptr1 = head;
        prev = NULL;

        while (ptr1->next != temp_head) {
            // �� ����� ������� ���� ���� ��� �� ���� ���, ������� ������
            if (ptr1->catalog_number > ptr1->next->catalog_number) {
                Book* temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;

                if (prev) {
                    prev->next = temp;
                }
                else {
                    head = temp; // ������� �� ��� ������ �� ����
                }

                swapped = true;
                prev = temp;
            }
            else {
                prev = ptr1;
                ptr1 = ptr1->next;
            }
        }
        temp_head = ptr1; // ��� ������� ������ ������ ��� ������ �����
    } while (swapped);
}


void save_books() {
    sort_books(); // ���� ������ ���� ������

    FILE* file = fopen("books.bin", "wb");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    Book* temp = head;
    while (temp) {
        fwrite(temp, sizeof(Book), 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void load_books() {
    FILE* file = fopen("books.bin", "rb");
    if (!file) {
        printf("No previous data found.\n");
        return;
    }

    Book temp;
    while (fread(&temp, sizeof(Book), 1, file)) {
        Book* new_book = (Book*)malloc(sizeof(Book));
        if (!new_book) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }
        *new_book = temp;
        new_book->next = head;
        head = new_book;
    }
    fclose(file);
}

void edit_or_remove_book() {
    int catalog_number, choice;
    printf("Enter catalog number of the book to edit or remove: ");
    scanf("%d", &catalog_number);


    Book* temp = head;
    Book* prev = NULL;

    // ����� ���� ������
    while (temp != NULL && temp->catalog_number != catalog_number) {
        prev = temp;
        temp = temp->next;
    }

    // �� ���� �� ����
    if (temp == NULL) {
        printf("Book with catalog number %d not found.\n", catalog_number);
        return;
    }

    // ����� ����� �� �����
    printf("\n1. Edit Title\n2. Edit Author\n3. Edit Price\n4. Edit Hardcover\n5. Edit Publication Date\n6. Edit Number of stock\n7. Remove Book\n8. Cancel\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Enter new title: ");
        scanf(" %99[^\n]", temp->title);
        break;
    case 2:
        printf("Enter new author: ");
        scanf(" %99[^\n]", temp->author);
        break;
    case 3:
        printf("Enter new price: ");
        scanf("%f", &temp->price);
        break;
    case 4:
        printf("Is it Topsaler (1 for Yes, 0 for No): ");
        scanf("%d", (int*)&temp->topsale);
        break;
    case 5:
        printf("Enter new publication date (DD-MM-YYYY): ");
        scanf(" %10[^\n]", temp->publication_date);
        break;
    case 6:
        printf("Enter new number of books in stock: ");
        scanf("%d", &temp->stock);
        break;
    case 7:
        // ���� ���� �������
        if (prev == NULL) {
            head = temp->next;
        }
        else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Book removed successfully.\n");
        break;
    case 8:
        printf("Action cancelled.\n");
        break;
    default:
        printf("Invalid choice.\n");
    }
}

// ������� ������ �� ��� ���� (���� �� ������ �������)
int isValidName(const char* name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != ' ') {
            return 0; // �� �� ����
        }
    }
    return 1; // �� ����
}

// ������� ������ �����
int isValidDate(const char* date) {
    int day, month, year;
    return sscanf(date, "%d/%d/%d", &day, &month, &year) == 3 &&
        day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900;
}

// ������� ������ �� ��� ���� �� ������
int isValidNumber(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '.') { // ���� �� ������ �������
            return 0;
        }
    }
    return 1;
}

void search_book() {

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
}


void search_by_title_or_author(const char* query) {
    Book* temp = head;
    int found = 0;
    while (temp) {
        if (strstr(temp->title, query) || strstr(temp->author, query)) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nBooks in stock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price,
                temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found matching '%s'.\n", query);
    }
}

void search_by_min_price(float min_price) {
    Book* temp = head;
    int found = 0;
    while (temp) {
        if (temp->price >= min_price) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nStock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price,
                temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found with minimum price of: %.2f.\n", min_price);
    }
}

void search_by_max_price(float max_price) {
    Book* temp = head;
    int found = 0;
    while (temp) {
        if (temp->price <= max_price) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nStock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price,
                temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found with maximum price of: %.2f.\n", max_price);
    }
}

void search_by_bestseller() {
    Book* temp = head;
    int found = 0;
    while (temp) {
        if (temp->topsale) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: Yes\nPublication Date: %s\nBooks in stock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price, temp->publication_date, temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No bestseller books found.\n");
    }
}

void search_by_date(const char* date) {
    Book* temp = head;
    int found = 0;
    while (temp) {
        if (strcmp(temp->publication_date, date) == 0) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nBooks in stock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price,
                temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found with publication date %s.\n", date);
    }
}

void search_by_stock() {
    Book* temp = head;
    while (temp) {
        if (temp->stock > 0) {
            printf("\nCatalog Number: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nTopsaler: %s\nPublication Date: %s\nStock: %d\n",
                temp->catalog_number, temp->title, temp->author, temp->price,
                temp->topsale ? "Yes" : "No", temp->publication_date, temp->stock);
        }
        temp = temp->next;
    }
}

void books_menu(int permissionLevel) {
    load_books(); // 
    int choice_books;
    do {
        if (permissionLevel <= 2) {
            printf("\nBookstore Menu:\n1. Add Book\n2. Display Books\n3. Edit/Remove Book\n4. Search Book\n5. Save & Exit\nEnter choice: ");
        }
        else if (permissionLevel == 3)
        {
            printf("\nBookstore Menu:\n1. Add Book\n2. Display Books\n3. Save & Exit\nEnter choice: ");
        }
        scanf("%d", &choice_books);

        switch (choice_books) {
        case 1:
            add_book();
            break;
        case 2:
            display_books();
            break;
        case 3:
            if (permissionLevel <= 2) {
                edit_or_remove_book();
            }
            else if(permissionLevel == 3) {
                save_books();
                printf("Data saved. Exiting.\n");
            }
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
    } while (choice_books != 5);
    return 0;
}
