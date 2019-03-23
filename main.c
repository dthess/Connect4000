#include "stdio.h"

int DEFAULT_LINE_SKIP = 4;

void printLines(){
	for(int i=0;i<DEFAULT_LINE_SKIP;i++){
		printf("\n");
	}
}

int menu(){
	//printLines(50);
	int choice=0;
	printf("\tWelcome to Connect 4000\n\n\n\t\t1) PLayer vs. PLayer\n\n\t\t"
			"2) PLayer vs. Computer\n\n\t\t3) Rules\n\n\t\t4) Exit\n\n\n\n\t\tEnter Number: ");
	scanf("%d",&choice);
	return choice;
}

void displayRules(){
	printLines();
	printf("\t\tEnter 1 to return to menu\n\n");
	int useless;
	scanf("%d",&useless);
}

void playGame(int mode){		//mode 0 for pvp, 1 for cpu 

	char player1Name[50];
	char player2Name[50] = "Computer";
	
	printLines();
	printf("\t\tPlayer 1 enter first name\n\n");
	scanf("%s",player1Name);
	
	printLines();
	if(mode==0){
		printf("\t\tPlayer 2 enter first name\n\n");
		scanf("%s",player2Name);
	}
	
	printLines();
}

void printBoard(int* arr[],int x,int y){
	printLines();
	printf("%c",201);
}


int main(){ while(1){

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
