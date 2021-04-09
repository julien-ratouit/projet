#ifndef _JEU_APREMIDI_H_
#define _JEU_APREMIDI_H_

extern void *fonc_pthread_timer2_cb(void *parametre);
extern void fonc_pthread_timer2(param_t *parametre);
extern void lancement_apremidi(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent);

#endif