#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif

#ifndef MODULE_book
    #define MODULE_book
    #include "book.h"
#endif

#ifndef MODULE_user
    #define MODULE_user
    #include "user.h"
#endif

#ifndef MODULE_file
    #define MODULE_file
    #include "file.h"
#endif

//Display functions :

char menu()
{
    char res;
    do
    {
        clear();
        printf("Application CY-BiblioTECH\n\n");
        printf("1 - Se connecter à son compte.\n");
        printf("2 - Créer un compte\n");
        printf("3 - Quitter Application\n");
        scanf("%c", &res);
		if(res == '\n') { // Doing a scanf %c after a scanf replaces it by '\n'
			scanf("%c", &res);
		}
    } while (res != '1' && res != '2' && res != '3' && res != '4');
    return res;
}

int login(User tabUser[], int tab_length, char info[])
{
    char user[50];
    char mdp[50];
    int max=3;
    int res=-1;
	
    clear();
    printf("Application CY-BiblioTECH\n\n");
    do
    {
        printf("%s",info);
        printf("Tapper * pour quitter.\n");
        printf("Nom d'utilisateur: ");
        scanf("%s", user);
        
        if(equal_chaine(user,"*")!=1) {
            printf("Mot de passe: ");
            scanf("%s", mdp);
			res = verif_login(tabUser, tab_length, user, mdp);

            //clear();
            printf("Application CY-BiblioTECH\n");
            printf("Utilisateur ou mot de passe incorect!\n\n");
	    max--;
	    if (max==0){
		    exit(1);
	    }
        }
    } while (res == -1 && equal_chaine(user,"*")!=1);

    if(equal_chaine(user,"*")) {
        return -1;
    }
    return res;
}

int deleteAccount(User tabUser[], int user_id, int tab_length) {
    int security;
    do {
	security = login(tabUser, tab_length,"Retappez votre nom d'utilisateur et votre mot de passe\nsi vous est sûr de vouloir supprimer votre compte\n");
    } while(security != -1 && security != user_id);
    if(security == -1) {
        return 0;
    }
    else
    {
        tabUser[user_id].login[0]='\0';
        //tabUser[user_id].password="";
        return 1;
    }
}

void drawDebug(User tabUser[], int len, Book tabBook[], int lenB) //Displays user and book lists
{
    clear();
    printf("Login - Password - Access\n--------------------------\n");
    for (int i = 0; i < len; i++)
    {
        if(tabUser[i].login[0]!='\0') {
            printf("%s - %s - %c\n", tabUser[i].login, tabUser[i].password, tabUser[i].access);
        }
    }
    printf("\nTitle - Author - Categorie\n--------------------------\n");
    for (int i = 0; i < len; i++)
    {
        if(tabBook[i].id!=-1) {
            printf("%s - %s - %s\n", tabBook[i].title, tabBook[i].author, tabBook[i].categorie);
        }
    }
}

int which_order(Book tabBook[], int id_tab[], int temp_tab_length) {
    int res;
	do {
		clear();
		printf("Application CY-BiblioTECH\n\n");
		printf("Tapper 0 pour quitter.\n");
		printf("Quel ordre voulez-vous afficher les livres ?\n");
		
        printf("1 - Titre\n");
        printf("2 - Auteur\n");
        printf("3 - Categorie\n");
        scanf("%d",&res);
    } while (res < 0 || res >= 4);
	switch(res) {
		case 0:
			return -1;
		case 1:
			title_order(tabBook, id_tab, temp_tab_length);
			return 0;
		case 2:
			author_order(tabBook, id_tab, temp_tab_length);
			return 0;
		case 3:
			categorie_order(tabBook, id_tab, temp_tab_length);
			return 0;
	}

}
int show_book(Book tabBook[], int max_length, int id_tab[]) //returns selected book's id and displays all books
{
    int j=0;
    int res;
    do {
        clear();
        printf("Application CY-BiblioTECH\n\n");
        printf("Tapper 0 pour quitter.\n");
        printf("Les Livres * ne sont pas disponible.\n");
        j=1;
        for(int i=0;i<max_length;i++) {
            //printf("%d",tabBook[i].id);
            if(tabBook[id_tab[i]].owner==-1) {
                printf("%d - %s\n",j,tabBook[id_tab[i]].title);
                j++;
            } else {
                printf("* - %s\n",tabBook[id_tab[i]].title);
            }
        }
        scanf("%d",&res);
    } while (res < 0 || res >= j);
    if(res==0) {
        return -1;
    }
    j=1;
    for(int i=0;i<max_length;i++) {
        if(tabBook[id_tab[i]].owner==-1) {
            if(j==res) {
                return id_tab[i];
            }
            j++;
        }
    }
    printf("error");
    exit(1);
}

