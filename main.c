#include "stdio.h"
#include "stdlib.h"

int DEFAULT_LINE_SKIP = 4;

void printLines(){
	for(int i=0;i<DEFAULT_LINE_SKIP;i++){
		printf("\n");
	}
}

int menu(){
	//printLines(50);
	int choice=0;
	printf("\tWelcome to Connect 4000\n\n\n\t\t1) Player vs. Player\n\n\t\t"
			"2) Player vs. Computer\n\n\t\t3) Rules\n\n\t\t4) Exit\n\n\n\n\t\tEnter Number: ");
	scanf("\n%d",&choice);
	return choice;
}

void displayRules(){
	printLines();
	printf("\t\tEnter 1 to return to menu\n\n");
	int useless;
	scanf("\n%d",&useless);
}

void printBoard(int size,int* arr[size]){
	printLines();
		
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){ // line 
			printf(".");
		} printf("\n");
		for(int j=0;j<size;j++){ // board values
			printf("%d",arr[i][j]);
		} printf("\n");
	}
	
}

void playGame(int mode){		//mode 0 for pvp, 1 for cpu 

	char player1Name[50];
	char player2Name[50] = "Computer";
	int boardSize=8;
	
	printLines();
	printf("\t\tPlayer 1 enter first name\n\n");
	//scanf("%s",player1Name);
	
	printLines();
	if(mode==0){
		printf("\t\tPlayer 2 enter first name\n\n");
		//scanf("%s",player2Name);
	}
	
	printLines();
	printf("\t\tEnter Y board size for a YxY board: (4 minimum)\n\n");
	//scanf("%d",&boardSize);

	int *board[boardSize];
	for(int i=0;i<boardSize;i++){
		board[i] = (int *)malloc(boardSize * sizeof(int));
	}
	for(int i=0;i<boardSize;i++)
		for(int j=0;j<boardSize;j++)
			board[i][j]=0;
	


	
	//printBoard(boardSize,board);
}




int main(){ while(1){

	printLines();
	int menuChoice = menu();
	switch(menuChoice){
	case 1:		printf("playgame 0");	
		
		playGame(0);
		break;
	case 2:		printf("playgame 1");
		
		playGame(1);
		
		break;
	case 3:		printf("displayrules");
		
		displayRules();
		break;
	case 4:
		return 0;
	}
	
	

} return 0;
}
