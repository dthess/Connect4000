#include "stdio.h"
#include "stdlib.h"

#include "playGame.h"

int main(){ 

	while(1){

		printLines();
		int menuChoice = 1;
		switch(menuChoice){

		case 1:		
			playGame(0);
			break;

		case 2:	
			playGame(1);
			break;

		case 3:
			displayRules();
			break;

		case 4:           //exit
			return 0;
		}

	}

	return 0;
}