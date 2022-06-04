#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

void tabBook_init(Book tabBook[], int size);
int find_unused_id_B(Book tabBook[], int size);
int createBook(Book tabBook[], int tab_length);
void borrow_book(User tabUser[], int user_id, Book tabBook[], int book_id);
void return_book(User tabUser[], int user_id, Book tabBook[], int borrow_id);
