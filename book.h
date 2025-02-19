#include <stdbool.h>

// ���� ������� �� ���
typedef struct Book {
    int catalog_number;
    char title[100];
    char author[100];
    float price;
    bool topsale;
    char publication_date[11]; // �����: DD-MM-YYYY
    int stock;
    struct Book* next;
} Book;

// �������� ������ ������
void add_book();//������� ������� ��� ������ �������
void display_books();//������� ������� ����� �� ������ ������
void save_books();//������� ������� ������ ����� �����
void load_books();//������� ������� ����� �� ������ ���� ����� ������ ������� 
void sort_books();//������� ������ �� ������ ��� ���� ������
void edit_or_remove_book(); // ������� �����\����� ��� �������
int isValidName(const char* name); // ������� ������ �� �� ����
int isValidDate(const char* date); // ������� ������ �� ����� ����
int isValidNumber(const char* str);// ������� ������ �� ��� ���� �� ������