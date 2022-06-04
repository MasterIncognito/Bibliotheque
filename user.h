#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

void tabUser_init(User tabUser[], int size);
int find_unused_id_U(User tabUser[], int size);
int verif_login(User tabUser[], int tab_length, char user[], char mdp[]);
int createAccount(User tabUser[], int tab_length);
