#include "display.h"
#include <stdio.h>

void displayInfoBox(char* s) {
	//80*24
	int i;
	int slength;
	for(slength=0; s[slength]!='\0'; slength++);
	printf("\033[%i;%iH", 8, 2);
	printf("╔═");
	for (i = 0; i < slength; i++) {
		printf("═");
	}
	printf("═╗");
	printf("\033[%i;%iH", 9, 2);
	printf("║ %s ║", s);
	printf("\033[%i;%iH", 10, 2);
	printf("╚═");
	for (i = 0; i < slength; i++) {
		printf("═");
	}
	printf("═╝");
}

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
			//printf("\e[1;37m");
			break;
	}
}

void displayDoubleGrid(Grid tab1, Grid tab2, Grid tab3, Ship *ships, int selectedX, int selectedY, int mode, int shipSelector, char dir)
{
	int i, j;

	//printf("\e[1m");

	printf("    ");

	for (j = 0; j < _GRIDSIZE_; ++j)
	{
		printf(" %c", j + 65);
	}

	printf(" ┃");

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
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)==1?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			else if(dir == 'v' && shipSelector != -1 && mode == 0 && i >= selectedY && i < selectedY + ships[shipSelector].shipLength && j == selectedX) {
				isSelected = 1;
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)==1?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
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
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)==1?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			printf(" ");
			if(j == 0 && tab1[i][j]=='~') {
				echoFormatedChar('~');
			}
			else if(tab1[i][j]!='~'){
				echoFormatedChar(tab1[i][j]);
			}
			if(isSelected) {
				isShipOverlapping(tab1, ships[shipSelector], selectedX, selectedY, dir)==1?printf("\e[41m\e[30m"):printf("\e[47m\e[30m");
			}
			if (tab3[i][j] == 'x') {
				printf("\e[41m\e[37m");
			}
			if (tab3[i][j] == 'o') {
				printf("\e[47m\e[30m");
			}
			printf("%c", tab1[i][j]);
		}
		echoFormatedChar('~');
		printf(" ");
		echoFormatedChar(' ');
		printf("\e[1;37m┃");
		echoFormatedChar('~');
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			printf("\e[1;37m");
			if(j == 0) {
				echoFormatedChar('~');
			}
			else if(tab2[i][j]=='~' && tab2[i][j-1]=='~') {
				echoFormatedChar('~');
			}
			else if(tab2[i][j]=='x' && tab2[i][j-1]=='x') {
				printf("\e[41m\e[37m");
			}
			else if(tab2[i][j]=='o' && tab2[i][j-1]=='o') {
				printf("\e[40m\e[30m");
			}
			else if (tab2[i][j-1]!=tab2[i][j] && tab2[i][j]!='~' && tab2[i][j-1]!='~') {
				printf("\e[40m\e[30m");
			}
			else {
				echoFormatedChar('~');
			}
			printf(" ");
			if(j == 0 && tab2[i][j]=='~') {
				echoFormatedChar('~');
			}
			else if(tab2[i][j]!='~'){
				echoFormatedChar(tab2[i][j]);
			}
			if(j == selectedX && i == selectedY && mode == 1) {
				printf("\e[47m\e[30m");
			}
			if (tab2[i][j] == 'x') {
				printf("\e[41m\e[37m");
			}
			if (tab2[i][j] == 'o') {
				printf("\e[40m\e[30m");
			}
			printf("%c", tab2[i][j]);
		}
		echoFormatedChar('~');
		printf("\e[1;37m ");
		echoFormatedChar(' ');
		printf("  ");

		if(shipSelector == i)printf(" > ");
		else printf("   ");
		if(i < _NBSHIPS_) printf("[%c] (%i) = %s", ships[i].shipChar, ships[i].shipLength, ships[i].shipName);
		printf("\e[1;37m\n");
	}
	printf("\e[49m");
}
