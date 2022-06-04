#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // pour isdigit()



//sctructure
typedef struct
{
    int id;
    char title[100];
    char author[100];
    char categorie[100];
    int owner; // par qui ?
    int time;
} Book;

typedef struct
{
    char login[50];
    char password[50];
    int borrowed[5];
    int allow;
    char access;//Etudiant / Professeur
} User;


//makefile: login->deleteAccount
int login(User tabUser[], int tab_length, char info[]);

//fonction Generale --

void clear()
{
    system("@cls||clear");
}

void download_db(User user[], Book book[])
{
}

int equal_chaine(char chaine1[], char chaine2[])
{
    int j = 0;
    while (j < 50 && chaine1[j] != '\0')
    {
        if (chaine1[j] != chaine2[j])
        {
            return 0;
        }
        j++;
    }
    if (chaine2[j] == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void chaine_assign(char chaine1[] ,char chaine2[] ,int len) {
    int i=0;
    while(i<(len-1) && chaine2[i]!='\0') {
        chaine1[i]=chaine2[i];
        i++;
    }
	chaine1[i]='\0';
}
int alphabet_bigger(char chaine1[] ,char chaine2[]) {
	int i=0;
	while(chaine1[i]!='\0' && chaine2[i]!='\0') {
		if(chaine1[i]>chaine2[i]) {
			return 1;
		} else if(chaine1[i]<chaine2[i]) {
			return 0;
		}
		i++;
	}
	if(chaine2[i]=='\0') {
		return 1;
	} else {
		return 0;
	}
}
int find_id(User tabUser[], char user_name[], int tab_length) {//trouve un compte qui match user_name
    for (int i = 0; i < tab_length; i++)
    {
        if (equal_chaine(tabUser[i].login, user_name) == 1) {
            //printf("aaaaa");
            return i;
        }
    }
    return -1;
}

int validPw(char pw[]) //Vérifie que le mdp rempli les conditions nécessaires
{
    if (strlen(pw) >= 8)
    {
        for (int i = 0; i < strlen(pw); i++)
        {
            if (isdigit(pw[i]))
            {
                for (i = 0; i < strlen(pw); i++)
                {
                    if (isupper(pw[i]))
                    {
                        for (i = 0; i < strlen(pw); i++)
                        {
                            if (islower(pw[i]))
                            {
                                return 1;
                            }
                        }
                        return 0;
                    }
                }
                return 0;
            }
        }
    }
    return 0;
}

void fputs_safe(char chaine[], FILE* file) {
    int error=0;
    //printf(chaine);
    error=fputs(chaine,file);
    if(error==-1) {
        printf("ERR0R");
    }
}

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
    int id=find_id(tabUser, user, tab_length);
    if (id == -1) {
        return -1;
    }
    if (equal_chaine(tabUser[id].password, mdp) == 1)
    {
        return id;
    }
    return -1;
}



int createAccount(User user[], int tab_length) // -1 Erreur d'emplacement; 0 annulé; 1 compte créé
{
    int id = find_unused_id_U(user, tab_length);
    char ipw[50];
    int temp;
    char access;
    if (id == -1) {
        printf("Base de donnée surcharchée!\n");
        return -1;
    }
    // Access de l'utilisateur
    do {
        printf("Etes-vous un étudiant ou un professeur? E/P\n");
        scanf("%s",&access);
    } while(access != 'E' && access != 'P' && access != '*');
    if (access=='*') {
        return 0;
    }
    // Nom de l'utilisateur
    char input_user[50];
    do
    {
        printf("Nom d'utilisateur: ");
        scanf("%s", input_user);
        temp = find_id(user, input_user, tab_length);
        if( temp!=-1) {
            printf("Nom d'utilisateur existe déjà !\n");
        }
    } while(temp!=-1);
	
    if (equal_chaine(input_user,"*")) {
        return 0;
    }
    // MDP de l'utilisateur
    do
    {
        printf("Veuillez entrer un mot de passe contenant au moins\n8 caractères,  une majuscule, une minuscule et un chiffre :\n ");
        scanf("%s", ipw);
        clear();
        printf("Mot de passe trop faible,\n");
    } while(0); //while (validPw(ipw) == 0);

    user[id].access = access;
    chaine_assign(user[id].login, input_user, 50);
    chaine_assign(user[id].password, ipw, 50);
	
    return 1;
//    if(user[id].login[0]=='\0') {//verifie que user est assigné
//        printf("Error\n");
//        user[id].login[0]='?';
//    }
}

int deleteAccount(User tabUser[], int user_id, int tab_length) {
    int security;
    do {
	security = login(tabUser, tab_length,"Retapper votre nom d'utilisateur et votre mot de passe\nsi vous est sûr de vouloir supprimer votre compte\n");
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
//fonction Tri

void title_order(Book tabBook[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(tabBook[tab[min]].title,tabBook[tab[j]].title)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}
void author_order(Book tabBook[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(tabBook[tab[min]].author,tabBook[tab[j]].author)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}
void categorie_order(Book tabBook[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(tabBook[tab[min]].categorie,tabBook[tab[j]].categorie)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}

int init_tab_id(Book tabBook[], int tab[], int tab_length) {//créé un tableau des id de book utilisé et renvoie sa vraie taille
	int j=0;
	int res;
	for(int i=0;i<tab_length; i++) {
		if(tabBook[i].id!=-1) {
			tab[j]=i;
			j++;
		}
	}
	res=j;
	while(j<tab_length) {
		tab[j]=-1;
		j++;
		
	}
	return res;
}
//fonction Livre --

void tabBook_init(Book tabBook[], int size) //rend tout les Livre non-assigné
{
    for (int i = 0; i < size; i++)
    {
        tabBook[i].id = -1;
        tabBook[i].owner = -1;
    }
}

int find_unused_id_B(Book tabBook[], int size) //trouver un compte non-assigné
{
    for (int i = 0; i < size; i++)
    {
        if (tabBook[i].id==-1)
        {
            return i;
        }
    }
    return -1;
}

int createBook(Book tabBook[], int tab_length) {
    int id = find_unused_id_B(tabBook, tab_length);
    if (id == -1) {
        printf("Base de donnée surcharchée!\n");
        return -1;
    }
    // Nom du livre
    if ('*'=='*') {
        return 0;
    }
    return 1;
}


void borrow_book(User tabUser[], int user_id, Book tabBook[], int book_id) {
    tabBook[book_id].owner=user_id;
    int i=0;
    while(tabUser[user_id].borrowed[i]!=-1) {
        i++;
    }
    tabUser[user_id].borrowed[i]=book_id;
}
void return_book(User tabUser[], int user_id, Book tabBook[], int borrow_id) {
    tabBook[ tabUser[user_id].borrowed[borrow_id] ].owner=-1;
    tabUser[user_id].borrowed[borrow_id]=-1;
}
//fonction Fichier --

void import_user(User tabUser[], int tab_length,char link[]) {
    FILE * file = NULL;

    file = fopen(link, "r");
    int i=find_unused_id_U(tabUser,tab_length);
    int j;
    char eof[100];
    int temp=0;
    fgets(eof,100,file);
    while(temp != -1) {
        //NOM
        j=0;
        do {
            temp=fgetc(file);
            tabUser[i].login[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        tabUser[i].login[j-2]='\0';

        //MDP
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            tabUser[i].password[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        tabUser[i].password[j-2]='\0';

        //ACCESS
        fgetc(file);
        temp=fgetc(file);
        tabUser[i].access=temp;
        do {
            i++;
        }while(tabUser[i].login[0]!='\0');
        temp=fgetc(file);
    }
    fclose(file);
}

void import_book(Book tabBook[], int tab_length,char link[]) {
    FILE * file = NULL;

    file = fopen(link, "r");
    int i=find_unused_id_B(tabBook,tab_length);;
    int j;
    char eof[100];
    int temp=0;
    fgets(eof,100,file);
    while(temp != -1) {
        //TITLE
        j=0;
        do {
            temp=fgetc(file);
            tabBook[i].title[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        tabBook[i].title[j-2]='\0';

        //AUTHOR
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            tabBook[i].author[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        tabBook[i].author[j-2]='\0';

        //categorie
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            tabBook[i].categorie[j]=temp;
            j++;
        } while (temp != -1 && temp != '\n' && j!=100);
        tabBook[i].categorie[j-1]='\0';
		
		//next id
        tabBook[i].id=i;
        do{
            i++;
        } while(tabBook[i].id!=-1);
    }
    fclose(file);
}

void export_user(User tabUser[], int tab_length,char link[]) {
    FILE * file= NULL;

    file = fopen(link, "w");
    fputs_safe("Nom | Mot de passe | Etudiant Professeur\n",file);
    for(int i=0; i<tab_length; i++) {

        if(tabUser[i].login[0]!='\0') {
            fputs_safe(tabUser[i].login,file);
            fputs_safe(" | ",file);
            fputs_safe(tabUser[i].password,file);
            fputs_safe(" | ",file);
            char temp[2];
            temp[0]=tabUser[i].access;
            fputs_safe(temp,file);
            fputs_safe("\n",file);
        }
    }
    fclose(file);
}
void export_book(Book tabBook[], int tab_length,char link[]) {
    FILE * file= NULL;

    file = fopen(link, "w");
    fputs_safe("Titre | Auteur | Categorie\n",file);
    for(int i=0; i<tab_length; i++) {

        if(tabBook[i].id!=-1) {
            fputs_safe(tabBook[i].title,file);
            fputs_safe(" | ",file);
            fputs_safe(tabBook[i].author,file);
            fputs_safe(" | ",file);
            fputs_safe(tabBook[i].categorie,file);
            fputs_safe("\n",file);
        }
    }
    fclose(file);
}
//fonction Page d'affichage --

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
    } while (res != '1' && res != '2' && res != '3' && res != '4');
    return res;
}

int login(User tabUser[], int tab_length, char info[])
{
    char user[50];
    char mdp[50];
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

            clear();
            printf("Application CY-BiblioTECH\n");
            printf("Utilisateur ou mot de passe incorect!\n\n");
            res = verif_login(tabUser, tab_length, user, mdp);
        }
    } while (res == -1 && equal_chaine(user,"*")!=1);

    if(user == "*") {
        return -1;
    }
    return res;
}


void drawDebug(User tabUser[], int len, Book tabBook[], int lenB) //Affiche les list user et book
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
int show_book(Book tabBook[], int max_length, int id_tab[]) //renvoie l'id du book selectionner
{
    int j=0;
    int res;
    do {
        clear();
        printf("Application CY-BiblioTECH\n\n");
        printf("Tapper 0 pour quitter.\n");
        printf("Les Livres * ne sont pas disponible\n");
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

int show_own_book(User tabUser[], int user_id, Book tabBook[]) //renvoie l'id du book selectionner
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

void main_User(User tabUser[], int user_id, int tab_length, Book tabBook[]) { // fonction Principale connection --
    char input = '0';
    int id_book;
	
	int id_tab[tab_length];
	int temp_tab_length;
    while (input != '4')
    {
        clear();
        printf("Application CY-BiblioTECH\n");
        printf("Bonjour %s,\n\n", tabUser[user_id].login);

        printf("1 - Emprunter un livre\n");
        printf("2 - Vos livres empruntés\n");
        printf("3 - Supprimer votre compte\n");
        printf("4 - Deconnexion\n");
        scanf("%c", &input);
        switch (input)
        {
        case '1':
			temp_tab_length = init_tab_id(tabBook, id_tab, tab_length);
			if(which_order(tabBook, id_tab, temp_tab_length)==0) {
				id_book = show_book(tabBook, temp_tab_length, id_tab);
				if(id_book!=-1) {
					borrow_book(tabUser, user_id, tabBook, id_book);
				}
			};
            break;
        case '2':
            id_book = show_own_book(tabUser, user_id, tabBook);
            if(id_book!=-1) {
                return_book(tabUser, user_id, tabBook, id_book);
            }
            break;
        case '3':
            if(deleteAccount(tabUser, user_id,tab_length)==1) {
                input='4';
            };
            break;
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
    
    //clear();
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