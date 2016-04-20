battleship : main.o grid.o ships.o display.o ai.o
	gcc main.o grid.o ships.o display.o ai.o -o battleship
main.o : main.c
	gcc -c main.c
grid.o : grid.c
	gcc -c grid.c
ships.o : ships.c
	gcc -c ships.c
display.o : display.c
	gcc -c display.c
ai.o : ai.c
	gcc -c ai.c
run : battleship
	./battleship
clear :
	rm *.o
	rm battleship
