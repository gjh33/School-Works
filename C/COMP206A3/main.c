#include <stdio.h>
#include "list.h"
#include <string.h>
#include <ctype.h>

char* toUpperS(char* str);

int main() {

	FILE *fp;//file pointer
	printf("Please enter a file name/path: ");
	char Uin[100];//user input
	char Uin2[10];//used for YES yes Yes y Y loop
	Uin2[0] = '\0';//just a fail safe for my toUpperS
	scanf("%s", Uin);//scan for the file name
	while(getchar() != '\n');//this clears the input buffer
	fp = fopen(Uin, "rt");
	while(fp == NULL){//while the file is invalid, repeat.
		printf("\nI'm sorry that file is incorrect. Try Again: ");
		scanf("%s", Uin);
		while(getchar() != '\n');
		fp = fopen(Uin, "rt");
	}
	while (!feof(fp)){
		int tmp;//used to store fscanf results
		fscanf(fp, "%d", &tmp);
		if(fgetc(fp) != '\n'){//clears the \n
			break;//breaks if it's the last number
			//we dont add because for some reason this while loop loops one extra time and picks up the last number twice... idk why
		}
		add(tmp);//add to linked list. add is public function of list module
	}
	printf("\n");
	prettyPrint();//print from list module
	do {
		printf("\nPlease provide the integer you wish to delete from the list: ");
		int tmp;//used for input
		scanf("%d", &tmp);
		while(getchar() != '\n');//clears input buffer
		if (delete(tmp)){//delete from list module and checks if someone was deleted
			printf("\nNUMBER WAS DELETED");
		}
		else {
			printf("\nNUMBER WAS NOT FOUND");
		}
		printf("\n");
		prettyPrint();//prints the new list
		printf("\nWould you like to delete another(y/yes)? ");
		scanf("%s", Uin2);//scan the user's response
		while(getchar() != '\n');//clears input buffer
	} while(strcmp(toUpperS(Uin2), "Y") == 0 || strcmp(toUpperS(Uin2), "YES") == 0); 
	return 0;
}

//toUpperS takes a string and converts it to an upper case string. It does not return a new string.
char* toUpperS(char* str){
	int curInd = 0;//current index
	while(str[curInd] != '\0'){
		str[curInd] = toupper(str[curInd]);
		curInd ++;
	}
	return str;
}
