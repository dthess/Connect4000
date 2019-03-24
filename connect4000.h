#include "stdio.h"
#include "stdlib.h"

#include "computer.h"
#include "utility.h"

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
void playGame(int mode){		//mode 0 for pvp, 1 for cpu 

	char player1Name[50] = "PLayer 1";
	char player2Name[50] = "Computer";
	int boardSize=12;

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
		} else if(boardSize<4){
			printLines();
			printf("\t\tInvalid board size\n\n\t\tTry again\n\n\n\n");
		} else if(boardSize>16){
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
	int *board[boardSize+2];  // +2 is for -1 border (for checking win state)
	for(int i=0;i<boardSize+2;i++){
		board[i] = (int *)malloc((boardSize+2) * sizeof(int));      
	}
	
	// intitalizes all board elements to 0 with a -1 border (-1 is out of bounds)
	for(int i=0;i<boardSize+2;i++){  // top row -1
		board[0][i] = -1;
	}
	for(int i=1;i<boardSize+1;i++){  // middle rows -1 0*n -1
		board[i][0] = -1;
		for(int j=1;j<boardSize+1;j++){
			board[i][j]=0; 
		}
		board[i][boardSize+1] = -1;
	}
	for(int i=0;i<boardSize+2;i++){  // bottom row -1
		board[boardSize+1][i] = -1;
	}
	


	int turn = 1;
	int gameState = 0;
	char* playerName;
	
	while(gameState==0){
		
		printBoard(boardSize,board);
		if(turn==1){
			playerName=player1Name;
		} else {
			playerName=player2Name;
		}
		
		if(mode==0){
			playerMove(boardSize,board,playerName,turn);
			if(turn==1){
				gameState = checkXWin(boardSize,board);
				turn=2;
			}
			else if(turn==2){
				gameState = checkOWin(boardSize,board);
				turn=1;
			}
		} else {
			if(turn==1){
				playerMove(boardSize,board,playerName,turn);
				gameState = checkXWin(boardSize,board);
				turn=2;
			} else {
				computerMove(boardSize,board);
				gameState = checkOWin(boardSize,board);
				turn=1;
			}
		}			
	}
	
}




