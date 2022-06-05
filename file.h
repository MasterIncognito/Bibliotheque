#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

#ifndef MODULE_user
    #define MODULE_user
    #include "user.h"
#endif

#ifndef MODULE_book
    #define MODULE_book
    #include "book.h"
#endif

int import_user(User userArray[], int tab_length,char link[]);
int import_book(Book bookArray[], int tab_length,char link[]);
void export_user(User userArray[], int tab_length,char link[]);
void export_book(Book bookArray[], int tab_length,char link[]);
