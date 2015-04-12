#include <stdio.h>

int mystrlen(char array[]);
void mystrcpy(char src[], char dst[]);
int mystrcmp(char s1[], char s2[]);

int main(){
	char* str1 = "Bob";
	char* str2 = "Billie";
	char* str3 = "Shannon";
	char copyArray[10];
	mystrcpy(str1, copyArray);
	printf("!!!! str1 with a value of \"%s\" HAS BEEN GLORIOUSLY COPIED TO THE WONDERFUL AND AMAZING copyArray !!!!\n", str1);
	printf("!!!! HOLY CRAPADOODLE copyArray HAS NOW BECOME %s !!!!\n", copyArray);
	int cmptmp = mystrcmp(str1, copyArray);
	printf("\nYo so i took this string str1 with a length of %d that says %s and decided to compare it with some other thing i think it was called copyArray and it was as long as %d that reads %s and in the end i got this number back: %d\n", mystrlen(str1), str1, mystrlen(copyArray), copyArray, cmptmp);
	cmptmp = mystrcmp(str2, copyArray);
	printf("\nwell that last time copyArray held in pretty well. so now it's str2 of length %d and reading %s compared with copyArray of length %d and text of %s and in the end i got %d\n", mystrlen(str2), str2, mystrlen(copyArray), copyArray, cmptmp);
	cmptmp = mystrcmp(str3, copyArray);
	printf("\nLAST BUT NOT LEAST IN THE LEFT ARGUMENT *drumrole* ITS str3 COMING IN WITH LENGHT %d AND A READ OF %s ... aaaAAANNNDDDD IN THE RIGHT ARGUMENT ITS THE DREADED copyArray WITH A LENTH OF %d READING %s HERE TO DEFEND HIS TITLE AS CHAMP!!!! THE RESULTS ARE IN!!!! THE OUTCOME OF THEIR COMPARISON WAS... %d!!!!!!!!!!!\n", mystrlen(str3), str3, mystrlen(copyArray), copyArray, cmptmp);
	return 0;
}

int mystrlen(char array[]){
	int toRet = 0;
	int errormax = 1000;
	if(array == NULL){
		return -1;
	}
	while (array[toRet] != '\0' && toRet < errormax){
		toRet++;//error max makes sure things dont go crazy if given an array with no null
	}
	if(toRet == errormax){
		return -1;
	}
	return toRet;
}

void mystrcpy(char src[], char dst[]){
	int cycle = 0;
	while (src[cycle] != '\0'){
		dst[cycle] = src[cycle];
		cycle++;
	}
	dst[cycle] = '\0';
}

int mystrcmp(char str1[], char str2[]){
	int point = 0;
	while (str1[point] == str2[point] && str1[point] != '\0'){
		point++;
	}
	return (str1[point]-str2[point]);
}
