#include "ships.h"

int isShipInGrid(Grid tab, Ship ship)
{
	int i, j;
	for (i = 0; i < _GRIDSIZE_; ++i)
	{
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			if(tab[i][j] == ship.shipChar) return 1;
		}
	}
	return 0;
}

int canShipFitInGrid(Grid tab, Ship ship, int x, int y, char dir)
{
	if(dir == 'h') {
		if((x + ship.shipLength <= _GRIDSIZE_) && y < _GRIDSIZE_ && (x >= 0)) {
			return 1;
		}
	}
	else if(dir == 'v') {
		if((y + ship.shipLength <= _GRIDSIZE_) && x < _GRIDSIZE_ && (y >= 0)) {
			return 1;
		}
	}
	return 0;
}

int isShipOverlapping(Grid tab, Ship ship, int x, int y, char dir)
{
	int i;
	if(dir == 'h') {
		for (i = x; i < x + ship.shipLength; i++) {
			if (tab[y][i] != '~') {
				if (tab[y][i] == ship.shipChar) {
					return 2;
				}
				return 1;
			}
		}
	}
	else if(dir == 'v') {
		for (i = y; i < y + ship.shipLength; i++) {
			if (tab[i][x] != '~') {
				if (tab[i][x] == ship.shipChar) {
					return 2;
				}
				return 1;
			}
		}
	}
	return 0;
}

void placeShipInGrid(Grid tab, Ship ship, int x, int y, char dir)
{
	int i;
	for (i = 0; i < ship.shipLength; ++i)
	{
		tab[dir == 'v' ? y + i : y][dir == 'h' ? x + i : x] = ship.shipChar;
	}
}

void removeShipFromGrid(Grid tab, Ship ship, int x, int y, char dir) {
	int i, j;
	for (i = 0; i < _GRIDSIZE_; ++i)
	{
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			if(tab[i][j] == ship.shipChar) tab[i][j] = '~';
		}
	}
}
