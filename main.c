#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "grid.h"
#include "ships.h"
#include "display.h"

void displayGameTitle()
{
	printf("\e[1;37m");
	printf("  ____        _   _   _       _____ _     _           \n");
	printf(" |  _ \\      | | | | | |     / ____| |   (_)          \n");
	printf(" | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __  ___ \n");
	printf(" |  _ < / _` | __| __| |/ _ \\__ _ \\| '_ \\| | '_ \\/ __|\n");
	printf(" | |_) | (_| | |_| |_| |  __/____) | | | | | |_) \\__ \\\n");
	printf(" |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/|___/\n");
	printf("                                           | |        \n");
	printf("                                           |_|        \n");
	printf("\n");
}

void placeShip(Grid mapPlayer, Ship ship, int cursorX, int cursorY, char dir) {
	if(!isShipInGrid(mapPlayer, ship)) {
		if(canShipFitInGrid(mapPlayer, ship, cursorX, cursorY, dir)) {
			if (!isShipOverlapping(mapPlayer, ship, cursorX, cursorY, dir)) {
				placeShipInGrid(mapPlayer, ship, cursorX, cursorY, dir);
			}
			else {
				printf("Ship is overlapping\n");
				getchar();
			}
		}
		else {
			printf("Ship out of bound\n");
			getchar();
		}
	}
	else {
		printf("Ship allready placed\n");
		getchar();
	}
}

void getPlayerCommand()
{
	printf("\n Quels sont vos instructions ?   \n > ");
	getchar();
}

int main(int argc, char const *argv[])
{

	// Déclaration des grilles
	Grid mapPlayer;
	Grid mapComputer;
	Grid tabPlayer;
	Grid tabComputer;

	// Remplissage des grilles
	fillWithWater(mapPlayer);
	fillWithWater(tabPlayer);

	// Création du curseur de placement
	int cursorX = 0;
	int cursorY = 0;

	char dir = 'h';
	int mode = 0;
	int shipSelector = -1;

	Ship ships[5];
	ships[0].shipName = "Porte-avion";
	ships[0].shipChar = 'p';
	ships[0].shipLength = 5;
	ships[1].shipName = "Cuirassé";
	ships[1].shipChar = 'c';
	ships[1].shipLength = 4;
	ships[2].shipName = "Frégate";
	ships[2].shipChar = 'f';
	ships[2].shipLength = 3;
	ships[3].shipName = "Sous-marin";
	ships[3].shipChar = 's';
	ships[3].shipLength = 3;
	ships[4].shipName = "Démineur";
	ships[4].shipChar = 'd';
	ships[4].shipLength = 2;

	struct termios old_tio, new_tio;
	unsigned char c;

	/* get the terminal settings for stdin */
	tcgetattr(STDIN_FILENO,&old_tio);

	/* we want to keep the old setting to restore them a the end */
	new_tio=old_tio;

	/* disable canonical mode (buffered i/o) and local echo */
	new_tio.c_lflag &=(~ICANON & ~ECHO);

	/* set the new settings immediately */
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

	// Game loop
	do {
		//Clear du terminal
		printf("\033[2J\033[1;1H");
		// Affichage du titre en ascii art
		displayGameTitle();
		// Affichage des grilles
		displayDoubleGrid(mapPlayer, tabPlayer, ships, cursorX, cursorY, mode, shipSelector, dir);
		// Play !

		c=getchar();

		switch (c) {
			case '8':
				if(cursorY > 0)cursorY--;
				break;
			case '2':
				if(canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX, cursorY+1, dir))cursorY++;
				break;
			case '4':
				if(cursorX > 0)cursorX--;
				break;
			case '6':
				if(canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX+1, cursorY, dir))cursorX++;
				break;
			case '9':
				if(shipSelector > 0)shipSelector--;
				while (!canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX, cursorY, dir)) {
					if(dir=='h') {
						cursorX--;
					}
					else {
						cursorY--;
					}
				}
				break;
			case '3':
				if(shipSelector < 4)shipSelector++;
				break;
			case '7':
			  placeShip(mapPlayer, ships[shipSelector], cursorX, cursorY, dir);
				break;
			case '1':
				dir = dir == 'h' ? 'v' : 'h';
				while (!canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX, cursorY, dir)) {
					if(dir=='h') {
						cursorX--;
					}
					else {
						cursorY--;
					}
				}
				break;
			case 's':
				mode = mode==1?0:1;
				break;
		}
	} while(c!='q');

	//Clear du terminal
	printf("\033[2J\033[1;1H");
	printf("Thanks for playing !\n");

	/* restore the former settings */
	tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

	//int continuePlaying = 1;
	//while(continuePlaying) {
		/*
		Ship ship = {'s', 3};
		printf("%i\n", isShipInGrid(mapPlayer, ship));
		//Player turn
		getPlayerCommand();
		//Computer turn*/
	//}
	return 0;
}
