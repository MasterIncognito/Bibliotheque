#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

void bookArray_init(Book bookArray[], int size);
int find_unused_id_B(Book bookArray[], int size);
int createBook(Book bookArray[], int array_length);
void borrow_book(User userArray[], int user_id, Book bookArray[], int book_id);
void return_book(User userArray[], int user_id, Book bookArray[], int borrow_id);
