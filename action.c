#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "action.h"

#define QUITTE -5
//Initialise les informations d'une action
//En static pour ne pas l'utiliser dans le main 
static action_t *init_action(int id, int prix, int cd,void (*fonction)(int))
{
	action_t *action = malloc(sizeof(action_t));
	action->id = id;
	action->prix = prix;
	action->statut = false;
	action->equipe = 0;
	action->cd = cd;
	action->action_realise = fonction;

	return action;
}

//seul fonction à utiliser, elle initialise un tableau avec toute les actions qu'on a creer.
extern void init_tab_action(action_t * tab[])
{
	tab[0] = init_action(0, 100, 1,fonc_action_1);
	tab[1] = init_action(1, 100, 2,fonc_action_2);
	tab[2] = init_action(2, 100, 3,fonc_action_3);
	tab[3] = init_action(3, 100, 4,fonc_action_4); 
}

//Ajoutez un bouton Equiper pour lancer la fonction
//Equipe une action si elle est acheté et si elle n'est pas déjà équipé
extern int equipe_action(int place, action_t * tab_equipe[4], action_t * tab_action[]){ //Pas fini
	
	//Initialise l'id a une valeur qui ne signifie rien
	int id;


	//Pour la fonction clic_choix()--------------------------

	//Attends de voir sur quelle action on clique
	//Si on clique le bouton pour quitter le menu, renvoie QUITTE
	//Si on clique sur une action, renvoie l'id de l'action (allant de 0 a ...)
	//Si on clique sur un emplacement d'équipement, renvoie la place en valeur négatif (allant de -1 a -4)

	//-------------------------------------------------------

	id = clic_choix();

	//Si on sort du menu d'action, ferme la fenetre du menu des actions et on renvoie -1 
	if(id == QUITTE){

		fermer_fenetre_action(); //A faire mon p'tit Charles :D
		return -1;

	}

	//Si on clique sur un autre emplacement relance la fonction equipe_action avec la nouvelle place, 
	else if(id < 0){

		int place = -id; //On aura récuperer -place, alors on refait le changement de signe
		return equipe_action(place, tab_equipe, tab_action);

	}

	//Sinon on fait soit un échange si l'action est déjà équipé, sinon ça l'équipe simplement (En écrasant l'action déjà placé)
	else if(tab_action[id]->statut && !tab_action[id]->equipe){ //Pas fini

		tab_equipe[place] = tab_action[id];
		tab_equipe[place]->equipe = place + 1;
		return 1;

	}
	else return 0;

}

//modifie le statut d'une action si elle est acheter, retourne faux si on n'a pas assez d'argent.
extern int achat_action(action_t *action, int *argent)
{
	if((*argent) >= action->prix)
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
	printf("Test 1\n");
}

void fonc_action_2 (int jour)
{
	//à faire.
	//diminue encore plus la barre d'agitation
	printf("Test 2\n");
}

void fonc_action_3 (int jour)
{
	//à faire.
	//ralentit la progression de la barre d'agitation
	printf("Test 3\n");
}

void fonc_action_4 (int jour)
{
	//à faire.
	//bloque la barre de depression pendant un temps donné
	printf("Test 4\n");
}

/*----------------------------------------------------------*/