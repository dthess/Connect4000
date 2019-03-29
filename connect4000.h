#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "stdbool.h"

#include "printBoard.h"
#include "checkState.h"
#include "computer.h"

/*
 * displays the main menu
 *
 * @returns menu choice input from user
 */
int menu(){

	printf("\tWelcome to Connect 4000\n\n\n\t1) Player vs. Player\n\n\t"
			"2) Player vs. Computer\n\n\t3) Rules\n\n\t4) Exit\n\n\n\n\tENTER NUMBER"); buffer();
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
 * displays the rules until a 1 from the user is entered
 */
void displayRules(){

	printf("\n\t...it's pretty self-explanatory"
			"\n\n\n\n\tEnter 1 to return to menu\n\n"); buffer();

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
 * takes user input for what column they would like to move in and
 * verifies that column is valid (not full and exists)
 *
 * @param size - board size
 * @param board[size] - 2d board array
 * @param name - current player's name
 * @param turn - 1 for player1's turn, 2 for player2's turn
 */
void playerMove(int size, int* board[size],char* name, int turn){

	printf("\n\t%s's turn\n\tEnter column number\n\t",name);

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
				printf("\n\tInvalid column number, try again");
			}
		}

		// check if column is already full
		if(board[0][columnNum-1]!=0){
			printf("\n\tColumn full, try again\n");
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

	// play for the appropriate player
	if(turn==1){
		board[rowNum][columnNum-1] = 1;
	} else {
		board[rowNum][columnNum-1] = 2;
	}
}

/*
 * main game-management function
 * takes control until user decides not to play another game
 *
 * @param mode - game mode (0 for p vs. p, 1 for p vs. cpu)
 */
void playGame(bool mode){

	char player1Name[50] = "PLayer 1";
	char player2Name[50] = "Computer";
	int boardSize; // max is 118 for my monitor

	printLines();
	printf("\tPlayer 1 enter name\n\tYou will be X"); buffer();
	scanf("%50s",player1Name);
	getLine();

	printLines();
	if(mode==0){
		printf("\tPlayer 2 enter name\n\tYou will be O"); buffer();
		scanf("%50s",player2Name);
		getLine();
	}

	int p1Score=0;
	int p2Score=0;

	bool keepPlaying = 1;
	while(keepPlaying==1){ // changed during "play again" stage

		bool validSize=0;
		while (validSize==0){ // makes sure board size is okay
			printLines();
			printf("\n\tEnter Y board size length for a YxY board (4 minimum)"); buffer();
			scanf("%d",&boardSize);
			getLine();
			if(boardSize<=3){ // make sure size is at least 4
				printLines();
				printf("\tInvalid board size\n\tTry again");
			} else if(boardSize>=100){ // warn about boards over 100
				bool playAnyway = 0;
				printLines();
				printf("\tCaution: Board sizes larger than 100 may run off screen (depending on the size of your monitor)\n"
						"\tContinue anyway?\n\t1) Yes\n\t2) Try a different board size\n"); buffer();
				scanf("%d",&playAnyway);
				getLine();
				if(playAnyway==1) validSize = 1;
				else printLines();
			} else{
				validSize=1;

			}
		}

		//dynamically allocates spaces for board
		int *board[boardSize];
		for(int i=0;i<boardSize;i++){
			board[i] = (int *)malloc((boardSize) * sizeof(int));
		}

		// intitalizes all board elements to 0
		for(int i=0;i<boardSize;i++){
			for(int j=0;j<boardSize;j++){
				board[i][j]=0;
			}
		}

		int turn = 1;
		int gameState = 0;
		char* playerName;
		int msec=0; // for timer
		bool displayTime=0;
		int computerColumn;

		while(gameState==0){ // gameState is 1 for P1 win, 2 for P2 win, and 3 for tie

			printBoard(boardSize,board);

			// display timer if computer just moved
			if(displayTime==1&&turn==1){
				printf("\n\tComputer moved in column %d in %d.%d seconds\n",computerColumn,msec/1000,msec%1000);
			}

			// determine current player's name
			if(turn==1){
				playerName=player1Name;
			} else {
				playerName=player2Name;
			}

			if(mode==0){ // for player vs player
				playerMove(boardSize,board,playerName,turn);
				gameState = checkTie(boardSize,board,gameState);
				gameState = checkWin(boardSize,board,gameState,turn);
				if(turn==1) turn=2;
				else if(turn==2) turn=1;

			} else { // for player vs computer
				if(turn==1){
					playerMove(boardSize,board,playerName,turn);
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkWin(boardSize,board,gameState,turn);
					turn=2;
					msec=0; // for timing
				} else {
					clock_t start = clock(); // for timing
					computerColumn = computerMove(boardSize,board);
					clock_t stop = clock(); // for timing
					msec = (stop-start)*1000 / CLOCKS_PER_SEC; // for timing
					displayTime=1; // for timing

					gameState = checkTie(boardSize,board,gameState);
					gameState = checkWin(boardSize,board,gameState,turn);
					turn=1;
				}
			}
		} // game over

		printBoard(boardSize,board);

		if(mode==1&& gameState==2){ // if the computer just moved, display the time
			printf("\n\tComputer moved in column %d in %d.%d seconds\n",computerColumn,msec/1000,msec%1000);
		}

		// display game result and adjust score
		if(gameState==3){
			printf("\n\n\tTIE GAME");
		} else if (gameState==1) {
			p1Score++;
			printf("\n\n\t%s WINS",player1Name);
		} else if(gameState==2){
			p2Score++;
			printf("\n\n\t%s WINS",player2Name);
		}

		printf("\n\n\t%s\t%s\n\t   %d\t\t   %d",player1Name,player2Name,p1Score,p2Score); // scoreboard
		printf("\n\n\tPlay again?\n\n\t1) yes\n\n\t2) no\n");

		// play again?
		bool validContinue=0;
		while(validContinue==0){
			char* line = getLine();
			for(int i=0;i<strlen(line);i++){ // looks for a 1 or 2 in the input line
				if(line[i]==49){
					validContinue=1;
					break;
				} else if(line[i]==50){
					validContinue=1;
					keepPlaying = 0;
					break;
				}
			}
		}
	}
	return;
}
