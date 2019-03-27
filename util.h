#include "stdio.h"
#include "stdlib.h"

int DEFAULT_LINE_SKIP = 50;   // number of lines used to give illusion of cleared screen

/*
 * prints set number of lines to give illusion of cleared screen
 */
void printLines(){  
	for(int i=0;i<DEFAULT_LINE_SKIP;i++){
		printf("\n");
	}
}

/*
 * buffers area between bottom of screen and text
 */
void buffer(){
	for(int i=0;i<24;i++){
		printf("\n");
	}
}

void scoreboard(){
	
}

/*
 * 
 */
void printBoard(int size, int* arr[size]){

	printLines();

	//print column numbers
	int columnNum = 1;
	printf(" ");
	for(int i=0;i<size;i++){ // first row of column number digits
		if(columnNum<100){
			printf("  ");
		} else {
			printf("%d ",columnNum/100%10);   
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // second row of column number digits
		if(columnNum<10){
			printf("  ");
		} else {
			printf("%d ",columnNum/10%10);   
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // third row of column number digits
		printf("%d ",columnNum%10);  
		columnNum++;
	} printf("\n");

	// vertical line above board	
	for(int i=0;i<size;i++){
		printf("__");
	} printf("_\n");

	for(int i=0;i<size;i++){
		printf("|");	 

		//prints board values
		
		for(int j=0;j<size;j++){        
			if(arr[i][j]==0) printf("_");     // empty space
			if(arr[i][j]==1) printf("X");     // player 1 space
			if(arr[i][j]==2) printf("O");     // player 2 space
			printf("|");               // divider 
		} printf("\n");
	}

	//print column numbers
	columnNum = 1;
	printf(" ");
	for(int i=0;i<size;i++){ // first row of column number digits
		if(columnNum<100){
			printf("  ");
		} else {
			printf("%d ",columnNum/100%10);   
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // second row of column number digits
		if(columnNum<10){
			printf("  ");
		} else {
			printf("%d ",columnNum/10%10);   
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // third row of column number digits
		printf("%d ",columnNum%10);  
		columnNum++;
	} printf("\n");
} 