all : prog
lib = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

prog : main.o fonction.o jour.o timer.o barre.o
	gcc -m32 -o bin/prog main.o fonction.o jour.o timer.c barre.c$(lib)

main.o : main.c
	gcc -m32 -o main.o -c main.c $(lib) 

fonction.o : fonction.c
	gcc -m32 -o fonction.o -c fonction.c $(lib)

jour.o : jour.c
	gcc -m32 -o jour.o -c jour.c $(lib)

timer.o : timer.c
	gcc -m32 -o timer.o -c timer.c $(lib)

barre.o : barre.c
	gcc -m32 -o barre.o -c barre.c $(lib)

clean : 
	rm *.o