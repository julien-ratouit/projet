all : prog
lib = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

prog : main.o fonction.o jour.o timer.o barre.o
	gcc -o bin/prog main.o fonction.o jour.o timer.c $(lib)

main.o : main.c
	gcc -o main.o -c main.c $(lib) 

fonction.o : fonction.c
	gcc -o fonction.o -c fonction.c $(lib)

jour.o : jour.c
	gcc -o jour.o -c jour.c $(lib)

timer.o : timer.c
	gcc -o timer.o -c timer.c $(lib)

barre.o : barre.c
	gcc -o barre.o -c barre.c $(lib)

clean : 
	rm *.o