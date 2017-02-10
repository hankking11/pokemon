game100:	game.o scanner.o olist.o io.o logic.o
	gcc game.o scanner.o olist.o io.o logic.o -o game100
game.o:	game.c game.h io.h logic.h olist.h
	gcc -Wall -g -c game.c
scanner.o:	scanner.c scanner.h
	gcc -Wall -g -c scanner.c
olist.o:	olist.c olist.h game.h
	gcc -Wall -g -c olist.c
io.o:	io.c game.h scanner.h logic.h io.h
	gcc -Wall -g -c io.c
logic.o:	logic.c game.h scanner.h logic.h io.h
	gcc -Wall -g -c logic.c
clean:
	rm logic.o io.o olist.o scanner.o game.o game100
run:	game100
	game100
puzzle:	game100
	cat PUZZLE | game100
