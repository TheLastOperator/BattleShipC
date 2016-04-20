#ifndef H_DISPLAY
#define H_DISPLAY

#include "grid.h"
#include "ships.h"

void displayDoubleGrid(Grid tab1, Grid tab2, Grid tab3, Ship *ships, int selectedX, int selectedY, int mode, int selectedZ, char dir);
void echoFormatedChar(char c);
void displayInfoBox(char* s);

#endif
