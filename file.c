#ifndef MODULE_file
    #define MODULE_file
    #include "file.h"
#endif

//File functions --

int import_user(User userArray[], int array_length,char link[]) {
    FILE * file = NULL;

    file = fopen(link, "r");
    int i=0;
    int j;
    char eof[100];
    int temp=0;
    fgets(eof,100,file);
    while(temp != -1) {
        do {
            i++;
        }while(userArray[i].login[0]!='\0');
		if (i>=array_length) {
			printf("Base de donnée surcharchée!\n");
			return -1;
		}
        //USERNAME
        j=0;
        do {
            temp=fgetc(file);
			if(temp == -1) {
				return 0;
			}
            userArray[i].login[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        userArray[i].login[j-2]='\0';

        //PASSWORD
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            userArray[i].password[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        userArray[i].password[j-2]='\0';

        //ACCESS
        fgetc(file);
        temp=fgetc(file);
        userArray[i].access=temp;
        temp=fgetc(file);
    }
    fclose(file);
	return 1;
}

int import_book(Book bookArray[], int array_length,char link[]) {
    FILE * file = NULL;

    file = fopen(link, "r");
    int i=0;
    int j;
    char eof[100];
    int temp=0;
    fgets(eof,100,file);
    while(temp != -1) {
        do{
            i++;
        } while(bookArray[i].id!=-1);
		if (i>=array_length) {
			printf("Base de donnée surcharchée!\n");
			return -1;
		}
        //TITLE
        j=0;
        do {
            temp=fgetc(file);
			if(temp == -1) {
				return 0;
			}
            bookArray[i].title[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        bookArray[i].title[j-2]='\0';

        //AUTHOR
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            bookArray[i].author[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        bookArray[i].author[j-2]='\0';

        //CATEGORY
        fgetc(file);
        j=0;
        do {
            temp=fgetc(file);
            bookArray[i].categorie[j]=temp;
            j++;
        } while (temp != -1 && temp != '\n' && j!=100);
        bookArray[i].categorie[j-1]='\0';
		
		//next id
        bookArray[i].id=i;
    }
    fclose(file);
	return 1;
}

void export_user(User userArray[], int array_length,char link[]) {
    FILE * file= NULL;

    file = fopen(link, "w");
    fputs_safe("Nom | Mot de passe | Etudiant Professeur",file);
    for(int i=0; i<array_length; i++) {

        if(userArray[i].login[0]!='\0') {
            fputs_safe("\n",file);
            fputs_safe(userArray[i].login,file);
            fputs_safe(" | ",file);
            fputs_safe(userArray[i].password,file);
            fputs_safe(" | ",file);
            char temp[2];
            temp[0]=userArray[i].access;
            fputs_safe(temp,file);
        }
    }
    fclose(file);
}
void export_book(Book bookArray[], int array_length,char link[]) {
    FILE * file= NULL;

    file = fopen(link, "w");
    fputs_safe("Titre | Auteur | Categorie",file);
    for(int i=0; i<array_length; i++) {

        if(bookArray[i].id!=-1) {
            fputs_safe("\n",file);
            fputs_safe(bookArray[i].title,file);
            fputs_safe(" | ",file);
            fputs_safe(bookArray[i].author,file);
            fputs_safe(" | ",file);
            fputs_safe(bookArray[i].categorie,file);
        }
    }
	
    fclose(file);
}
