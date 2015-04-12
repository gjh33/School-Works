#include <stdio.h>
#include <string.h>

void printTriangle(int x);//x is inp, des is destination array

int main() {
	int range;//range of triangle array (# of rows)
	int domain;//domain of triangle array (# of col)
	char uInput[5] = "YES\n";//it's 5 to compensate for when fgets also gets the carriange return
	

	while (strcmp(uInput, "YES\n")==0 || strcmp(uInput, "yes\n")==0 || strcmp(uInput, "Y\n")==0 || strcmp(uInput, "y\n")==0) {
		printf("Welcome to the triangle machine!\n");
		printf("Please enter the size of the base: \n>>");
		int inp = 0;//our input variable
		while (inp<1){
			scanf("%d", &inp);
		}
		while(getchar() != '\n');//CLEARS BUFFER after scanf (why the heck is that not the default??? or why doesn't fflush work? why cant they make a function that does that)
		printTriangle(inp);// calls teh function that formats and prints the triangle
		printf("would you like to try again? \n>>");
		fgets(uInput, 5, stdin);//gets the input + the carriage return
	}
	return 0;
}

void printTriangle(int x){
	int charPerRow = (2*x)-1;//how many characters per row
	int numRows;//number of rows in the triangle
	int curRow;//current row used in for loop
	int curChar;//current char used in for loop
	int sideSpaces; //number of spaces to the left or right of the stars in the current row
	int curNumStars;//current stars on this line

	if((x%2)==1){// checks if we are building an odd or even triangle
		numRows = (x+1)/2;
	}
	else{
		numRows = x;
	}

	for (curRow=1; curRow <= numRows; curRow++){
		if((x%2)==1){//are we building an even or odd triangle.
			curNumStars = (2*curRow)-1;
		}
		else{
			curNumStars = curRow;
		}
		sideSpaces = (charPerRow - ((2*curNumStars)-1))/2;
		for(curChar=0; curChar<charPerRow; curChar++){
			if(curChar<sideSpaces){//before the asterixes
				putchar(' ');;
			}
			else if(curChar<(sideSpaces+(2*curNumStars)-1)){//when in the asterix part, alternate between space and star
				//these if statements check whether to put a * or a _. curChar-sideSpaces is equal to how many char i placed after the side spaces
				//if it's an even number then place a * else place an asterix
				if((curChar-sideSpaces)%2==0){
					putchar('*');
				}
				else{
					putchar(' ');
				}
			}
			else{//after the star portion
				putchar(' ');
			}
		}
		printf("\n");
	}
}
