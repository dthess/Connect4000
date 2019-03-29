#include "stdlib.h"

/*
 * determines if the game has been won by the player indicated
 * checks horizontally, vertically, diagonally (\), and then diagonally again (/)
 *
 * @param size - board size
 * @param board[size] - 2d board array
 * @param state - current gameState
 * @param player - player who needs to be checked
 *
 * @returns - state when no winner, 1 or 2 if there is a winner (depending on who won)
 */
int checkWin(int size, int* board[size], int state, int player){

	//create an array of possible moves
	int possibleMoves[size]; // stores row index for each column
	for (int i=0;i<size;i++){
		for (int j=size-1;j>=0;j--){
			if(board[j][i]==0){
				possibleMoves[i] = j; // open space found
				break;
			} else if(j==0&&board[j][i]!=0){
				possibleMoves[i] = -1; // column is full
			}
		}
	}

	//check horizontal
	for(int k=0;k<size;k++){
		int i=possibleMoves[k]+1;
		if(possibleMoves[k]!=-1&&i<size)
			for(int j=0;j<size-3;j++)
				if(board[i][j] == player)
					if(board[i][j+1] == player) // 1 in a row
						if(board[i][j+2] == player) // 2 in a row
							if(board[i][j+3] == player) // 3 in a row
								state = player;
	}

	//check vertical
	for(int i=0;i<size;i++){
		if(board[size-4][i]!=0||possibleMoves[i]!=-1)
			for(int j=0;j<size-3;j++){
				if(board[j][i] == player)
					if(board[j+1][i] == player) // 1 in a row
						if(board[j+2][i] == player) // 2 in a row
							if(board[j+3][i] == player) // 3 in a row
								state = player;
			}
	}

	//check diagonal '\'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
		if(i<size-3&&i!=-1)
			for(int j=0;j<size-3;j++)
				if(board[i][j] == player)
					if(board[i+1][j+1] == player) // 1 in a row
						if(board[i+2][j+2] == player) // 2 in a row
							if(board[i+3][j+3] == player) // 3 in a row
								state = player;
	}

	//check diagonal '/'
	for(int k=0;k<size-3;k++){
		int i=possibleMoves[k]+1;
		if(i<size-3&&i!=-1)
			for(int j=3;j<size;j++)
				if(board[i][j] == player)
					if(board[i+1][j-1] == player) // 1 in a row
						if(board[i+2][j-2] == player) // 2 in a row
							if(board[i+3][j-3] == player) // 3 in a row
								state = player;
	}

	return state;
}

/*
 * determines if game is over due to tie (all spaces filled and no winner)
 *
 * @param size - board size
 * @param board[size] - 2d board array
 * @param state - current gameState
 *
 * @returns state value when no tie, 3 for a tie
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

