#ifndef _LANCEMENT_JEU_H_
#define _LANCEMENT_JEU_H_

typedef struct
{
	SDL_Renderer *rendu;
	SDL_Window *fenetre;
}param_barre_t;

extern void lancement(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent);

#endif