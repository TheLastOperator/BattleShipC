#include "display.h"
#include <stdio.h>

void echoFormatedChar(char c)
{
	switch(c)
	{
		case '~': //eau
			printf("\e[44m");
			break;
		case 'p': //porte avion
			printf("\e[40m");
			break;
		case 'c': //cuiracé
			printf("\e[40m");
			break;
		case 'f': //frégate
			printf("\e[40m");
			break;
		case 's': //sous-marin
			printf("\e[40m");
			break;
		case 'd': //démineur
			printf("\e[40m");
			break;
		default:
			printf("\e[49m");
			break;
	}
}

void displayDoubleGrid(Grid tab1, Grid tab2, Ship *ships, int selectedX, int selectedY, int mode, int shipSelector, char dir)
{
	int i, j;

	//printf("\e[1m");

	printf("    ");

	for (j = 0; j < _GRIDSIZE_; ++j)
	{
		printf(" %c", j + 65);
	}

	printf(" |");

	for (j = 0; j < _GRIDSIZE_; ++j)
	{
		printf(" %c", j + 65);
	}

	printf("\n");

	for (i = 0; i < _GRIDSIZE_; ++i)
	{
		echoFormatedChar(' ');
		printf(" %2d ", i);
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			int isSelected = 0;
			if(dir == 'h' && shipSelector != -1 && mode == 0 && j >= selectedX && j < selectedX + ships[shipSelector].shipLength && i == selectedY) {
				isSelected = 1;
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			else if(dir == 'v' && shipSelector != -1 && mode == 0 && i >= selectedY && i < selectedY + ships[shipSelector].shipLength && j == selectedX) {
				isSelected = 1;
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}

			printf("\e[1;37m");
			if(j == 0) {
				echoFormatedChar('~');
			}
			else if(tab1[i][j-1]=='~' || tab1[i][j-1]!=tab1[i][j]) {
				echoFormatedChar('~');
			}
			else {
				echoFormatedChar(tab1[i][j]);
			}
			if(isSelected && selectedX != j) {
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			printf(" ");
			if(j == 0 && tab1[i][j]=='~') {
				echoFormatedChar('~');
			}
			else if(tab1[i][j]!='~'){
				echoFormatedChar(tab1[i][j]);
			}
			if(isSelected) {
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			printf("%c", tab1[i][j]);
		}
		echoFormatedChar('~');
		printf(" ");
		echoFormatedChar(' ');
		printf("\e[1;37m|");
		echoFormatedChar('~');
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			if((j-1) >= 0) {
				if(tab2[i][j] == '~' || tab2[i][j-1] == '~') {
					echoFormatedChar('~');
				}
				else {
					echoFormatedChar(tab2[i][j-1]);
				}
			}
			printf(" ");

			if(mode == 1 && i == selectedY && j == selectedX) {
				printf("\e[47m\e[30m");
			}
			else {
				printf("\e[1;37m");
				echoFormatedChar(tab2[i][j]);
			}
			printf("%c", tab2[i][j]);
		}
		echoFormatedChar('~');
		printf("\e[1;37m ");
		echoFormatedChar(' ');
		printf("  ");

		if(shipSelector == i)printf("\e[0;37m");
		if(i < _NBSHIPS_) printf("[%c] (%i) = %s", ships[i].shipChar, ships[i].shipLength, ships[i].shipName);
		printf("\e[1;37m\n");
	}
	printf("\e[49m");
}
