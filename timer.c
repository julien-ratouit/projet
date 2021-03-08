#include <stdio.h>
#include <stdlib.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"

//Le Timer
typedef struct Timer_s{

    //Initialise les variables-----------------------------------------
    //Tick du lancé du timer
    int tick_debut;
    //Tick du début de la pause (Pour sauvegarder le temps depuis le début de la pause)
    int tick_pause;
    //Status du timer
    bool pause;
    bool start;
 
    //Initialise les fonctions------------------------------------------



    //Les différentes actions du timer
    void (*debut)(struct Timer_s *);
    void (*stop)(struct Timer_s *);
    void (*pause)(struct Timer_s *);
    void (*unpause)(struct Timer_s *);
    //Récupère les millisecondes depuis le lancé du timer
    // ou peux aussi récuperer les millisecondes depuis le début de la pause
    int (*get_ticks)(struct Timer_s *);
    //Fonctions de vérification du status du timer
    bool (*is_started)(struct Timer_s *);
    bool (*is_paused)(struct Timer_s *);
};Timer_t


//Initialise le timer
void timer_init(Timer_t * Timer){

    //Création de l'espace du timer
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

}


//Démarre le timer et initialise le début du timer 
//(A utiliser 1 fois ! Pour enlever la pause faire unpause)
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
            return SDL_GetTicks() - Timer->Tick_pause;

        }
        else{

            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - Timer->Tick_debut;

        }
    }
    //Si le timer n'est pas en marche
    return 0;
}

void timer_pause(Timer_t * Timer){

    //Si le timer est en marche et pas encore en pause
    if(( Timer->start == true ) && ( Timer->paused == false )){

        //On met en pause le timer
        paused = true;
 
        //On calcul le pausedTicks
        Timer->Tick_pause = SDL_GetTicks() - Timer->Tick_debut;
    }
}

void timer_unpause(Timer_t * Timer){

    //Si le timer est en pause
    if( Timer->paused == true )
    {
        //on enlève la pause du timer
        Timer->paused = false;
 
        //On remet à zero le startTicks
        Timer->Tick_debut = SDL_GetTicks() - Timer->Tick_pause;
 
        //Remise à zero du pausedTicks
        Timer->Tick_pause = 0;
    }
}

bool timer_is_started(Timer_t Timer){

    return Timer->start

}

bool timer_is_paused(){

    return Timer->paused;

}

int main(){

    Timer_t myTimer;
    init_timer(&myTimer);
 
    
}