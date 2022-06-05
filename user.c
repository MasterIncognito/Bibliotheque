#ifndef MODULE_user
    #define MODULE_user
    #include "user.h"
#endif

//fontion Utilisateur --

void userArray_init(User userArray[], int size) //set all users to unassigned
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            userArray[i].borrowed[j] = -1;
        }
        userArray[i].allow = 1;
        userArray[i].login[0]='\0';
    }
}

int find_unused_id_U(User userArray[], int size) //find an unassigned user
{
    for (int i = 0; i < size; i++)
    {
        if (userArray[i].login[0]=='\0')
        {
            return i;
        }
    }
    return -1;
}

int verif_login(User userArray[], int tab_length, char user[], char psw[]) //finds a user with user/pw
{
    int id=find_id_U(userArray, user, tab_length);
    if (id == -1) {
        return -1;
    }
    if (equal_string(userArray[id].password, psw) == 1)
    {
        return id;
    }
    return -1;
}



int createAccount(User userArray[], int tab_length) // -1 index error; 0 canceled; 1 user created
{
    int id = find_unused_id_U(userArray, tab_length);
    int temp;
	User input_user;
	clear();
	printf("Application CY-BiblioTECH\n\n");
    if (id == -1) {
        printf("Base de donnée surcharchée!\n");
        return -1;
    }
    // Setting access for user :
    do {
        printf("Etes-vous un étudiant ou un professeur? E/P\n");
        scanf("%c",&input_user.access);
		if(input_user.access == '\n') { // Doing a scanf %c after a scanf replaces it by '\n'
			scanf("%c", &input_user.access);
		}
    } while(input_user.access != 'E' && input_user.access != 'P' && input_user.access != '*' && input_user.access != 'e' && input_user.access != 'p');
    if (input_user.access=='*') {
        return 0;
    }
    // Username :
    do
    {
        printf("Nom d'utilisateur: ");
        scanf("%s", input_user.login);
        temp = find_id_U(userArray, input_user.login, tab_length);
        if( temp!=-1) {
            printf("Nom d'utilisateur existe déjà !\n");
        }
    } while(temp!=-1);
	
    if (equal_string(input_user.login,"*")) {
        return 0;
    }
    // User password :
    do
    {
        printf("Veuillez entrer un mot de passe contenant au moins\n8 caractères,  une majuscule, une minuscule et un chiffre :\n");
        scanf("%s", input_user.password);
		if(validPw(input_user.password) != 0) {
			printf("Mot de passe trop faible,\n");
		}
    } while (validPw(input_user.password) == 0);
	
	if(input_user.access == 'e') {
		input_user.access = 'E';
	}
	if(input_user.access == 'p') {
		input_user.access = 'P';
	}
    userArray[id].access = input_user.access;
    string_assign(userArray[id].login, input_user.login, 50);
    string_assign(userArray[id].password, input_user.password, 50);
	
    return 1;
}


