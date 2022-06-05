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

int equal_string(char string1[], char string2[]);
void string_assign(char string1[] ,char string2[] ,int len);
int find_id_U(User userArray[], char user_name[], int array_length);
int find_id_B(Book bookArray[], char user_name[], int array_length);
int validPw(char pw[]);
void fputs_safe(char string[], FILE* file);
int vigenere(char input, int goal, int size); //goal is 0 to code, and 1 to decode.

//tri
void title_order(Book bookArray[], int array[], int array_length);
void author_order(Book bookArray[], int array[], int array_length);
void categorie_order(Book bookArray[], int array[], int array_length);
int init_array_id(Book bookArray[], int array[], int array_length);
