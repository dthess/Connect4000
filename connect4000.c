#include "stdio.h"
#include "stdlib.h"

#include "connect4000.h"

/*
 * main method handles the different menu choices
 */
int main(){

	while(1){

		printLines();
		int menuChoice = menu();

		switch(menuChoice){

		case 1:
			printLines();
			playGame(0); // player vs. player
			break;

		case 2:
			printLines();
			playGame(1); // player vs. computer
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
