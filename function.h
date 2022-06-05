#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isdigit()
#include <time.h> // To track time
#include <unistd.h>
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char categorie[100];
    int owner; // Borrowed by whom
    time_t time; // hour to return
} Book;

typedef struct
{
    char login[50];
    char password[50];
    int borrowed[5];
    int allow;
    char access; //Student / Teacher
} User;

void clear();

int equal_chaine(char chaine1[], char chaine2[]);
void chaine_assign(char chaine1[] ,char chaine2[] ,int len);
int find_id_U(User tabUser[], char user_name[], int tab_length);
int find_id_B(Book tabBook[], char user_name[], int tab_length);
int validPw(char pw[]);
void fputs_safe(char chaine[], FILE* file);
char vigenere(char input, int goal); //goal is 0 to code, and 1 to decode.

//tri
void title_order(Book tabBook[], int tab[], int tab_length);
void author_order(Book tabBook[], int tab[], int tab_length);
void categorie_order(Book tabBook[], int tab[], int tab_length);
int init_tab_id(Book tabBook[], int tab[], int tab_length);
