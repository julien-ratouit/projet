#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "action.h"

//fonction à ne pas utiliser dans le main
action_t *init_action(int id, int prix, void (*fonction)(int))
{
	action_t *action = malloc(sizeof(action_t));
	action->id = id;
	action->prix = prix;
	action->statut = false;
	action->action_realise = fonction;

	return action;
}

//seul fonction à utiliser, elle initialise un tableau avec toute les actions qu'on a creer.
void init_tab_action(action_t * tab[])
{
	tab[0] = init_action(0, 100, fonc_action_1);
	tab[1] = init_action(1, 100, fonc_action_2);
	tab[2] = init_action(2, 100, fonc_action_3);
	tab[3] = init_action(3, 100, fonc_action_4); 
}

//modifie le statut d'une action si elle est acheter, retourne faux si on n'a pas assez d'argent.
int achat_action(action_t *action, int *argent)
{
	if(argent >= action->prix)
	{
		action->statut = true;
		(*argent) -= action->prix;
		return 1;
	}
	else
		return 0;
}

//fonctions d'action, leurs but est d'agire sur la barre d'agitation ou de depression en fonction de l'action choisi.
/*----------------------------------------------------------*/
void fonc_action_1 (int jour)
{
	//à faire.
	//diminue de quelques pourcent la barre d'agitation
}

void fonc_action_2 (int jour)
{
	//à faire.
	//diminue encore plus la barre d'agitation
}

void fonc_action_3 (int jour)
{
	//à faire.
	//ralentit la progression de la barre d'agitation
}

void fonc_action_4 (int jour)
{
	//à faire.
	//bloque la barre de depression pendant un temps donné
}

/*----------------------------------------------------------*/