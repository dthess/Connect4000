#include "stdlib.h"
#include "string.h"

int DEFAULT_LINE_SKIP = 60;   // number of lines used to clear screen

/*
 * prints a number of lines to clear the screen
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
 * prints the current board array
 *
 * @param size - board size
 * @param board[size] - 2d board array
 */
void printBoard(int size, int* board[size]){

	printLines();

	//print column numbers
	int columnNum = 1;
	printf(" ");
	for(int i=0;i<size;i++){ // first row of column number digits (hundreds)
		if(columnNum<100){
			printf("  ");
		} else {
			printf("%d ",columnNum/100%10);
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // second row of column number digits (tens)
		if(columnNum<10){
			printf("  ");
		} else {
			printf("%d ",columnNum/10%10);
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // third row of column number digits (ones)
		printf("%d ",columnNum%10);
		columnNum++;
	} printf("\n");

	// vertical line above board
	for(int i=0;i<size;i++){
		printf("__");
	} printf("_\n");

	//prints board values with separators
	for(int i=0;i<size;i++){
		printf("|");
		for(int j=0;j<size;j++){
			if(board[i][j]==0) printf("_"); // empty space
			if(board[i][j]==1) printf("X"); // player 1 space
			if(board[i][j]==2) printf("O"); // player 2 space
			printf("|");
		} printf("\n");
	}

	//print column numbers
	columnNum = 1;
	printf(" ");
	for(int i=0;i<size;i++){ // first row of column number digits (hundreds)
		if(columnNum<100){
			printf("  ");
		} else {
			printf("%d ",columnNum/100%10);
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // second row of column number digits (tens)
		if(columnNum<10){
			printf("  ");
		} else {
			printf("%d ",columnNum/10%10);
		}
		columnNum++;
	} printf("\n ");
	columnNum=1;
	for(int i=0;i<size;i++){ // third row of column number digits (ones)
		printf("%d ",columnNum%10);
		columnNum++;
	} printf("\n");
}
