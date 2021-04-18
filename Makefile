all : prog
lib = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread
opt = -m32
prog.o = main.o fonction.o timer.o barre.o jeu_matin.o jeu_apremidi.o tuto.o argent.o self.o salle_prof.o action.o depression.o nombre_jour.o save.o

prog : $(prog.o)
	gcc $(opt) -o bin/prog $(prog.o) $(lib)

main.o : main.c
	gcc $(opt) -o main.o -c main.c $(lib) 

fonction.o : fonction.c
	gcc $(opt) -o fonction.o -c fonction.c $(lib)

timer.o : timer.c
	gcc $(opt) -o timer.o -c timer.c $(lib)

barre.o : barre.c
	gcc $(opt) -o barre.o -c barre.c $(lib)

jeu_matin.o : jeu_matin.c
	gcc $(opt) -o jeu_matin.o -c jeu_matin.c $(lib)

jeu_apremidi.o : jeu_apremidi.c
	gcc $(opt) -o jeu_apremidi.o -c jeu_apremidi.c $(lib)

tuto.o : tuto.c
	gcc $(opt) -o tuto.o -c tuto.c $(lib)

argent.o : argent.c
	gcc $(opt) -o argent.o -c argent.c $(lib)

self.o : self.c
	gcc $(opt) -o self.o -c self.c $(lib)

salle_prof.o : salle_prof.c
	gcc $(opt) -o salle_prof.o -c salle_prof.c $(lib)

action.o : action.c
	gcc $(opt) -o action.o -c action.c $(lib)

depression.o : depression.c
	gcc $(opt) -o depression.o -c depression.c $(lib)

nombre_jour.o : nombre_jour.c
	gcc $(opt) -o nombre_jour.o -c nombre_jour.c $(lib)

save.o : save.c
	gcc $(opt) -o save.o -c save.c

clean : 
	rm *.o