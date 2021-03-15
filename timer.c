#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"
#include "timer.h"




//Démarre le timer 
//Pour enlever la pause faire unpause
void timer_debut(Timer_t * Timer){

    //On demarre le timer
    Timer->start = true;
    //On enlève la pause du timer
    Timer->paused = false;
    //On récupére le temps courant
    Timer->tick_debut = SDL_GetTicks();
}

//On stoppe définitivement le timer pour pouvoir le réutiliser plus tard
void timer_stop(Timer_t * Timer){

    //On stoppe le timer
    Timer->start = false;
    //On stoppe la pause
    Timer->paused = false;

}

int timer_get_ticks(Timer_t * Timer){
    //Si le timer est en marche
    if( Timer->start == true ){

        //Si le timer est en pause
        if( Timer->paused == true ){

            //On retourne le nombre de ticks quand le timer a été mis en pause
            return SDL_GetTicks() - Timer->tick_pause;

        }
        else{

            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - Timer->tick_debut;

        }
    }
    //Si le timer n'est pas en marche
    return 0;
}

void timer_pause(Timer_t * Timer){

    //Si le timer est en marche et pas encore en pause
    if(( Timer->start == true ) && ( Timer->paused == false )){

        //On met en pause le timer
        Timer->paused = true;
 
        //On calcul le pausedTicks
        Timer->tick_pause = SDL_GetTicks() - Timer->tick_debut;
        
    }
}

void timer_unpause(Timer_t * Timer){

    //Si le timer est en pause
    if( Timer->paused == true ){
        //on enlève la pause du timer
        Timer->paused = false;
 
        //On remet à zero le startTicks
        Timer->tick_debut = SDL_GetTicks() - Timer->tick_pause;
 
        //Remise à zero du pausedTicks
        Timer->tick_pause = 0;
    }
}

//Renvoie vrai si le timer a commencer 
bool timer_is_started(Timer_t * Timer){

    return (Timer->start);

}

//Renvoie vrai si le timer est en pause
bool timer_is_paused(Timer_t * Timer){

    return (Timer->paused);

}

//Initialise le timer
Timer_t * timer_init(){

    //Création de l'espace du timer    
	Timer_t * Timer;
	Timer = malloc(sizeof(Timer_t));

    //Initialisation de valeur de base
    Timer->start = false;
    Timer->paused = false;
    Timer->tick_debut = 0;
    Timer->tick_pause = 0;

    //Initialisation des fonctions a utiliser
    Timer->debut = timer_debut;
    Timer->stop = timer_stop;
    Timer->pause = timer_pause;
    Timer->unpause = timer_unpause;
    Timer->get_ticks = timer_get_ticks;
    Timer->is_started = timer_is_started;
    Timer->is_paused = timer_is_paused;
	
	return Timer;
}
/*
int main(int arv, char *argc[]){

    SDL_Init(SDL_INIT_VIDEO);

    //Initialisation du timer test

    Timer_t * test;
    test = timer_init();
    
    //Lance le timer
    test->debut(test);
    printf("%i\n",test->get_ticks(test));
    printf("A commence : %i\n", test->is_started(test));
    printf("En pause : %i \n", test->is_paused(test));

    SDL_Delay(1000);
    //Mets en pause le timer
    printf("%i\n",test->get_ticks(test));
    test->pause(test);
    printf("A commence : %i\n", test->is_started(test));
    printf("En pause : %i \n", test->is_paused(test));
    SDL_Delay(1000);

    //Depause le timer
    test->unpause(test);
    printf("%i\n",test->get_ticks(test)); //N'a pas bouger par rapport au dernier affichage
    printf("A commence : %i\n", test->is_started(test));
    printf("En pause : %i \n", test->is_paused(test));

    //Arrete completement le timer
    test->stop(test);
    printf("%i\n",test->get_ticks(test)); //Censer renvoyer 0
    printf("A commence : %i\n", test->is_started(test));
    printf("En pause : %i \n", test->is_paused(test));
}
*/