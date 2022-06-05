#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

void userArray_init(User userArray[], int size);
int find_unused_id_U(User userArray[], int size);
int verif_login(User userArray[], int tab_length, char user[], char psw[]);
int createAccount(User userArray[], int tab_length);
