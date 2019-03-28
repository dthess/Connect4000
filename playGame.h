#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "stdbool.h"

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

		if(--len == 0){
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

	printf("\n\t\tCome on it's pretty self-explanatory"
			"\n\n\n\n\t\tEnter 1 to return to menu\n\n"); buffer();

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
int checkXWin(int size, int* board[size], int state){

	int winState = state;

	int possibleMoves[size]; // stores row index for each column
	for (int i=0;i<size;i++){
		for (int j=size-1;j>=0;j--){
			if(board[j][i]==0){
				possibleMoves[i] = j; // open space found
				break;
			} else if(j==0){
				possibleMoves[i] = -1; // column is full
			}
		}
	}

	//check horizontal
	for(int k=0;k<size;k++){
		int i=possibleMoves[k]+1;
	//	printf("\n%d %d",k,i+1);
		if(possibleMoves[k]!=-1&&i<size){
	//		printf(" CHECKING horizontal %d %d",k,i+1);
			for(int j=0;j<size-3;j++)
				if(board[i][j]==1)
					if(board[i][j+1]==1) // 1 in a row
						if(board[i][j+2]==1) // 2 in a row
							if(board[i][j+3]==1) // 3 in a row
								winState = 1;
		}
	}

	//check vertical
	for(int i=0;i<size;i++)
		if(possibleMoves[i]<size-3&&possibleMoves[i]!=-1){
			//printf("CHECKING vert %d\n",+1);
			for(int j=0;j<size-3;j++)
				if(board[j][i]==1)
					if(board[j+1][i]==1) // 1 in a row
						if(board[j+2][i]==1) // 2 in a row
							if(board[j+3][i]==1) // 3 in a row
								winState = 1;
		}

	//check diagonal '\'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
	//	printf("\nright diagonal k: %d i: %d",k,i);
		if(i<size-3&&i!=-1){
		//	printf("CHECKING");
			for(int j=0;j<size-3;j++)
				if(board[i][j]==1)
					if(board[i+1][j+1]==1) // 1 in a row
						if(board[i+2][j+2]==1) // 2 in a row
							if(board[i+3][j+3]==1) // 3 in a row
								winState = 1;
		}
	}


	//check diagonal '/'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
	//	printf("\nleft diagonal k: %d i: %d",k,i);
		if(i<size-3&&i!=-1){
		//	printf("CHECKING");
			for(int j=3;j<size;j++)
				if(board[i][j]==1)
					if(board[i+1][j-1]==1) // 1 in a row
						if(board[i+2][j-2]==1) // 2 in a row
							if(board[i+3][j-3]==1) // 3 in a row
								winState = 1;
		}
	}

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
int checkOWin(int size, int* board[size], int state){

	int winState = state;

	int possibleMoves[size];
	for (int i=0;i<size;i++){
		for (int j=size-1;j>=0;j--){
			if(board[j][i]==0){
				possibleMoves[i] = j; // open space found
				break;
			} else if(j==0){
				possibleMoves[i] = -1; // column is full
			}
		}
	}

	//check horizontal
	for(int k=0;k<size;k++){
		int i=possibleMoves[k]+1;
		if(possibleMoves[k]!=-1&&i<size){
			for(int j=0;j<size-3;j++)
				if(board[i][j]==2)
					if(board[i][j+1]==2) // 1 in a row
						if(board[i][j+2]==2) // 2 in a row
							if(board[i][j+3]==2) // 3 in a row
								winState = 2;
		}
	}

	//check vertical
	for(int i=0;i<size;i++)
		if(possibleMoves[i]<size-3&&possibleMoves[i]!=-1){
			//printf("CHECKING vert %d\n",+1);
			for(int j=0;j<size-3;j++)
				if(board[j][i]==2)
					if(board[j+1][i]==2) // 1 in a row
						if(board[j+2][i]==2) // 2 in a row
							if(board[j+3][i]==2) // 3 in a row
								winState = 2;
		}

	//check diagonal '\'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
		if(i<size-3&&i!=-1){
			//printf("CHECKING diag %d\n",+1);
			for(int j=0;j<size-3;j++)
				if(board[i][j]==2)
					if(board[i+1][j+1]==2) // 1 in a row
						if(board[i+2][j+2]==2) // 2 in a row
							if(board[i+3][j+3]==2) // 3 in a row
								winState = 2;
		}
	}

	//check diagonal '/'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
		if(i<size-3&&i!=-1){
			for(int j=3;j<size;j++)
				if(board[i][j]==2)
					if(board[i+1][j-1]==2) // 1 in a row
						if(board[i+2][j-2]==2) // 2 in a row
							if(board[i+3][j-3]==2) // 3 in a row
								winState = 2;
		}
	}

	return winState;
}

/*
 * determines if game is over due to tie (all spaces filled and no winner)
 *
 * takes the 2d board array and its size as arguments
 * takes the current gameState as argument so that the correct state
 * can be returned in the event of no tie
 *
 * returns the same state value when no tie, 3 for a tie
 */
int checkTie(int size, int* board[size], int state){
	int tieState = state;

	// compares number of full columns to size of board
	int fullColumns = 0;
	for(int i=0;i<size;i++)
		if(board[0][i]!=0) fullColumns++;
	if(fullColumns==size) tieState = 3;

	return tieState;
}

/*
 * gets user input
 */
