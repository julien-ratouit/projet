#ifndef _JEU_MATIN_H_
#define _JEU_MATIN_H_

extern void *fonc_pthread_timer1_cb(void *parametre);
extern void fonc_pthread_timer1(param_t *parametre);
extern void lancement_matin(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent);

#endif