#include <stdbool.h>

// מבנה הנתונים של ספר
typedef struct Book {
    int catalog_number;
    char title[100];
    char author[100];
    float price;
    bool topsale;
    char publication_date[11]; // פורמט: DD-MM-YYYY
    int stock;
    struct Book* next;
} Book;

// פונקציות לניהול הספרים
void add_book();//פונקציה המוסיפה ספר לרשימה המקושרת
void display_books();//פונקציה האחראית להציג את הספרים למשתמש
void save_books();//פונקציה האחראית לשמירת ספרים לקובץ
void load_books();//פונקציה האחראית לטעון את הספרים מתוך הקובץ לרשימה המקושרת 
void sort_books();//פונקציה שתמיין את הספרים לפי מספר קטלוגי
void edit_or_remove_book(); // פונקציה להסרה\עריכת ספר מהרשימה
int isValidName(const char* name); // פונקציה לבדיקה אם שם תקין
int isValidDate(const char* date); // פונקציה לבדיקה אם תאריך תקין
int isValidNumber(const char* str);// פונקציה לבדיקה אם קלט מכיל רק מספרים