#include "stdio.h"
#include "stdlib.h"

/*
 * 
 */
int checkOWin(int size, int* arr[size]){  // returns 0 for no winner, 1 for win
	return 0;
}

/*
 * 
 */
int checkXWin(int size, int* arr[size]){  // returns 0 for no winner, 1 for win
	return 0;
}

/*
 * 
 */
void playerMove(int size, int* arr[size],char* name, int turn){  // turn 1 for player1, 2 for player2
	
	printf("\n\n\t\t%s's turn",name);
	
	
	char column;
	int columnNum;
	int row;
	
	int validChoice=0;
	while(validChoice==0){
		
		printf("\n\n\t\tENTER COLUMN LETTER (UPPERCASE)\n\t\t");
		int validColumn = 0;
		while(validColumn==0){
			
			scanf("\n%c",&column);
			columnNum = (int)column;
			if(column>64 && column<=64+size){
				validColumn=1;
			} else {
				printf("\n\n\t\tInvalid column letter, try again");
			}
		}
		columnNum-=64;

		printf("\n\n\t\tENTER ROW NUMBER\n\t\t");
		
		int validRow = 0;
		while(validRow==0){
			scanf("\n%d",&row);
			if(row>0 && row<=size){
				validRow=1;
			} else {
				printf("\n\n\t\tInvalid row number, try again\n\n\t\t");
			}
		}
		
		if(arr[row][columnNum]==0){
			validChoice=1;
		} else {
			printf("\n\n\t\tSpace already taken, try again\n\n\t\t");
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
	
}