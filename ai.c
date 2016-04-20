#include "ai.h"

void placeShipsAI(Grid tab, Ship* ships) {
	int i,x,y;
	char dir;
	for (i = 0; i < _NBSHIPS_; i++) {
		do {
			x = rand() % _GRIDSIZE_;
			y = rand() % _GRIDSIZE_;
			dir = (rand() % 2)?'h':'v';
		} while(!canShipFitInGrid(tab,ships[i],x,y,dir) || isShipOverlapping(tab,ships[i],x,y,dir));
		placeShipInGrid(tab, ships[i], x, y, dir);
	}
}

/*
'x' = ship
'o' = no ship
'~' = don't know
*/

Pos getNextTarget(Grid tab) {
	int x,y;
	Pos pos;
	int isFull = 1;
	for (x = 0; x < _GRIDSIZE_; x++) {
		for (y = 0; y < _GRIDSIZE_; y++) {
			if(tab[y][x] == '~')isFull = 0;
			if (tab[y][x] == 'x') {
				//  ~ ? ~
				// [~]x ?
				//  ~ ? ~
				if(x>0 && tab[y][x-1] == '~') {
					pos.x = x-1;
					pos.y = y;
					return pos;
				}
				//  ~[~]~
				//  o x ?
				//  ~ ? ~
				else if(y>0 && tab[y-1][x] == '~') {
					pos.x = x;
					pos.y = y-1;
					return pos;
				}
				//  ~ o ~
				//  o x[~]
				//  ~ ? ~
				else if(x+1<_GRIDSIZE_ && tab[y][x+1] == '~') {
					pos.x = x+1;
					pos.y = y;
					return pos;
				}
				//  ~ o ~
				//  o x 0
				//  ~[?]~
				else if(x+1<_GRIDSIZE_ && tab[y][x+1] == '~') {
					pos.x = x;
					pos.y = y+1;
					return pos;
				}
			}
		}
	}
	do {
		x = rand() % _GRIDSIZE_;
		y = rand() % _GRIDSIZE_;
	} while(tab[y][x] != '~' && !isFull);
	pos.x = x;
	pos.y = y;
	return pos;
}
