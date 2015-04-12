#include <stdio.h>
#include <stdlib.h>

struct PROFILE {
	int incurrentGame;
	int x;
	int y;
	int hunger;
	int strength;
	int health;
	char Alliance[50];
	char Allies[500];
};

int main() {
	//INITIALIZE
	printf("Content-Type:text/html\n\n");
	printf("<html>\n");
	printf("<head><title>Den Hunger Games</title></head>\n");
	
	//GET USERNAME AND PASS FROM DATA
	char Name[50];
	char Pass[50];
	int ptr;
	char c;
	while (getchar() != '=');//get to the first value
	for (ptr=0; (c = getchar()) != '&'; ptr++) {//add into Name
		Name[ptr] = c;
	}
	Name[ptr] = '\0';
	while(getchar() != '=');//get to next value
	for (ptr=0; (c = getchar()) != EOF; ptr++) {//add into Pass
		if (c == '&') break;//just for use outside of server
		Pass[ptr] = c;
	}
	Pass[ptr] = '\0';
	//CHECK CURRENT USERS AND VERIFY
	FILE* fp;
	char tmp[50];
	int userAuthent = 0;
	fp = fopen("build/accounts.info", "rt");
	if (fp == NULL) {
		printf("<body><h1>Unable to access accounts.info</h1></body>");
		return 1;
	}
	while(fgetc(fp) != '&') {//get to first name, if no names break
		if (feof(fp)) break;
	}
	while(fscanf(fp, "%s", tmp) != 0) {
		if (strcmp(tmp, Name) == 0) {
			while(fgetc(fp) != '#');//get to pass
			fscanf(fp, "%s", tmp);
			if (strcmp(tmp, Pass) ==0) {
				userAuthent = 1;
				break;
			}
			else {//wrong pass
				printf("<body><h1>Wrong Password</h1></body>");
				return 2;
			}
		}
		while((c=fgetc(fp)) != '&') {
			if (c == EOF) break;
		}
		if(c == EOF) break;
	}
	if (!userAuthent) {
		printf("<body><h1>That username doesn't exist</h1><h3>You can create an account on the main page</h3></body>");
		return 3;
	}
	//LOAD PROFILE
	struct PROFILE user;
	while (fgetc(fp) != ':');
	fscanf(fp, "%d", &user.incurrentGame);
	while (fgetc(fp) != ':');
	fscanf(fp, "%d", &user.x);
	fgetc(fp);
	fscanf(fp, "%d", &user.y);
	while (fgetc(fp) != ':');
	fscanf(fp, "%d", &user.hunger);
	while (fgetc(fp) != ':');
	fscanf(fp, "%d", &user.strength);
	while (fgetc(fp) != ':');
	fscanf(fp, "%d", &user.health);
	while (fgetc(fp) != ':');
	fscanf(fp, "%s", user.Alliance);
	while (fgetc(fp) != ':');
	fscanf(fp, "%s", user.Allies);
	//SET UP LOGIN PAGE
	FILE* form;
	int actionCounter = 0;
	form = fopen("./forms/login.frm", "rt");
	while ((c = fgetc(form)) != EOF){
		//check for replacement char
		if(c == '%') {
			//actions
			if (actionCounter == 0) {
				printf("%d.%d", user.x, user.y);
			}
			else if (actionCounter == 1) {
				printf("%d", user.health);
			}
			else if (actionCounter == 2) {
				printf("%d", user.hunger);
			}
			else if (actionCounter == 3) {
				printf("%d", user.strength);
			}
			else if (actionCounter == 4) {
				printf("%s", user.Alliance);
			}
			else if (actionCounter == 5) {
				//print allies if there are some, else print none
			}
			else if (actionCounter == 6) {
				if (user.incurrentGame == 0) {
					printf("<b>You are currently not in a game</b><br />");
				}
			}
			//Increment Counter
			actionCounter++;
		}
		//otherwise spit it back out
		else {
			putchar(c);
		}
	}
	//CLOSURE
	fclose(fp);
	fclose(form);
	printf("</html>");
	return 0;
}
