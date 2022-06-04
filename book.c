#ifndef MODULE_book
    #define MODULE_book
    #include "book.h"
#endif

//Book functions --

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
    int temp;
	Book input_book;
	clear();
	printf("Application CY-BiblioTECH\n\n");
    if (id == -1) {
        printf("Base de donnée surcharchée!\n");
        return -1;
    }
	
    // Nom du livre
	do {
        printf("Nom du livre: ");
        scanf("%s", input_book.title);
        temp = find_id_B(tabBook, input_book.title, tab_length);
        if( temp!=-1) {
            printf("Ce livre existe déjà !\n");
        }
    } while(temp!=-1);
    if (equal_chaine(input_book.title,"*")) {
        return 0;
    }
	
	// Auteur du livre
	printf("Auteur du livre: ");
    scanf("%s", input_book.author);
    if (equal_chaine(input_book.author,"*")) {
        return 0;
    }
	
	// Categorie of book
	printf("Categorie du livre: ");
    scanf("%s", input_book.categorie);
	
	
	tabBook[id].id = id;
	chaine_assign(tabBook[id].title,input_book.title, 50);
	chaine_assign(tabBook[id].author,input_book.author, 50);
	chaine_assign(tabBook[id].categorie,input_book.categorie, 50);
	
    return 1;
}


void borrow_book(User tabUser[], int user_id, Book tabBook[], int book_id) {
    int i=0;
    while(tabUser[user_id].borrowed[i]!=-1) {
        i++;
    }
	if((i>=5)&&(tabUser[user_id].access=='P') || (i>=3)&&(tabUser[user_id].access=='E')) {
		printf("Vous avez déjà %d livre(s) emprunté(s)!\n",i);
	} else {
		tabBook[book_id].owner=user_id;
		tabUser[user_id].borrowed[i]=book_id;
		time_t temp_time = time(NULL);
		struct tm* tm = localtime(&temp_time);
		tm->tm_min+=2 + (tabUser[user_id].access=='P'); //set hour time to 3min for professors and 2min for students
		tabBook[book_id].time= mktime(tm);
		printf("Vous avez maintenant %d livre(s) emprunté(s).\n",i+1);
	}
	scanf("%d");
}
void return_book(User tabUser[], int user_id, Book tabBook[], int borrow_id) {
	
	time_t now = time(NULL);
    
    float secondes = difftime(now, tabBook[ tabUser[user_id].borrowed[borrow_id]].time);
	if( secondes > 0) {
		tabUser[user_id].allow = 0;
	}
    tabBook[ tabUser[user_id].borrowed[borrow_id] ].owner=-1;
    tabUser[user_id].borrowed[borrow_id]=-1;
}
