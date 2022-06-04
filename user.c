#ifndef MODULE_user
    #define MODULE_user
    #include "user.h"
#endif

//fontion Utilisateur --

void tabUser_init(User tabUser[], int size) //rend tout les compte non-assigné
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tabUser[i].borrowed[j] = -1;
        }
        tabUser[i].allow = 1;
        tabUser[i].login[0]='\0';
    }
}

int find_unused_id_U(User tabUser[], int size) //trouver un compte non-assigné
{
    for (int i = 0; i < size; i++)
    {
        if (tabUser[i].login[0]=='\0')
        {
            return i;
        }
    }
    return -1;
}

int verif_login(User tabUser[], int tab_length, char user[], char mdp[]) //cherche un compte avec user/mdp
{
    int id=find_id_U(tabUser, user, tab_length);
    if (id == -1) {
        return -1;
    }
    if (equal_chaine(tabUser[id].password, mdp) == 1)
    {
        return id;
    }
    return -1;
}



int createAccount(User tabUser[], int tab_length) // -1 Erreur d'emplacement; 0 annulé; 1 compte créé
{
    int id = find_unused_id_U(tabUser, tab_length);
    int temp;
	User input_user;
	clear();
	printf("Application CY-BiblioTECH\n\n");
    if (id == -1) {
        printf("Base de donnée surcharchée!\n");
        return -1;
    }
    // Access de l'utilisateur
    do {
        printf("Etes-vous un étudiant ou un professeur? E/P\n");
        scanf("%c",&input_user.access);
		if(input_user.access == '\n') { // Faire un scanf %c apres un scanf le remplit automatiquement par '\n'
			scanf("%c", &input_user.access);
		}
    } while(input_user.access != 'E' && input_user.access != 'P' && input_user.access != '*');
    if (input_user.access=='*') {
        return 0;
    }
    // Nom de l'utilisateur
    do
    {
        printf("Nom d'utilisateur: ");
        scanf("%s", input_user.login);
        temp = find_id_U(tabUser, input_user.login, tab_length);
        if( temp!=-1) {
            printf("Nom d'utilisateur existe déjà !\n");
        }
    } while(temp!=-1);
	
    if (equal_chaine(input_user.login,"*")) {
        return 0;
    }
    // MDP de l'utilisateur
    do
    {
        printf("Veuillez entrer un mot de passe contenant au moins\n8 caractères,  une majuscule, une minuscule et un chiffre :\n");
        scanf("%s", input_user.password);
		if(validPw(input_user.password) != 0) {
			printf("Mot de passe trop faible,\n");
		}
    } while(0); //while (validPw(input_user.password) == 0);

    tabUser[id].access = input_user.access;
    chaine_assign(tabUser[id].login, input_user.login, 50);
    chaine_assign(tabUser[id].password, input_user.password, 50);
	
    return 1;
//    if(tabUser[id].login[0]=='\0') {//verifie que tabUser est assigné
//        printf("Error\n");
//        tabUser[id].login[0]='?';
//    }
}


