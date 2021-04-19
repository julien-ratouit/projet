/**
* \file timer.c
* \brief Ce fichier permet de répertorier toutes les actions qu'un timer peut faire.
* \details On utilise ce programme pour calculer depuis combien de temps la partie ou une action est lancé.
* \author Vallet Guillaume
*/

#include "../include/commun.h"
#include "../include/timer.h"




/**
* \brief Démarre le timer
* 
* \details Initialise les valeurs du timer pour lancer. 
* \param Le timer a lancer
*  
*/
void timer_debut(Timer_t * Timer)
{

    //On demarre le timer
    Timer->start = true;
    //On enlève la pause du timer
    Timer->paused = false;
    //On récupére le temps courant
    Timer->tick_debut = SDL_GetTicks();
}

/**
* \brief Arrête définitivement le timer
* 
* \details Mets le timer en arrêt en mettant ses bool en false 
* \param Le timer a stoppé
*  
*/
void timer_stop(Timer_t * Timer)
{

    //On stoppe le timer
    Timer->start = false;
    //On stoppe la pause
    Timer->paused = false;

}

/**
* \brief Donne le temps depuis lequel le timer a démarrer
* 
* \details Si le timer est en pause, ne donne rien.
* \param Le timer a observer
* \return Le temps depuis lequel le timer a commencé en entier
*  
*/
int timer_get_ticks(Timer_t * Timer)
{
    //Si le timer est en marche
    if( Timer->start == true )
    {

        //Si le timer est en pause
        if( Timer->paused == false )
        {
            
            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - Timer->tick_debut;

        }
    }
    //Si le timer n'est pas en marche
    return 0;
}

/**
* \brief Mets le timer en pause
* 
* \details Initialise le tick_pause du timer au tick du lancement de la fonction pour savoir quand le timer a été mis en pause 
* \param Le timer a pauser
*  
*/
void timer_pause(Timer_t * Timer)
{

    //Si le timer est en marche et pas encore en pause
    if(( Timer->start == true ) && ( Timer->paused == false ))
    {

        //On met en pause le timer
        Timer->paused = true;
 
        //On calcul le pausedTicks
        Timer->tick_pause = SDL_GetTicks() - Timer->tick_debut;
        
    }
}

/**
* \brief Dépause le timer
* 
* \details Dépause le timer en enlevant l'état de pause et en remettant le tick_debut a une valeur qui permettent de redonner le même temps avant la pause 
* \param Le timer a dépauser
*  
*/
void timer_unpause(Timer_t * Timer)
{

    //Si le timer est en pause
    if( Timer->paused == true )
    {
        //on enlève la pause du timer
        Timer->paused = false;
 
        //On remet à zero le startTicks
        Timer->tick_debut = SDL_GetTicks() - Timer->tick_pause;
 
        //Remise à zero du pausedTicks
        Timer->tick_pause = 0;
    }
}

/**
* \brief Regarde si le timer a démarrer
* 
* \details Donne l'état du timer. 
* \param Le timer a observer
* \return Un booléen qui dit si le timer est lancer.
*  
*/
bool timer_is_started(Timer_t * Timer)
{

    return (Timer->start);

}

/**
* \brief Regarde si le timer est en pause
* 
* \details Donne l'état du timer. 
* \param Le timer a observer
* \return Un booléen qui dit si le timer est en pause.
*  
*/
bool timer_is_paused(Timer_t * Timer)
{

    return (Timer->paused);

}

/**
* \brief Initialise le timer
* 
* \details Fait un malloc et initialise tout les paramètres du timer pour qu'il soit opérationelle 
* \param Aucun
* \return Un pointeur sur timer_t pour pouvoir ensuite affecter ce pointeur a une variable de type timer_t *
*  
*/
Timer_t * timer_init()
{

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
int main(int arv, char *argc[])
{

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