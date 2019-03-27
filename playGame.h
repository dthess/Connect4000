#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "util.h"

/*
 * used for getting user input without causing any major bugs due to bad input
 * borrowed from https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
 */
char * getLine(void) {
	char * line = malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;

	if(line == NULL)
		return NULL;

	while(1){
		c = fgetc(stdin);
		if(c == EOF)
			break;

		if(--len == 0) {
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);

			if(linen == NULL) {
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if((*line++ = c) == '\n')
			break;
	}
	*line = '\0';
	return linep;
}

/*
 * displays the main menu
 * 
 * returns menu choice input from player
 */
int menu(){

	printf("\tWelcome to Connect 4000\n\n\n\t\t1) Player vs. Player\n\n\t\t"
			"2) Player vs. Computer\n\n\t\t3) Rules\n\n\t\t4) Exit\n\n\n\n\t\tENTER NUMBER"); buffer();
	char* menuChoice = getLine();
	int menuChoiceInt = 0;
	for(int i=0;i<strlen(menuChoice);i++){ // takes the first int between 1 and 4 in the input line
		if(menuChoice[i]>48&&menuChoice[i]<53){
			menuChoiceInt = menuChoice[i]-48;
			break;
		}
	}
	return menuChoiceInt;
}

/*
 * 
 */
void displayRules(){
	
	printf("\n\t\tDo you really need the rules to connect 4?\n\n\t\tThe objective is literally the name of the game"
			"\n\n\t\tEnter 1 to return to menu\n\n"); buffer();
	
	// wait for 1 to be entered
	while(1){
		char* line = getLine();
		for(int i=0;i<strlen(line);i++){ // looks for a 1 in the input line
			if(line[i]==49){
				return;
			}
		}
	}

}

/*
 * determines whether X has won the game or not
 * 
 * takes the 2d board array and its size as arguments
 * takes the current gameState as argument so that the correct state 
 * can be returned in the event X is not the winner
 * 
 * checks horizontally, vertically, diagonally (\), and then diagonally again (/)
 * 
 * returns the same state value when X has not won, 1 when X has won
 */
int checkXWin(int size, int* arr[size], int state){

	int winState = state;

	//check horizontal
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==1)
				if(arr[i][j+1]==1) // 1 in a row
					if(arr[i][j+2]==1) // 2 in a row
						if(arr[i][j+3]==1) // 3 in a row
							winState = 1;

	//check vertical
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[j][i]==1)
				if(arr[j+1][i]==1) // 1 in a row
					if(arr[j+2][i]==1) // 2 in a row
						if(arr[j+3][i]==1) // 3 in a row
							winState = 1;

	//check diagonal '\'
	for(int i=0;i<size-3;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==1)
				if(arr[i+1][j+1]==1) // 1 in a row
					if(arr[i+2][j+2]==1) // 2 in a row
						if(arr[i+3][j+3]==1) // 3 in a row
							winState = 1;


	//check diagonal '/'
	for(int i=0;i<size-3;i++)
		for(int j=3;j<size;j++)
			if(arr[i][j]==1)
				if(arr[i+1][j-1]==1) // 1 in a row
					if(arr[i+2][j-2]==1) // 2 in a row
						if(arr[i+3][j-3]==1) // 3 in a row
							winState = 1;

	return winState;
}

/*
 * determines whether O has won the game or not
 * 
 * takes the 2d board array and its size as arguments
 * takes the current gameState as argument so that the correct state 
 * can be returned in the event O is not the winner
 * 
 * checks horizontally, vertically, diagonally (\), and then diagonally again (/)
 * 
 * returns the same state value when O has not won, 2 when O has won
 */
