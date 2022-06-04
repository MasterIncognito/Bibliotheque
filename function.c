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
int find_id_U(User tabUser[], char user_name[], int tab_length) {//Finds a user matching the username
    for (int i = 0; i < tab_length; i++)
    {
        if (equal_chaine(tabUser[i].login, user_name) == 1) {
            //printf("aaaaa");
            return i;
        }
    }
    return -1;
}

int find_id_B(Book tabBook[], char book_title[], int tab_length) {//Finds a book matching the book_title
    for (int i = 0; i < tab_length; i++)
    {
        if (equal_chaine(tabBook[i].title, book_title) == 1) {
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

void fputs_safe(char chaine[], FILE* file) {//Function to write to file
    int error=0;
    //printf(chaine);
    error=fputs(chaine,file);
    if(error==-1) {
        printf("ERR0R");
    }
}


//Sorting functions

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