int show_own_book(User tabUser[], int user_id, Book tabBook[]) //returns selected book's id and displays borrowed books
{
    int j=1;
    int res;
    do
    {
        clear();
        printf("Application CY-BiblioTECH\n\n");
        printf("Tapper 0 pour quitter.\n");
        printf("Vouler-vous rendre un livre?\n");
        j=1;
        for(int i=0; i<5; i++) {
            if(tabUser[user_id].borrowed[i]!=-1) {
                printf("%d - %s\n",j,tabBook[tabUser[user_id].borrowed[i]].title);
                j++;
            }
        }
        scanf("%d",&res);
    } while (res < 0 || res >= j);

    if(res==0) {
        return -1;
    }
    j=1;
    for(int i=0;i<5;i++) {
        if(tabUser[user_id].borrowed[i]!=-1) {
            if(j==res) {
                return i;
            }
            j++;
        }
    }
    printf("error");
    exit(1);
}

void main_User(User tabUser[], int user_id, int tab_length, Book tabBook[]) { // Main function while connected --
    char input = '0';
    int id_book;
	
	int id_tab[tab_length];
	int temp_tab_length;
    while ((input != '4')&&(tabUser[user_id].access == 'E') ||  (input != '5')&&(tabUser[user_id].access == 'P'))
    {
        clear();
        printf("Application CY-BiblioTECH\n");
        printf("Bonjour %s,\n", tabUser[user_id].login);
		
		if (tabUser[user_id].allow == 0) { // vérifie que l'utilisateur a le droit d'emprunter un livre
			printf("Vous n'avez pas le droit d'emprunter un livre car vous avez rendu un livre en retard.\n\n* - Emprunter un livre\n");
		} else {
			printf("\n1 - Emprunter un livre\n");
		}
		printf("2 - Vos livres empruntés\n");
		printf("3 - Supprimer votre compte\n");
		
		if (tabUser[user_id].access == 'P') { // Different options for Teacher/Student
			printf("4 - Ajouter un livre\n");
			printf("5 - Deconnexion\n");
		} else {
			printf("4 - Deconnexion\n");
		}
		
		// input
        scanf("%c", &input);
		if(input == '\n') { // Doing a scanf %c after a scanf replaces it by '\n'
			scanf("%c", &input);
		}
        switch (input) {
        case '1':
			if (tabUser[user_id].allow == 1) { // Check if the user is allowed to borrow a book
				temp_tab_length = init_tab_id(tabBook, id_tab, tab_length); //Creates an array with existing book's ids
				if(which_order(tabBook, id_tab, temp_tab_length)== 0) { //sorts the array
					id_book = show_book(tabBook, temp_tab_length, id_tab); // gets the id of the book that is going to be borrowed
					if(id_book!=-1) {
						borrow_book(tabUser, user_id, tabBook, id_book); // borrows the book
					}
				};
			}
            break;
        case '2':
			id_book = show_own_book(tabUser, user_id, tabBook); // Gets the borrowed book's id
			if(id_book!=-1) {
				return_book(tabUser, user_id, tabBook, id_book); // changes the book to the return state
			}
            break;
        case '3':
            if(deleteAccount(tabUser, user_id,tab_length)==1) {
                input='4';
            };
            break;
		case '4':
            if(tabUser[user_id].access == 'P') {
                createBook(tabBook, tab_length);
            };
        }
    }
}

void main() // fonction Principale --
{
    int tab_length = 50;
    User tabUser[tab_length];
    Book tabBook[tab_length];
    tabUser_init(tabUser, tab_length);
    tabBook_init(tabBook, tab_length);
    import_book(tabBook,50,"book.txt");
    import_user(tabUser,50,"user.txt");
    int user_id;

    //export_book(tabBook, tab_length, "book.txt");
    //export_user(tabUser, tab_length, "user.txt");
    
    createAccount(tabUser, tab_length);
    char input = 0;
    while (input != 3)
    {
        input = menu();
        switch (input)
        {
        case '1':
            user_id = login(tabUser, tab_length,"-- Connection --\n");
            if(user_id > -1) {
                main_User(tabUser, user_id, tab_length,tabBook);
            }
            break;
        case '2':
            createAccount(tabUser, tab_length);
            break;
        case '3':
            exit(1);
            break;
        case '4':
            drawDebug(tabUser, tab_length, tabBook, tab_length);
            scanf("%d");
            break;
        }
    }
}
