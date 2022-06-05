#ifndef MODULE_book
    #define MODULE_book
    #include "book.h"
#endif

//Book functions --

void bookArray_init(Book bookArray[], int size) //Sets all books to unassigned
{
    for (int i = 0; i < size; i++)
    {
        bookArray[i].id = -1;
        bookArray[i].owner = -1;
    }
}

int find_unused_id_B(Book bookArray[], int size) //Finds an unnassigned user
{
    for (int i = 0; i < size; i++)
    {
        if (bookArray[i].id==-1)
        {
            return i;
        }
    }
    return -1;
}

int createBook(Book bookArray[], int tab_length) {
    int id = find_unused_id_B(bookArray, tab_length);
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
        temp = find_id_B(bookArray, input_book.title, tab_length);
        if( temp!=-1) {
            printf("Ce livre existe déjà !\n");
        }
    } while(temp!=-1);
    if (equal_string(input_book.title,"*")) {
        return 0;
    }
	
	// Auteur du livre
	printf("Auteur du livre: ");
    scanf("%s", input_book.author);
    if (equal_string(input_book.author,"*")) {
        return 0;
    }
	
	// Categorie of book
	printf("Categorie du livre: ");
    scanf("%s", input_book.categorie);
	
	
	bookArray[id].id = id;
	string_assign(bookArray[id].title,input_book.title, 50);
	string_assign(bookArray[id].author,input_book.author, 50);
	string_assign(bookArray[id].categorie,input_book.categorie, 50);
	
    return 1;
}


void borrow_book(User userArray[], int user_id, Book bookArray[], int book_id) {
    int i=0;
    while(userArray[user_id].borrowed[i]!=-1) {
        i++;
    }
	if((i>=5)&&(userArray[user_id].access=='P') || (i>=3)&&(userArray[user_id].access=='E')) {
		printf("Vous avez déjà %d livre(s) emprunté(s)!\n",i);
	} else {
		bookArray[book_id].owner=user_id;
		userArray[user_id].borrowed[i]=book_id;
		time_t temp_time = time(NULL);
		struct tm* tm = localtime(&temp_time);
		tm->tm_min+=2 + (userArray[user_id].access=='P'); //set hour time to 3min for professors and 2min for students
		bookArray[book_id].time= mktime(tm);
		printf("Vous avez maintenant %d livre(s) emprunté(s).\n",i+1);
	}
	scanf("%d");
}
void return_book(User userArray[], int user_id, Book bookArray[], int borrow_id) {
	
	time_t now = time(NULL);
    
    float secondes = difftime(now, bookArray[ userArray[user_id].borrowed[borrow_id]].time);
	if( secondes > 0) {
		userArray[user_id].allow = 0;
	}
    bookArray[ userArray[user_id].borrowed[borrow_id] ].owner=-1;
    userArray[user_id].borrowed[borrow_id]=-1;
}
