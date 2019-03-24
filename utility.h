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
 * buffers area between bottom of screen and display
 */
 void buffer(){
		for(int i=0;i<24;i++){
			printf("\n");
		}
 }
 
 /*
  * for debug
  */
 void printArray(int size, int* arr[size+2]){
	 for(int i=0;i<size+2;i++){
		 for(int j=0;j<size+2;j++){
			 printf("%d ",arr[i][j]);
		 } printf("\n");
	 }
 }
 
 /*
  * 
  */
 void printBoard(int size, int* arr[size+2]){
	 
 	printLines();
 	int columnLetter = 65;
 	int rowNumber = 1;
 	
 	printf("\t\t");
 	for(int i=0;i<size;i++){  
 		printf("%c     ",columnLetter);   // prints column letters
		columnLetter++;
 	} printf("\n");
 	
 	for(int i=1;i<size+1;i++){
 		
 		
 		printf("\t     _");
 		for(int j=0;j<size;j++){   // Horizontal line over numbers
 			printf("______");
 		}
 		
 		printf("\n\t     |");
 		for(int j=0;j<size;j++){   // Vertical lines above number, below horizontal line
 			printf("     |");
 		}

 		if(rowNumber<10){
 			printf("\n\t  %d  |  ",rowNumber);	 // prints row numbers
 		} else {
 			printf("\n\t %d  |  ",rowNumber);   // one less space if rowNumber has extra digit
 		}
 		rowNumber++;
 		
 		//prints board values
 		for(int j=1;j<size+1;j++){        
 			if(arr[i][j]==0) printf(" ");     // empty space
 			if(arr[i][j]==1) printf("X");     // player 1 space
 			if(arr[i][j]==2) printf("O");     // player 2 space
 			printf("  |  ");               // divider 
 		} 
 		printf("\n\t     |");
 		for(int j=0;j<size;j++){ // Vertical lines below number, above horizontal line
 			printf("     |");
 		}
 		printf("\n");
 	}
 	printf("\t     _");
 	for(int i=0;i<size;i++){
 		printf("______");
 	}
 }