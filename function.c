#ifndef MODULE_Function
    #define MODULE_Function
    #include "function.h"
#endif
//sctructure

//Core functions --

void clear()
{
    system("@cls||clear");
}

int equal_string(char string1[], char string2[])
{
    int j = 0;
    while (j < 50 && string1[j] != '\0')
    {
        if (string1[j] != string2[j])
        {
            return 0;
        }
        j++;
    }
    if (string2[j] == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void vigenere(char input[], int goal, int size) {	//goal is 0 to code, and 1 to decode.
    char key[14]="cytechlibrary";
    int nb;
    int tracker=0;
    for(int i=0;i<size;i++){
        if (islower(input[i])){
            if (goal==0){
                nb=input[i]-97;
                nb+=key[tracker]-97;
                input[i]=nb%25+97;
                tracker+=1;
            }else {
                nb=input[i]-97;
                nb-=key[tracker]-97;
                if (nb<0){
                    nb+=25;
                }
                input[i]=nb+97;
                tracker+=1;
            }
            if (tracker==13){
                tracker=0;
            }
        }
    }
}

void string_assign(char string1[] ,char string2[] ,int len) {
    int i=0;
    while(i<(len-1) && string2[i]!='\0') {
        string1[i]=string2[i];
        i++;
    }
	string1[i]='\0';
}
int alphabet_bigger(char string1[] ,char string2[]) {
	int i=0;
	while(string1[i]!='\0' && string2[i]!='\0') {
		if(string1[i]>string2[i]) {
			return 1;
		} else if(string1[i]<string2[i]) {
			return 0;
		}
		i++;
	}
	if(string2[i]=='\0') {
		return 1;
	} else {
		return 0;
	}
}
int find_id_U(User tabUser[], char user_name[], int tab_length) {//Finds a user matching the username
    for (int i = 0; i < tab_length; i++)
    {
        if (equal_string(tabUser[i].login, user_name) == 1) {
            //printf("aaaaa");
            return i;
        }
    }
    return -1;
}

int find_id_B(Book bookArray[], char book_title[], int tab_length) {//Finds a book matching the book_title
    for (int i = 0; i < tab_length; i++)
    {
        if (equal_string(bookArray[i].title, book_title) == 1) {
            //printf("aaaaa");
            return i;
        }
    }
    return -1;
}

int validPw(char pw[]) //Makes sure the password is meeting the requirements
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

void fputs_safe(char string[], FILE* file) {//Function to write to file
    int error=0;
    //printf(string);
    error=fputs(string,file);
    if(error==-1) {
        printf("ERR0R");
    }
}

//Sorting functions

void title_order(Book bookArray[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(bookArray[tab[min]].title,bookArray[tab[j]].title)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}
void author_order(Book bookArray[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(bookArray[tab[min]].author,bookArray[tab[j]].author)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}
void categorie_order(Book bookArray[], int tab[], int tab_length) {
	int min;
	int temp;
	for(int i=0; i<tab_length; i++) {
		min=i;
		for(int j=i+1; j<tab_length; j++) {
			if(alphabet_bigger(bookArray[tab[min]].categorie,bookArray[tab[j]].categorie)) {
				min=j;
			}
		}
		temp=tab[i];
		tab[i]=tab[min];
		tab[min]=temp;
	}
}

int init_tab_id(Book bookArray[], int tab[], int tab_length) {//créé un tableau des id de book utilisé et renvoie sa vraie taille
	int j=0;
	int res;
	for(int i=0;i<tab_length; i++) {
		if(bookArray[i].id!=-1) {
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