void playerMove(int size, int* board[size],char* name, int turn){  // turn 1 for player1, 2 for player2

	printf("\n\t\t%s's turn\n\t\tEnter column number\n\t\t",name);

	int columnNum;
	int rowNum;

	// make sure the column choice is valid (column isn't full)
	bool validChoice=0;
	while(validChoice==0){

		// make sure the column choice exists (column number is <= size)
		bool choiceExists = 0;
		while(choiceExists == 0){

			scanf("%d",&columnNum);
			getLine();
			if(columnNum>0 && columnNum<=size){ // make sure column isn't too big or small
				choiceExists = 1;
			}  else {
				printf("\n\t\tInvalid column number, try again");
			}
		}

		// check if column is already full
		if(board[0][columnNum-1]!=0){
			printf("\n\t\tColumn full, try again\n");
		} else { // otherwise find out what row to use
			validChoice = 1;
			for(int i=size-1;i>=0;i--){ // start at lowest row and move up
				if(board[i][columnNum-1]==0){
					rowNum = i;
					break;
				}
			}
		}
	}

	if(turn==1){
		board[rowNum][columnNum-1] = 1;
	} else {
		board[rowNum][columnNum-1] = 2;
	}
}

/*
 * uses a series of steps to determine the next best move for the computer and moves there
 *
 * takes the 2d board array and its size as arguments
 *
 * returns the column the computer moved in
 */
int computerMove(int size, int* board[size]){

	int column, temp, temp2, i, j, winningMove;

	// STEP 1: make list of all spaces computer can move
	int possibleMoves[size]; // array of row indexes
	for (i=0;i<size;i++){
		for (j=size-1;j>=0;j--){
			if(board[j][i]==0){
				possibleMoves[i] = j; // open space found
				break;
			} else if(j==0){
				possibleMoves[i] = -1; // column is full
			}
		}
	}

	// STEP 2: check if any one of those possible moves would win the game for the computer
	for(i=0;i<size;i++){
		if(possibleMoves[i]!=-1){
			temp = board[possibleMoves[i]][i];
			board[possibleMoves[i]][i] = 2;
			winningMove = checkOWin(size,board,0);
			if(winningMove==2){ // winning move found
				column = i;
				column++;
				return column;
			}
			board[possibleMoves[i]][i] = temp; // if not, reset space
		}
	}

	// STEP 3: check if any one of those possible moves would win the game for the opponent (to block)
	for(i=0;i<size;i++){
		if(possibleMoves[i]!=-1){
			temp = board[possibleMoves[i]][i];
			board[possibleMoves[i]][i] = 1;
			winningMove = checkXWin(size,board,0);
			if(winningMove==1){ // winning move for opponent found
				board[possibleMoves[i]][i] = 2;
				column = i;
				column++;
				return column;
			}
			board[possibleMoves[i]][i] = temp; // if not, reset space
		}
	}

	// STEP 4: check if any two of those possible moves would win the game for the computer
	for(i=0;i<size-3;i++){
		for(j=1;j<4;j++){ // cycle offset values 1 through 3
			temp = board[possibleMoves[i]][i];
			temp2 = board[possibleMoves[i+j]][i+j];
			board[possibleMoves[i]][i] = 2;
			board[possibleMoves[i+j]][i+j] = 2;
			winningMove = checkOWin(size,board,0); // check if its a winning pair of moves
			if(winningMove == 2){ // if its a winning pair of moves, move in right space
				board[possibleMoves[i]][i] = temp;  // reset the left space
				column = i+j;
				column++;
				return column;
			}
			board[possibleMoves[i]][i] = temp; // reset the left space
			board[possibleMoves[i+j]][i+j] = temp2; // reset the right space
		}
	}


	// STEP 5: check if any two of those possible moves would win the game for the opponent (block one)
	for(i=0;i<size-3;i++){
		for(j=1;j<4;j++){ // cycle values 1 through 3
			temp = board[possibleMoves[i]][i];
			temp2 = board[possibleMoves[i+j]][i+j];
			board[possibleMoves[i]][i] = 1;
			board[possibleMoves[i+j]][i+j] = 1;
			winningMove = checkXWin(size,board,0); // check if its a winning pair of moves
			if(winningMove == 1){ // if its a winning pair of moves, move in the right space
				board[possibleMoves[i]][i] = temp; // reset the left space
				board[possibleMoves[i+j]][i+j] = 2;
				column = i+j;
				column++;
				return column;
			}
			board[possibleMoves[i]][i] = temp; // reset the left space
			board[possibleMoves[i+j]][i+j] = temp2; // reset the right space
		}
	}

	// STEP 6: just look for any O to play next to (mostly used in first few turns)
	for(i=1;i<size-1;i++){
		if(board[size-1][i]==2){
			if(possibleMoves[i-1]==size-1 || possibleMoves[i-1]==size-2){ // looking to the left
				board[possibleMoves[i-1]][i-1] = 2;
				column = i;
				return column;
			} else if(possibleMoves[i+1]==size-1 || possibleMoves[i+1]==size-2){ // looking to the right
				board[possibleMoves[i+1]][i+1] = 2;
				column = i+2;
				return column;
			}
		}
	}

	// no best move could be found, move randomly (usually only first turn)
	while(1){
		int random = clock()%size;
		if(possibleMoves[random]!=-1){
			board[possibleMoves[random]][random] = 2;
			column = random;
			column++;
			return column;
		}
	}
}


