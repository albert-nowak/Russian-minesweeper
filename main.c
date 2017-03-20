#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// GLOBAL VARs
#define EXIT "exit"
#define CHEAT 1

int surfaceWidth = 8;
int surfaceHeigth = 8;
int allFields = 64;
int fieldsLeft = 64;

char surface[8][8];
char mines[8][8];

int minesCount = 10;
bool mainLoop = true;
bool isOver = false;


// Functions
void prepSurface();
void drawSurface();
void setMines();
bool handleUserInteraction();
void handleError(char *message);
void handleMessage(char *message);
int translate(char letter);
void gameOver();
void winScenario();
void showMines();

// Main
int main(){

	// before game
	setMines();
	prepSurface();

	while(mainLoop){

		// clear screen
		system("clear");

		//hint for user
		printf("Notice that X is a number and Y is a letter!\n");
		printf("Fields left: %d\n", fieldsLeft);

		if(CHEAT == 1){
			showMines();
		}

		// game main loop
		drawSurface();

		if(!handleUserInteraction()){
			if(!isOver){
				printf("Press any key to continue...");
				getchar();
			} else {
				gameOver();
			}
		}
		if(fieldsLeft == minesCount){
			winScenario();
		}
	}

	return 0;
}

void prepSurface(){

	int i, j;

	for(i=0;i<surfaceHeigth;i++){
		for(j=0;j<surfaceWidth;j++){
			surface[i][j] = '+';
		}
	}
}

void drawSurface(){

	int i, j, k;
	char upperLett[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

	// Draw upper row with letters
	printf("\n     "); //5 empty spaces
	for(k=0;k<surfaceWidth; k++){
		printf("%c ", upperLett[k]);
	}
	printf("\n");

	// Draw surface with left nums
	int leftCounter = 0;
	for(i=0;i<surfaceHeigth;i++){
		printf(" %d | ", ++leftCounter);
		for(j=0;j<surfaceWidth;j++){
			printf("%c ", surface[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void setMines(){
	
	int i, mine_x, mine_y;
	bool setCorrectly = false;
	time_t t;
	srand((unsigned) time(&t));

	// Fill mines array with default data like '#'
	int x, y;
	for(x = 0; x < surfaceHeigth; x++){
		for(y = 0; y < surfaceWidth; y++){
			mines[x][y] = '#';
		}
	}

	for(i = 0; i < minesCount; i++){
		while(!setCorrectly){		// while i don't hace correct data
			mine_x = rand() % 8;
			mine_y = rand() % 8;

			//debug
			// printf("mine_x: %d\n", mine_x);
			// printf("mine_y: %d\n", mine_y);

			if(mines[mine_x][mine_y] != 'x'){
				mines[mine_x][mine_y] = 'x';
				setCorrectly = true;
			}
		}
		setCorrectly = false;
	}

	// DEBUG
	// int j, k;
	// char upperLett[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	// printf("\n     "); //5 empty spaces
	// for(k=0;k<surfaceWidth; k++){
	// 	printf("%c ", upperLett[k]);
	// }
	// printf("\n");
	// int leftCounter = 0;
	// for(j=0;j<surfaceHeigth;j++){
	// 	printf(" %d | ", ++leftCounter);
	// 	for(k=0;k<surfaceWidth;k++){
	// 		printf("%c ", mines[j][k]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");


}

bool handleUserInteraction(){

	char buffor[5];

	printf("Enter x and y: ");
	if(!fgets(buffor, 5, stdin)){		// error case
		handleError("Read error!");
	}

	if(strcmp(buffor, EXIT) == 0){		// exit case
		mainLoop = false;
		return false;
	}

	// convert char into integer
	int user_x = buffor[0] - '0';
	int user_y = buffor[1] - 'a';

	// simple validation
	if(user_x > 8 || user_x < 1 || user_y < 0 || user_y > 8){
		//printf("%d %d\n", user_x, user_y);
		handleError("IndexError!");
		return false;
	}

	// here i have correct data to work with
	// printf("%d %c\n", user_x, buffor[1]);
	
	// Check if x and y hited a bomb!
	user_y = translate(buffor[1]) -1;
	user_x -= 1;

	// printf("%d %d\n", user_x, user_y);
	// printf("%c",mines[user_x][user_y]);

	if(surface[user_x][user_y] == '0'){
		handleMessage("You already visited this field!");
		return false;
	}

	if(mines[user_x][user_y] != 'x'){
		surface[user_x][user_y] = '0';
		fieldsLeft = allFields - 1;
	} else {
		isOver = true;
		return false;
	}

	return true;
}

void handleError(char *error){
	printf("Problem: %s\n", error);
}

void handleMessage(char *message){
	printf("Message: %s\n", message);
}

int translate(char letter){
	switch(letter){
		case 'a':
			return 1;
			break;
		case 'b':
			return 2;
			break;
		case 'c':
			return 3;
			break;
		case 'd':
			return 4;
			break;
		case 'e':
			return 5;
			break;
		case 'f':
			return 6;
			break;
		case 'g':
			return 7;
			break;
		case 'h':
			return 8;
			break;
		default:
			return 0;
	}
}

void gameOver(){
	mainLoop = false;
	system("clear");
	printf("\n\n\n Game Over!!!\n\n\n");
	sleep(3);
	system("clear");
	printf("\n\nMines map\n");
	printf("(x is a bomb)\n\n");
	
	showMines();
}

void winScenario(){
	mainLoop = false;
	system("clear");
	printf("\n\n\n You won!!!\n");
	printf("\n Congratulations!\n\n\n");
	sleep(3);
	system("clear");
	printf("\n\nMines map\n");
	printf("(x is a bomb)\n\n");
	showMines();
	sleep(2);
}

void showMines(){
	int j, k;
	char upperLett[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	printf("\n     ");
	for(k=0;k<surfaceWidth; k++){
		printf("%c ", upperLett[k]);
	}
	printf("\n");
	int leftCounter = 0;
	for(j=0;j<surfaceHeigth;j++){
		printf(" %d | ", ++leftCounter);
		for(k=0;k<surfaceWidth;k++){
			printf("%c ", mines[j][k]);
		}
		printf("\n");
	}
	printf("\n");

}





