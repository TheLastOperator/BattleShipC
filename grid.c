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
