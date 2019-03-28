#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "playGame.h"

/*
 * 
 */
void playGame(bool mode){		//mode 0 for pvp, 1 for cpu

	char player1Name[50] = "PLayer 1";
	char player2Name[50] = "Computer";
	int boardSize=26; // max is 118 for my monitor

	printLines();
	printf("\t\tPlayer 1 enter name\n\t\tYou will be X"); buffer();
	scanf("%50s",player1Name);
	getLine();

	printLines();
	if(mode==0){
		printf("\t\tPlayer 2 enter name\n\t\tYou will be O"); buffer();
		scanf("%50s",player2Name);
		getLine();
	}

	printLines();
	bool validSize=0;
	while (validSize==0){
		printf("\n\t\tEnter Y board size length for a YxY board (4 minimum)"); buffer();
		scanf("%d",&boardSize);
		getLine();
		if(boardSize<=3){
			printf("\t\t\nInvalid board size\n\t\tTry again");
		} else if(boardSize>=100){
			int playAnyway = 0;
			printLines();
			printf("\t\tCaution: Board sizes larger than 100 may run off screen (depending on the size of your monitor)\n"
					"\t\tContinue anyway?\n\t\t1) Yes\n\t\t2) Try a different board size\n"); buffer();
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
		int msec=0;
		bool displayTime=0;
		int computerColumn;

		while(gameState==0){

			//printBoard(boardSize,board);

			// display timer if computer just moved
			if(displayTime==1&&turn==1){ 
				printf("\n\t\tComputer moved in column %d in %d.%d seconds\n",computerColumn,msec/1000,msec%1000);
			}

			// determine current player's name
			if(turn==1){
				playerName=player1Name;
			} else {
				playerName=player2Name;
			}

			if(mode==0){ // for player vs player
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
			} else { // for player vs computer
				if(turn==1){
					playerMove(boardSize,board,playerName,turn);	
					gameState = checkTie(boardSize,board,gameState);
					gameState = checkXWin(boardSize,board,gameState);
					turn=2;
					msec=0; // for timing
				} else {
					clock_t start = clock(); // for timing
					computerColumn = computerMove(boardSize,board);
					clock_t stop = clock(); // for timing
					msec = (stop-start)*1000 / CLOCKS_PER_SEC; // for timing
					displayTime=1; // for timing

					gameState = checkTie(boardSize,board,gameState);
					gameState = checkOWin(boardSize,board,gameState);
					turn=1;
				}
			}			
		} // game over


		//printBoard(boardSize,board);


		if(mode==1&& gameState==2){
			printf("\n\t\tComputer moved in column %d in %d.%d seconds\n",computerColumn,msec/1000,msec%1000);
		}

		if(gameState==3){
			printf("\n\n\t\tTIE GAME\n\n\t\tPlay again?\n\n\t\t1) yes\n\n\t\t2) no\n");
		} else {
			printf("\n\n\t\t%s WINS\n\n\t\tPlay again?\n\n\t\t1) yes\n\n\t\t2) no\n",playerName);
		}
		scanf("%d",&keepPlaying);
		getLine();

	}
}

int main(){ 

	while(1){

		printLines();
		int menuChoice = menu();
		switch(menuChoice){

		case 1:
			printLines();
			playGame(0);
			break;

		case 2:	
			printLines();
			playGame(1);
			break;

		case 3:
			printLines();
			displayRules();
			break;

		case 4:           //exit
			return 0;
		}

	}

	return 0;
}
