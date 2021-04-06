#ifndef _LANCEMENT_JEU_H_
#define _LANCEMENT_JEU_H_

typedef struct
{
	Timer_t *temps_jeu;
	int id_salle;
	SDL_Rect *depression;
	SDL_Renderer *renderer;
	SDL_Window *window;
}
param_t;

extern void *fonc_pthread_timer_cb(void *parametre);
extern void changement_salle(param_t *parametre);
extern void fonc_pthread_timer(param_t *parametre);
extern void lancement(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int id_salle);

#endif