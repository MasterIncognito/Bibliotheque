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
int find_id_U(User arrayUser[], char user_name[], int array_length) {//Finds a user matching the username
    for (int i = 0; i < array_length; i++)
    {
        if (equal_string(arrayUser[i].login, user_name) == 1) {
            //printf("aaaaa");
            return i;
        }
    }
    return -1;
}

int find_id_B(Book bookArray[], char book_title[], int array_length) {//Finds a book matching the book_title
    for (int i = 0; i < array_length; i++)
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

void title_order(Book bookArray[], int array[], int array_length) {
	int min;
	int temp;
	for(int i=0; i<array_length; i++) {
		min=i;
		for(int j=i+1; j<array_length; j++) {
			if(alphabet_bigger(bookArray[array[min]].title,bookArray[array[j]].title)) {
				min=j;
			}
		}
		temp=array[i];
		array[i]=array[min];
		array[min]=temp;
	}
}
void author_order(Book bookArray[], int array[], int array_length) {
	int min;
	int temp;
	for(int i=0; i<array_length; i++) {
		min=i;
		for(int j=i+1; j<array_length; j++) {
			if(alphabet_bigger(bookArray[array[min]].author,bookArray[array[j]].author)) {
				min=j;
			}
		}
		temp=array[i];
		array[i]=array[min];
		array[min]=temp;
	}
}
void categorie_order(Book bookArray[], int array[], int array_length) {
	int min;
	int temp;
	for(int i=0; i<array_length; i++) {
		min=i;
		for(int j=i+1; j<array_length; j++) {
			if(alphabet_bigger(bookArray[array[min]].categorie,bookArray[array[j]].categorie)) {
				min=j;
			}
		}
		temp=array[i];
		array[i]=array[min];
		array[min]=temp;
	}
}

int init_array_id(Book bookArray[], int array[], int array_length) {//créé un arrayleau des id de book utilisé et renvoie sa vraie taille
	int j=0;
	int res;
	for(int i=0;i<array_length; i++) {
		if(bookArray[i].id!=-1) {
			array[j]=i;
			j++;
		}
	}
	res=j;
	while(j<array_length) {
		array[j]=-1;
		j++;
		
	}
	return res;
}
