#include "grid.h"

void fillWithWater(char tab[_GRIDSIZE_][_GRIDSIZE_])
{
	int i, j;

	for (i = 0; i < _GRIDSIZE_; ++i)
	{
		for (j = 0; j < _GRIDSIZE_; ++j)
		{
			tab[i][j] = '~';
		}
	}
}

void shotTarget(Grid tab, Grid map, int x, int y) {
	if(map[y][x] != '~') {
		tab[y][x] = 'x';
	}
	else {
		tab[y][x] = 'o';
	}
}
