#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // pour isdigit()
#include <time.h>
#include <unistd.h>
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char categorie[100];
    int owner; // emprunter par qui ?
    time_t time; // hour to return
} Book;

typedef struct
{
    char login[50];
    char password[50];
    int borrowed[5];
    int allow;
    char access;//Etudiant / Professeur
} User;

void clear();

int equal_chaine(char chaine1[], char chaine2[]);
void chaine_assign(char chaine1[] ,char chaine2[] ,int len);
int find_id_U(User tabUser[], char user_name[], int tab_length);
int find_id_B(Book tabBook[], char user_name[], int tab_length);
int validPw(char pw[]);
void fputs_safe(char chaine[], FILE* file);

//tri
void title_order(Book tabBook[], int tab[], int tab_length);
void author_order(Book tabBook[], int tab[], int tab_length);
void categorie_order(Book tabBook[], int tab[], int tab_length);
int init_tab_id(Book tabBook[], int tab[], int tab_length);