int checkOWin(int size, int* arr[size], int state){ 

	int winState = state;

	//check horizontal
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==2)
				if(arr[i][j+1]==2) // 1 in a row
					if(arr[i][j+2]==2) // 2 in a row
						if(arr[i][j+3]==2) // 3 in a row
							winState = 2;

	//check vertical
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[j][i]==2)
				if(arr[j+1][i]==2) // 1 in a row
					if(arr[j+2][i]==2) // 2 in a row
						if(arr[j+3][i]==2) // 3 in a row
							winState = 2;

	//check diagonal '\'
	for(int i=0;i<size-3;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==2)
				if(arr[i+1][j+1]==2) // 1 in a row
					if(arr[i+2][j+2]==2) // 2 in a row
						if(arr[i+3][j+3]==2) // 3 in a row
							winState = 2;


	//check diagonal '/'
	for(int i=0;i<size-3;i++)
		for(int j=3;j<size;j++)
			if(arr[i][j]==2)
				if(arr[i+1][j-1]==2) // 1 in a row
					if(arr[i+2][j-2]==2) // 2 in a row
						if(arr[i+3][j-3]==2) // 3 in a row
							winState = 2;

	return winState;
}

/*
 * determines if game is over due to tie 
 * (all spaces filled)
 * 
 * returns 0 for no tie, 3 for tie
 */
int checkTie(int size, int* arr[size], int state){
	int tieState = state;

	int fullColumns = 0;
	for(int i=0;i<size;i++)
		if(arr[0][i]!=0) fullColumns++;

	if(fullColumns==size) tieState = 3;

	return tieState;
}

/*
 * 
 */
void playerMove(int size, int* arr[size],char* name, int turn){  // turn 1 for player1, 2 for player2

	printf("\n\t\t%s's turn\n\t\tEnter column number\n\t\t",name);

	int columnNum;
	int rowNum;

	// make sure the column choice is valid (column isn't full)
	int validChoice=0;
	while(validChoice==0){

		// make sure the column choice exists (column number is <= size)
		int choiceExists = 0;
		while(choiceExists == 0){
			scanf("\n%d",&columnNum);
			if(columnNum>0 && columnNum<=size){ 
				choiceExists = 1;
			}  else {
				printf("\n\t\tInvalid column number, try again");
			}
		}

		// check if column is already full
		if(arr[0][columnNum-1]!=0){
			printf("\n\t\tColumn full, try again\n");    
		} else { // otherwise find out what row to use
			validChoice = 1;
			for(int i=size-1;i>=0;i--){ // start at lowest row and move up
				if(arr[i][columnNum-1]==0){
					rowNum = i;
					break;
				}
			}
		}
	}

	if(turn==1){
		arr[rowNum][columnNum-1] = 1;
	} else {
		arr[rowNum][columnNum-1] = 2;
	}
}

/*
 * returns comlumn computer moved in
 */
int computerMove(int size, int* arr[size]){

	int column=-1;

	// make list of all spaces computer can move
	int rowArray[size];
	for (int i=0;i<size;i++){
		for (int j=size-1;j>=0;j--){
			if(arr[j][i]==0){
				rowArray[i] = j; // open space found
				break;
			} else if(j==0){
				rowArray[i] = -1; // column is full
			}
		}
	}

	for(int i=0;i<size;i++)printf("%d ",rowArray[i]);

	// check if each of those possible moves would win the game for the computer
	for(int i=0;i<size;i++){
		if(rowArray[i]!=-1){
			int temp = arr[rowArray[i]][i];
			arr[rowArray[i]][i] = 2;
			int winningMove = checkOWin(size,arr,0);
			if(winningMove==2){ // winning move found
				column = i;
				column++;
				return column;
			}
			arr[rowArray[i]][i] = temp; // reset space
		}
	}

	// check if each of those possible moves would win the game for the opponent (to block)
	for(int i=0;i<size;i++){
		if(rowArray[i]!=-1){
			int temp = arr[rowArray[i]][i];
			arr[rowArray[i]][i] = 1;
			int winningMove = checkXWin(size,arr,0);
			if(winningMove==1){ // winning move for opponent found
				arr[rowArray[i]][i] = 2;
				column = i;
				column++;
				return column;
			}
			arr[rowArray[i]][i] = temp; // reset space
		}
	}

	// check for (0220)

	// check for (0110)


	// no best move could be found, move randomly
	while(1){
		int random = clock()%size+1;
		if(rowArray[random]!=-1){
			arr[rowArray[random]][random] = 2;
			column = random;
			column++;
			return column;
		}
	}
}


