#include "stdio.h"
#include "stdlib.h"

#include "util.h"

/*
 * displays the main menu
 * 
 * returns menu choice input from player
 */
int menu(){
	//printLines();
	int choice;	
	printf("\tWelcome to Connect 4000\n\n\n\t\t1) Player vs. Player\n\n\t\t"
			"2) Player vs. Computer\n\n\t\t3) Rules\n\n\t\t4) Exit\n\n\n\n\t\tENTER NUMBER"); buffer();
	scanf("\n%d",&choice);
	return choice;
}

/*
 * 
 */
void displayRules(){
	printLines();
	printf("\t\tEnter 1 to return to menu\n\n"); buffer();
	int useless;
	scanf("\n%d",&useless);
}

/*
 * 
 */
int checkXWin(int size, int* arr[size], int state){  // returns 0 for no winner, 1 for win

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
 * 
 */
int checkOWin(int size, int* arr[size], int state){  // returns 0 for no winner, 2 for win

	int winState = state;

	//check horizontal
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==1)
				if(arr[i][j+1]==1) // 1 in a row
					if(arr[i][j+2]==1) // 2 in a row
						if(arr[i][j+3]==1) // 3 in a row
							winState = 2;

	//check vertical
	for(int i=0;i<size;i++)
		for(int j=0;j<size-3;j++)
			if(arr[j][i]==1)
				if(arr[j+1][i]==1) // 1 in a row
					if(arr[j+2][i]==1) // 2 in a row
						if(arr[j+3][i]==1) // 3 in a row
							winState = 2;

	//check diagonal '\'
	for(int i=0;i<size-3;i++)
		for(int j=0;j<size-3;j++)
			if(arr[i][j]==1)
				if(arr[i+1][j+1]==1) // 1 in a row
					if(arr[i+2][j+2]==1) // 2 in a row
						if(arr[i+3][j+3]==1) // 3 in a row
							winState = 2;


	//check diagonal '/'
	for(int i=0;i<size-3;i++)
		for(int j=3;j<size;j++)
			if(arr[i][j]==1)
				if(arr[i+1][j-1]==1) // 1 in a row
					if(arr[i+2][j-2]==1) // 2 in a row
						if(arr[i+3][j-3]==1) // 3 in a row
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

	printf("\n\n\t\t%s's turn\n\n\t\tEnter column letter\n\t\t",name);

	char column;
	int columnNum;
	int row;

	// make sure the column choice is valid
	int validChoice=0;
	while(validChoice==0){

		// make sure the column choice exists
		int choiceExists = 0;
		while(choiceExists == 0){
			scanf("\n%c",&column);
			columnNum = (int)column;
			if(column>64 && column<=64+size){ // uppercase letter that exists
				choiceExists = 1;
				columnNum-=65;  // normalize from ASCII value
			} else if(column>96 && column<=96+size) { // lowercase letter that exists
				choiceExists = 1;
				columnNum-=97;  // normalize from ASCII value
			} else {
				printf("\n\t\tInvalid column letter, try again");
			}
		}

		// check if column is already full
		if(arr[0][columnNum]!=0){
			printf("\n\t\tColumn full, try again\n");    
		} else { // otherwise find out what row to use
			validChoice = 1;
			for(int i=size;i>=0;i--){
				if(arr[i][columnNum]==0){
					row = i;
					break;
				}
			}
		}
	}

	if(turn==1){
		arr[row][columnNum] = 1;
	} else {
		arr[row][columnNum] = 2;
	}
}

/*
 * 
 */
void computerMove(int size, int* arr[size]){

	// check if 3 in a row (222)
	
	// check if opponent 3 in a row (111)

	// check for 2 in a row and open spot on both ends (0220)
	
	// check if opponent 2 in a row and open both ends (0110)

}

/*
 * 
 */
void playGame(int mode){		//mode 0 for pvp, 1 for cpu 

	char player1Name[50] = "PLayer 1";
	char player2Name[50] = "Computer";
	int boardSize=4;

	printLines();
	printf("\t\tPlayer 1 enter first name\n\t\tYou will be X"); buffer();
	//scanf("%s",player1Name);

	printLines();
	if(mode==0){
		printf("\t\tPlayer 2 enter first name\n\t\tYou will be O"); buffer();
		//scanf("%s",player2Name);
	}

	printLines();
	int validSize=0;
	while (validSize==0){
		printf("\t\tEnter Y board size length for a YxY board (4 minimum)"); buffer();
		//scanf("%d",&boardSize);
		if(boardSize>3 && boardSize<17){
			validSize=1;
		} else if(boardSize>16&&boardSize<27){
			validSize=2;
		} else if(boardSize<4){
			printLines();
			printf("\t\tInvalid board size\n\n\t\tTry again\n\n\n\n");

		} else if(boardSize>=27){
			int playAnyway = 0;
			printLines();
			printf("\t\tBoard size larger than 16 will be *extremely* difficult to comprehend\n\n"
					"\t\tContinue anyway?\n\n\n\n\t\t1) Yes\n\n\t\t2) Try a different board size\n\n\n\n"
					"\t\tENTER NUMBER"); buffer();
			scanf("%d",&playAnyway);
			if(playAnyway==1) validSize = 1;
			else printLines();
		}
	}

	//dynamically allocates spaces for board
	int *board[boardSize];
	for(int i=0;i<boardSize;i++){
		board[i] = (int *)malloc((boardSize) * sizeof(int));      
	}

	int keepPlaying = 1;
	while(keepPlaying==1){
		// intitalizes all board elements to 0
		for(int i=0;i<boardSize;i++){ 
			for(int j=0;j<boardSize;j++){
				board[i][j]=0; 
			}
		}

		int turn = 1;
		int gameState = 0;
		char* playerName;

		while(gameState==0){

			// print board using appropriate function
			if(validSize==1){
				printBoard16(boardSize,board);
			} else if(validSize==2){
				printBoard26(boardSize,board);
			}
			
			// determine current player's name
			if(turn==1){
				playerName=player1Name;
			} else {
				playerName=player2Name;
			}

			if(mode==0){
				playerMove(boardSize,board,playerName,turn);
				if(turn==1){
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkXWin(boardSize,board,gameState);
					turn=2;
				}
				else if(turn==2){
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkOWin(boardSize,board,gameState);
					turn=1;
				}
			} else {
				if(turn==1){
					playerMove(boardSize,board,playerName,turn);	
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkXWin(boardSize,board,gameState);
					turn=2;
				} else {
					computerMove(boardSize,board);
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkOWin(boardSize,board,gameState);
					turn=1;
				}
			}			
		}
		//if gamestate = 1 p1 wins, 2 p2 wins, 3 tie

		if(validSize==1){
			printBoard16(boardSize,board);
		} else if(validSize==2){
			printBoard26(boardSize,board);
		}
		
		if(gameState==3){
			printf("\n\n\t\tTIE GAME\n\n\t\tPlay again?\n\n\t\t1) yes\n\n\t\t2) no\n");
		} else {
			printf("\n\n\t\t%s WINS\n\n\t\tPlay again?\n\n\t\t1) yes\n\n\t\t2) no\n",playerName);
		}
		scanf("%d",&keepPlaying);

	}
}




