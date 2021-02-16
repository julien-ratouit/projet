all : prog
lib = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

prog : aff_fenetre.o fonction.o
	gcc -o prog aff_fenetre.o fonction.o $(lib)

aff_fenetre.o : aff_fenetre.c
	gcc -o aff_fenetre.o -c aff_fenetre.c $(lib)

fonction.o : fonction.c
	gcc -o fonction.o -c fonction.c $(lib)

clean : 
	rm *.o