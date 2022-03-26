# *-* Makefile *-*

all: main

main: main.o utils.o board.o players.o
	gcc main.o utils.o board.o players.o -o main

main.o: main.c utils.h players.h board.h
	gcc -c main.c

utils.o: utils.c
	gcc -c utils.c

board.o: board.c
	gcc -c board.c

players.o: players.c utils.h board.h
	gcc -c players.c


clean:
	rm -f *.o main