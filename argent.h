#ifndef _ARGENT_H_
#define _ARGENT_H_

/*----------------------------------------*/
/*ARGENT
/*----------------------------------------*/

/*placement texture du fond*/
#define FOND_X 10
#define FOND_Y 10

/*placement texture de la piece de monnaie*/
#define PIECE_X 103
#define PIECE_Y 16

/*placement texture de la centaine*/
#define CENT_X 15
#define CENT_Y 16

/*placement texture de la dizaine*/
#define DIZ_X 45
#define DIZ_Y 16

/*placement texture de l'unite*/
#define UNIT_X 75
#define UNIT_Y 16

/*----------------------------------------*/
/*FIN ARGENT
/*----------------------------------------*/

extern void affiche_argent(SDL_Window *window, SDL_Renderer *renderer,int argent_total);

#endif