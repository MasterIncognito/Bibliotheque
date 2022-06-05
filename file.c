#ifndef MODULE_file
    #define MODULE_file
    #include "file.h"
#endif

//File functions --

void import_user(User tabUser[], int tab_length,char link[]) {
    FILE * file = NULL;

    file = fopen(link, "r");
    int i=find_unused_id_U(tabUser,tab_length);
    int j;
    char eof[100];
    int temp=0;
    fgets(eof,100,file);
    while(temp != -1) {
        //USERNAME
        j=0;
        do {
            temp=fgetc(file);
            tabUser[i].login[j]=temp;
            j++;
        } while (temp != '|' && j!=99);
        tabUser[i].login[j-2]='\0';

        //PASSWORD
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

        //CATEGORY
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
    fputs_safe("Nom | Mot de passe | Etudiant Professeur",file);
    for(int i=0; i<tab_length; i++) {

        if(tabUser[i].login[0]!='\0') {
            fputs_safe("\n",file);
            fputs_safe(tabUser[i].login,file);
            fputs_safe(" | ",file);
            fputs_safe(tabUser[i].password,file);
            fputs_safe(" | ",file);
            char temp[2];
            temp[0]=tabUser[i].access;
            fputs_safe(temp,file);
        }
    }
    fclose(file);
}
void export_book(Book tabBook[], int tab_length,char link[]) {
    FILE * file= NULL;

    file = fopen(link, "w");
    fputs_safe("Titre | Auteur | Categorie",file);
    for(int i=0; i<tab_length; i++) {

        if(tabBook[i].id!=-1) {
            fputs_safe("\n",file);
            fputs_safe(tabBook[i].title,file);
            fputs_safe(" | ",file);
            fputs_safe(tabBook[i].author,file);
            fputs_safe(" | ",file);
            fputs_safe(tabBook[i].categorie,file);
        }
    }
	
    fclose(file);
}
