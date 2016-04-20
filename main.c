#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "grid.h"
#include "ships.h"
#include "display.h"
#include "ai.h"

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
	printf("\n\n\n");
}

void placeShip(Grid mapPlayer, Ship ship, int cursorX, int cursorY, char dir) {
	if(canShipFitInGrid(mapPlayer, ship, cursorX, cursorY, dir)) {
		if (isShipOverlapping(mapPlayer, ship, cursorX, cursorY, dir) != 1) {
			if(isShipInGrid(mapPlayer, ship)) {
				removeShipFromGrid(mapPlayer, ship, cursorX, cursorY, dir);
			}
			placeShipInGrid(mapPlayer, ship, cursorX, cursorY, dir);
		}
		else {
			displayInfoBox("Vous ne pouvez pas placer un bateau ici.");
			getchar();
		}
	}
	else {
		displayInfoBox("Ship out of bound");
		getchar();
	}
}

int main(int argc, char const *argv[])
{
	srand (time (NULL));

	// Déclaration des grilles
	Grid mapPlayer;
	Grid mapComputer;
	Grid tabPlayer;
	Grid tabComputer;

	// Remplissage des grilles
	fillWithWater(mapPlayer);
	fillWithWater(tabPlayer);
	fillWithWater(mapComputer);
	fillWithWater(tabComputer);

	// Création des types de bateaux
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

	// Placement IA
	placeShipsAI(mapComputer, ships);

	// Création du curseur de placement
	int cursorX = 0;
	int cursorY = 0;

	char dir = 'h';
	int mode = 0;
	int shipSelector = 0;

	// Déclaration des structures de gestion du terminal
	struct termios old_tio, new_tio;
	unsigned char c;

	// Récupération de la configuration du terminal pour STDIN
	tcgetattr(STDIN_FILENO,&old_tio);

	// Sauvegarde des la configuration
	new_tio=old_tio;

	// Désactivation de l'echo local
	new_tio.c_lflag &=(~ICANON & ~ECHO);

	// Application des changements
	tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

	// Hide cursor
	printf("\e[?25l");

	// Game loop
	do {
		// Clear du terminal
		printf("\033[2J\033[1;1H");

		// Affichage du titre en ascii art
		displayGameTitle();

		// Affichage des grilles
		displayDoubleGrid(mapPlayer, tabPlayer, tabComputer, ships, cursorX, cursorY, mode, shipSelector, dir);

		if (mode == 0) {
			displayInfoBox("Selectionez vos bateaux avec A et E et placez les avec Z,Q,S,D,R et ESPACE");
		}
		else if (mode == 1) {
			displayInfoBox("Ciblez les bateaux enemis avec Z,Q,S,D et tirez avec ESPACE");
		}

		// Play !

		c=getchar();

		// Phase placement des bateaux
		if (mode == 0) {
			switch (c) {
				case 'z':
					if(cursorY > 0)cursorY--;
					break;
				case 's':
					if(canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX, cursorY+1, dir))cursorY++;
					break;
				case 'q':
					if(cursorX > 0)cursorX--;
					break;
				case 'd':
					if(canShipFitInGrid(mapPlayer, ships[shipSelector], cursorX+1, cursorY, dir))cursorX++;
					break;
				case 'a':
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
				case 'e':
					if(shipSelector < 4)shipSelector++;
					break;
				case ' ':
					placeShip(mapPlayer, ships[shipSelector], cursorX, cursorY, dir);
					break;
				case 'r':
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
				case '\n':
					mode = 1;
					shipSelector = -1;
					break;
			}
		}
		// Phase de jeu
		else {
			switch (c) {
				case 'z':
					if(cursorY > 0)cursorY--;
					break;
				case 's':
					if(cursorY + 1 < _GRIDSIZE_)cursorY++;
					break;
				case 'q':
					if(cursorX > 0)cursorX--;
					break;
				case 'd':
					if(cursorX + 1 < _GRIDSIZE_)cursorX++;
					break;
				case ' ':
					if(tabPlayer[cursorY][cursorX] == '~') {
						// Player turn
						shotTarget(tabPlayer, mapComputer, cursorX, cursorY);
						// Computer turn
						Pos pos = getNextTarget(tabComputer);
						shotTarget(tabComputer, mapPlayer, pos.x, pos.y);
					}
					break;
			}
		}
	} while(c!=27);

	// Clear du terminal
	printf("\033[2J\033[1;1H");

	// Restoration de la configuration du terminal
	tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

	// Show cursor
	printf("\e[?25h");

	return 0;
}
