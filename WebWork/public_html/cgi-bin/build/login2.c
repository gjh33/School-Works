#include <stdio.h>
#include <stdlib.h>

int main(){
	char user[50];//entered username
	char pass[50];//entered pass
	int i;//iterator
	char x;//used when obtaining parameters
	while(getchar()!='=');//get to the first parameter
	for (i=0; (x=getchar())!='&'; i++){//read the first param char by char
		if (x==EOF) break;
		user[i] = x;
	}
	user[i] = '\0'; //add the null
	//now for the second param we just repeat
	while(getchar()!='=');
	for (i=0; (x=getchar())!='&'; i++){
		if (x==EOF) break;
		pass[i] = x;
	}
	pass[i] = '\0';
	//verification
	FILE* fp;
	char fuser[50];//used when reading from file
	char fpass[50];//used when reading from file
	char name[50];
	int userFound = 0;
	
	printf("Content-type: text/html\r\n\r\n");
	
	fp = fopen("data/members.CSV", "rt");//open data file and check we opened it
	if (fp == NULL) {
		printf("<html><head><title>Error 51</title></head><body>Error Opening members.CSV</body></html>");
		return 1;
	}
	while(fscanf(fp, "%s", name) != 0){//loop until we scan nothing and then decide if we found someone
		fscanf(fp, "%s", fuser);
		if (strcmp(user, fuser) == 0){
			userFound = 1;
			fscanf(fp, "%s", fpass);
			if (strcmp(fpass, pass) != 0){
				printf("<html><head><title>Wrong Password!</title></head><body><h3>Wrong Password</h3><br><a href=\"http://cs.mcgill.ca/~sarres/welcome.html\">Try Again!</a></body></html>");
				fclose(fp);
				return 2;
			}
			break;
		}
		while((x=fgetc(fp))!='\n'){
			if(x==EOF) break;
		}
		if(x==EOF) break;
	}
	if (!userFound){
		//print wrong username page with link
		printf("<html><head><title>Wrong User</title></head><body><h3>Username doesn't exist!</h3><br><a href=\"http://cs.mcgill.ca/~sarres/welcome.html\">Try Again!</a></body></html>");
		fclose(fp);
		return 3;
	}
	//create the validator for security when passing values
	char validator[3];
	validator[0] = name[0] + 1;
	//find the \0 then access the last element
	for(i=0; (x=name[i])!='\0'; i++);
	validator[1] = name[i-1] + 1;
	validator[3] = '\0';
	//our validator is first and last char of name + 1
	//print successful Log in page with link using validator
	printf("<html><head><title>Success!!!!</title></head><body><h3>Congrats on loggin in! Good Job!</h3><br><a href=\"http://cs.mcgill.ca/~sarres/cgi-bin/MyFacebookPage.py?name=%s&val=%s\">Go to my feed!</a></body></html>", name, validator);

	//cleanup
	fclose(fp);
	return 0;
}
