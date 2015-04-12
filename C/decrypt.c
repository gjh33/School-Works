#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i;
	int j;
	FILE *curFile;
	FILE *curOut;
	unsigned long int tmp[1];
	unsigned long int tmp2;
	unsigned long int tmp3;
	unsigned char binForm;
	char *token;
	char *last;
	char newFileName[100];
	if (argc <= 1){
		printf("error: no files specified\n");
		return 1;
	}
	for (i=1; i<argc; i++) {
		curFile = fopen(argv[i], "rb");
		if (curFile == NULL){
			printf("Error: %s does not exist\n", argv[i]);
			continue;
		}
		token = strtok(argv[i], ".");
		strcat(newFileName, token);
		while (token!=NULL){
			last = token;
			token = strtok(NULL, ".");
			if (token != NULL){
				strcat(newFileName, ".");
				strcat(newFileName, token);
			}
		}
		if (strcmp(last, "RSA13") != 0){
			printf("Error: Expecting .RSA13 file\n");
			continue;
		}	
		else{
			newFileName[strlen(newFileName)-6] = '\0';
			curOut = fopen(newFileName, "wb");
			while(!feof(curFile)){
				fread(tmp, 4, 1, curFile);
				printf("before: %lu\n", tmp[0]);
				tmp2 = tmp[0];
				tmp2 = tmp2%299;
				tmp3 = 1;
				for (j=0; j<113; j++){
					tmp3 = tmp3*tmp2;
					tmp3 = tmp3%299;
				}
				binForm = (unsigned char) tmp3;
				printf("after: %d\n", binForm);
				fwrite(&binForm, 1, 1, curOut);
			}
		}
		
		fclose(curFile);
		fclose(curOut);
	}
	return 0;
}
