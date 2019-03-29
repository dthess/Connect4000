#include "stdlib.h"

/*
 * uses a series of steps to determine the next best move for the computer and moves there
 *
 * @param size - board size
 * @param board[size] - 2d board array
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
			winningMove = checkWin(size,board,0,2); // check if its a winning move
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
			winningMove = checkWin(size,board,0,1); // check if its a winning move
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
		if(possibleMoves[i]!=-1)
			for(j=1;j<4;j++) // cycle offset values 1 through 3
				if(possibleMoves[i+j]!=-1){
					temp = board[possibleMoves[i]][i];
					temp2 = board[possibleMoves[i+j]][i+j];
					board[possibleMoves[i]][i] = 2;
					board[possibleMoves[i+j]][i+j] = 2;
					winningMove = checkWin(size,board,0,2); // check if its a winning pair of moves
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
		if(possibleMoves[i]!=-1)
			for(j=1;j<4;j++) // cycle values 1 through 3
				if(possibleMoves[j]!=-1){
					temp = board[possibleMoves[i]][i];
					temp2 = board[possibleMoves[i+j]][i+j];
					board[possibleMoves[i]][i] = 1;
					board[possibleMoves[i+j]][i+j] = 1;
					winningMove = checkWin(size,board,0,1); // check if its a winning pair of moves
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

	// STEP 7: just look for any X to play next to (only used on first turn)
	for(i=1;i<size-1;i++){
		if(board[size-1][i]==1){
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

	// FAILSAFE: no best move could be found, move randomly (will probably never happen)
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

