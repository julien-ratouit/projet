#ifndef _TIMER_H_
#define _TIMER_H_

//Le Timer
typedef struct Timer_s{

    //Initialise les variables-----------------------------------------
    //Tick du lancé du timer
    int tick_debut;
    //Tick du début de la pause (Pour sauvegarder le temps depuis le début de la pause)
    int tick_pause;
    //Status du timer
    bool paused;
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
}Timer_t;

extern void timer_debut(Timer_t * Timer);
extern void timer_stop(Timer_t * Timer);
extern int timer_get_ticks(Timer_t * Timer);
extern void timer_pause(Timer_t * Timer);
extern void timer_unpause(Timer_t * Timer);
extern bool timer_is_started(Timer_t * Timer);
extern bool timer_is_paused(Timer_t * Timer);
extern Timer_t * timer_init();

#endif