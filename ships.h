#ifndef H_SHIPS
#define H_SHIPS
#define _NBSHIPS_ 5

#include "grid.h"

typedef struct Ship Ship;
struct Ship
{
	char  shipChar;
	char* shipName;
	int   shipLength;
};

typedef struct Pos Pos;
struct Pos
{
	int x;
	int y;
};

int isShipInGrid(Grid tab, Ship ship);
int canShipFitInGrid(Grid tab, Ship ship, int x, int y, char dir);
int isShipOverlapping(Grid tab, Ship ship, int x, int y, char dir);
void placeShipInGrid(Grid tab, Ship ship, int x, int y, char dir);
void removeShipFromGrid(Grid tab, Ship ship, int x, int y, char dir);

#endif
