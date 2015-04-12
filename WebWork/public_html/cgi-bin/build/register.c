#include <stdlib.h>
#include <stdio.h>

int main() {

	int doesExist = 0;
	char tmp[100];
	tmp[0] = 'p';
	char name[50];
	char pass[50];
	printf("Content-Type:text/html\n\n");
	printf("<html>");
	
	int pos = 0;
	char c;
	while (getchar() != '=');//get to the first variable
	for (pos=0; (c = getchar()) != '&'; pos++){//read into name
		name[pos] = c;
	}
	name[pos] = '\0';
	while (getchar() != '=');//get to next variable
	for (pos=0; (c = getchar()) != EOF; pos++){//read into pass
		if (c == '&') break; // DELETE FOR SERVER RUN
		pass[pos] = c;
	}
	pass[pos] = '\0';
	FILE* fp;
	FILE* rf;
	
	fp = fopen("build/accounts.info", "at");
	rf = fopen("build/accounts.info", "rt");
	if (fp == NULL){
		printf("<body><h1>Unable to access accounts.info</h1></body>");
		return 1;
	}
	while(fgetc(rf) != '&') {
		if (feof(rf)) break;
	}
	while(fscanf(rf, "%s", tmp) != 0){
		if (strcmp(tmp, name) == 0){
			printf("<body><h1>Username Already Exists</h1></body>");
			return 2;
		}
		while((c = fgetc(rf)) != '&'){
			if(c == EOF) break;
		}
		if(c == EOF) break;
	}
	fprintf(fp, "&%s\n#%s\n", name, pass);
	fputs(":0\n:0@0\n:100\n:0\n:100\n:none\n:none\n", fp);
	fclose(fp);
	fclose(rf);
	printf("<script language=\"javascript\">window.location.href = \"http://www.cs.mcgill.ca/~ljones15/hungerGames.html\"</script>");
	printf("</html>");
	return 0;
}
