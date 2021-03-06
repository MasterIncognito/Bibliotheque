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
    } while (res != '1' && res != '2' && res != '3');
    return res;
}

int login(User userArray[], int array_length, char info[])
{
    char user[50];
    char psw[50];
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
        
        if(equal_string(user,"*")!=1) {
            printf("Mot de passe: ");
            scanf("%s", psw);
			vigenere(psw,0,50);
			res = verif_login(userArray, array_length, user, psw);

            //clear();
            printf("Application CY-BiblioTECH\n");
            printf("Utilisateur ou mot de passe incorect!\n\n");
	    max--;
	    if (max==0){
		    exit(1);
	    }
        }
    } while (res == -1 && equal_string(user,"*")!=1);

    if(equal_string(user,"*")) {
        return -1;
    }
    return res;
}

int deleteAccount(User userArray[], int user_id, int array_length) {
    int security;
    do {
	security = login(userArray, array_length,"Retappez votre nom d'utilisateur et votre mot de passe\nsi vous est sûr de vouloir supprimer votre compte\n");
    } while(security != -1 && security != user_id);
    if(security == -1) {
        return 0;
    }
    else
    {
        userArray[user_id].login[0]='\0';
        //userArray[user_id].password="";
        return 1;
    }
}

void drawDebug(User userArray[], int len, Book bookArray[], int lenB) //Displays user and book lists
{
    clear();
    printf("Login - Password - Access\n--------------------------\n");
    for (int i = 0; i < len; i++)
    {
        if(userArray[i].login[0]!='\0') {
            printf("%s - %s - %c\n", userArray[i].login, userArray[i].password, userArray[i].access);
        }
    }
    printf("\nTitle - Author - Categorie\n--------------------------\n");
    for (int i = 0; i < len; i++)
    {
        if(bookArray[i].id!=-1) {
            printf("%s - %s - %s\n", bookArray[i].title, bookArray[i].author, bookArray[i].categorie);
        }
    }
}

int which_order(Book bookArray[], int id_array[], int temp_array_length) {
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
			title_order(bookArray, id_array, temp_array_length);
			return 0;
		case 2:
			author_order(bookArray, id_array, temp_array_length);
			return 0;
		case 3:
			categorie_order(bookArray, id_array, temp_array_length);
			return 0;
	}

}
int show_book(Book bookArray[], int max_length, int id_array[]) //returns selected book's id and displays all books
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
            //printf("%d",bookArray[i].id);
            if(bookArray[id_array[i]].owner==-1) {
                printf("%d - %s - %s - %s\n", j,bookArray[id_array[i]].title, bookArray[id_array[i]].author, bookArray[id_array[i]].categorie);
                j++;
            } else {
                printf("* - %s - %s - %s\n", bookArray[id_array[i]].title, bookArray[id_array[i]].author, bookArray[id_array[i]].categorie);
            }
        }
        scanf("%d",&res);
    } while (res < 0 || res >= j);
    if(res==0) {
        return -1;
    }
    j=1;
    for(int i=0;i<max_length;i++) {
        if(bookArray[id_array[i]].owner==-1) {
            if(j==res) {
                return id_array[i];
            }
            j++;
        }
    }
    printf("error");
    exit(1);
}

int show_own_book(User userArray[], int user_id, Book bookArray[]) //returns selected book's id and displays borrowed books
{
    int j=1;
    int res;
	int temp_id;
    do
    {
        clear();
        printf("Application CY-BiblioTECH\n\n");
        printf("Tapper 0 pour quitter.\n");
        printf("Vouler-vous rendre un livre?\n");
        j=1;
        for(int i=0; i<5; i++) {
			temp_id=userArray[user_id].borrowed[i];
			
            if(temp_id!=-1) {
                printf("%d - %s - %s - %s - %s\n", j, bookArray[temp_id].title, bookArray[temp_id].author, bookArray[temp_id].categorie, ctime(&bookArray[temp_id].time));
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
        if(userArray[user_id].borrowed[i]!=-1) {
            if(j==res) {
                return i;
            }
            j++;
        }
    }
    printf("error");
    exit(1);
}

void main_User(User userArray[], int user_id, int array_length, Book bookArray[]) { // Main function while connected --
    char input = '0';
    int id_book;
	
	int id_array[array_length];
	int temp_array_length;
    while ((input != '4')&&(userArray[user_id].access == 'E') ||  (input != '5')&&(userArray[user_id].access == 'P'))
    {
        clear();
        printf("Application CY-BiblioTECH\n");
        printf("Bonjour %s,\n", userArray[user_id].login);
		
		if (userArray[user_id].allow == 0) { // vérifie que l'utilisateur a le droit d'emprunter un livre
			printf("Vous n'avez pas le droit d'emprunter un livre car vous avez rendu un livre en retard.\n\n* - Emprunter un livre\n");
		} else {
			printf("\n1 - Emprunter un livre\n");
		}
		printf("2 - Vos livres empruntés\n");
		printf("3 - Supprimer votre compte\n");
		
		if (userArray[user_id].access == 'P') { // Different options for Teacher/Student
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
			if (userArray[user_id].allow == 1) { // Check if the user is allowed to borrow a book
				temp_array_length = init_array_id(bookArray, id_array, array_length); //Creates an array with existing book's ids
				if(which_order(bookArray, id_array, temp_array_length)== 0) { //sorts the array
					id_book = show_book(bookArray, temp_array_length, id_array); // gets the id of the book that is going to be borrowed
					if(id_book!=-1) {
						borrow_book(userArray, user_id, bookArray, id_book); // borrows the book
					}
				};
			}
            break;
        case '2':
			id_book = show_own_book(userArray, user_id, bookArray); // Gets the borrowed book's id
			if(id_book!=-1) {
				return_book(userArray, user_id, bookArray, id_book); // changes the book to the return state
			}
            break;
        case '3':
            if(deleteAccount(userArray, user_id,array_length)==1) {
                if(userArray[user_id].access == 'P') {
					input='5';
				} else {
					input='4';
				}
				export_user(userArray, array_length, "user.txt");
            };
            break;
		case '4':
            if(userArray[user_id].access == 'P') {
                createBook(bookArray, array_length);
            };
			export_book(bookArray, array_length, "book.txt");
        }
    }
}

void main() // fonction Principale --
{
    int array_length = 50;
    User userArray[array_length];
    Book bookArray[array_length];
    userArray_init(userArray, array_length);
    bookArray_init(bookArray, array_length);
    import_book(bookArray,50,"book.txt");
    import_user(userArray,50,"user.txt");
    int user_id;

    //export_book(bookArray, array_length, "book.txt");
    //export_user(userArray, array_length, "user.txt");
    
    //createAccount(userArray, array_length);
    char input = 0;
    while (input != '3')
    {
        input = menu();
        switch (input)
        {
        case '1':
            user_id = login(userArray, array_length,"-- Connection --\n");
            if(user_id > -1) {
                main_User(userArray, user_id, array_length,bookArray);
            }
            break;
        case '2':
            createAccount(userArray, array_length);
			export_user(userArray, array_length, "user.txt");
            break;
        }
    }
	clear();
	//drawDebug(userArray, array_length, bookArray, array_length); // show every information store
}
