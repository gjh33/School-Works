#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i;
	int j;
	FILE *curFile;
	FILE *curOut;
	unsigned char tmp[1];
	unsigned long int tmp2;
	unsigned long int tmp4=0;
	char src[100];
	char dest[100];
	if (argc <= 1) {
		printf("error: no files specified\n");
		return 1;
	}
	for (i=1;i<argc;i++){
		curFile = fopen(argv[i], "rb");
		strcpy(dest, argv[i]);
		strcpy(src, ".RSA13");
		strcat(dest, src);
		if (curFile == NULL) {
			printf("Error: %s does not exist\n", argv[i]);
		}
		else{
			curOut = fopen(dest, "wb");
			while(!feof(curFile)){
				fread(tmp, 1, 1, curFile);
				printf("before: %d\n", tmp[0]);
				tmp2 = tmp[0];
				tmp2 = tmp2%299;
				tmp4 = 1;
				for (j=0; j<257; j++)
				{
					tmp4 = tmp4*tmp2;
					tmp4 = tmp4%299;
				}
				printf("after: %lu\n", tmp4);
				fwrite(&tmp4, 4, 1, curOut);
			}
		}
		fclose(curFile);
		fclose(curOut);
	}
	return 0;
}


