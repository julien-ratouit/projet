all : prog
lib = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
opt = -m32
prog.o = main.o fonction.o jour.o timer.o barre.o lancement_jeu.o tuto.o

prog : $(prog.o)
	gcc $(opt) -o bin/prog $(prog.o) $(lib)

main.o : main.c
	gcc $(opt) -o main.o -c main.c $(lib) 

fonction.o : fonction.c
	gcc $(opt) -o fonction.o -c fonction.c $(lib)

jour.o : jour.c
	gcc $(opt) -o jour.o -c jour.c $(lib)

timer.o : timer.c
	gcc $(opt) -o timer.o -c timer.c $(lib)

barre.o : barre.c
	gcc $(opt) -o barre.o -c barre.c $(lib)

lancement_jeu.o : lancement_jeu.c
	gcc $(opt) -o lancement_jeu.o -c lancement_jeu.c $(lib)

tuto.o : tuto.c
	gcc $(opt) -o tuto.o -c tuto.c $(lib)
clean : 
	rm *.o