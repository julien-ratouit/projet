#ifndef _DEPRESSION_H_
#define _DEPRESSION_H_

/*placement texture du fond*/
#define FOND_X_DEP 10
#define FOND_Y_DEP 80

/*placement texture de la barre de depression*/
#define DEP_X 112
#define DEP_Y 86

/*placement texture de la dizaine*/
#define DIZ_X_DEP 15
#define DIZ_Y_DEP 86

/*placement texture de l'unite*/
#define UNIT_X_DEP 45
#define UNIT_Y_DEP 86

/*placement texture du poucentage (logo)*/
#define POURC_X_DEP 75
#define POURC_Y_DEP 86

extern void affiche_depression(SDL_Window *window, SDL_Renderer *renderer, int val);


#endif