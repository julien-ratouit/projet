#include "commun.h"
#include "action.h"

//Constantes renvoyer quand on clique sur les emplacement d'équipement respectifs
#define EQUIP_1 -1
#define EQUIP_2 -2
#define EQUIP_3 -3
#define EQUIP_4 -4
//-------------------------------------------------------------------------------
#define QUITTE_MENU -5
#define QUITTE_SDP -6

//Initialise les informations d'une action
//En static pour ne pas l'utiliser dans le main
extern action_t *init_action(int id, int prix, int cd,void (*fonction)(int))
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


//Pour la fonction clic_choix()--------------------------

//Attends de voir sur quelle action on clique
//Si on clique le bouton pour quitter le menu, renvoie QUITTE_MENU
//Si on clique sur une action, renvoie l'id de l'action (allant de 0 a ...)
//Si on clique sur un emplacement d'équipement, renvoie la place en valeur négatif (allant de -1 a -4)

//-------------------------------------------------------


extern int clic_choix_sdp(){

	SDL_Event event;

	switch(event.type)
	{
			case SDL_MOUSEBUTTONDOWN:
			//Si on clique sur la croix //Salle des profs
			if((event.button.x < EMPLACEMENT_QUITTE_MENU_ACTION_X_MAX && event.button.x > EMPLACEMENT_QUITTE_MENU_ACTION_X_MIN) && (event.button.y < EMPLACEMENT_QUITTE_MENU_ACTION_Y_MAX && event.button.y > EMPLACEMENT_QUITTE_MENU_ACTION_Y_MIN)){

				return QUITTE_MENU;

			}
			//Si on clique sur les emplacement d'équipement
			if((event.button.x < EMPLACEMENT_EQUIPE_1_X_MAX && event.button.x > EMPLACEMENT_EQUIPE_1_X_MIN) && (event.button.y < EMPLACEMENT_EQUIPE_1_Y_MAX && event.button.y > EMPLACEMENT_EQUIPE_1_Y_MIN)){

				return EQUIP_1;

			}
			if((event.button.x < EMPLACEMENT_EQUIPE_2_X_MAX && event.button.x > EMPLACEMENT_EQUIPE_2_X_MIN) && (event.button.y < EMPLACEMENT_EQUIPE_2_Y_MAX && event.button.y > EMPLACEMENT_EQUIPE_2_Y_MIN)){

				return EQUIP_2;

			}
			if((event.button.x < EMPLACEMENT_EQUIPE_3_X_MAX && event.button.x > EMPLACEMENT_EQUIPE_3_X_MIN) && (event.button.y < EMPLACEMENT_EQUIPE_3_Y_MAX && event.button.y > EMPLACEMENT_EQUIPE_3_Y_MIN)){

				return EQUIP_3;

			}
			if((event.button.x < EMPLACEMENT_EQUIPE_4_X_MAX && event.button.x > EMPLACEMENT_EQUIPE_4_X_MIN) && (event.button.y < EMPLACEMENT_EQUIPE_4_Y_MAX && event.button.y > EMPLACEMENT_EQUIPE_4_Y_MIN)){

				return EQUIP_4;

			}
			//Si on clique sur les actions
			if((event.button.x < EMPLACEMENT_ACTION_0_X_MAX && event.button.x > EMPLACEMENT_ACTION_0_X_MIN) && (event.button.y < EMPLACEMENT_ACTION_0_Y_MAX && event.button.y > EMPLACEMENT_ACTION_0_Y_MIN)){

				return 0;

			}
			if((event.button.x < EMPLACEMENT_ACTION_1_X_MAX && event.button.x > EMPLACEMENT_ACTION_1_X_MIN) && (event.button.y < EMPLACEMENT_ACTION_1_Y_MAX && event.button.y > EMPLACEMENT_ACTION_1_Y_MIN)){

				return 1;

			}
			if((event.button.x < EMPLACEMENT_ACTION_2_X_MAX && event.button.x > EMPLACEMENT_ACTION_2_X_MIN) && (event.button.y < EMPLACEMENT_ACTION_2_Y_MAX && event.button.y > EMPLACEMENT_ACTION_2_Y_MIN)){

				return 2;

			}
			if((event.button.x < EMPLACEMENT_ACTION_3_X_MAX && event.button.x > EMPLACEMENT_ACTION_3_X_MIN) && (event.button.y < EMPLACEMENT_ACTION_3_Y_MAX && event.button.y > EMPLACEMENT_ACTION_3_Y_MIN)){

				return 3;

			}
			break;
	}
}


//Modifie le statut d'une action si elle est acheter, retourne faux si on n'a pas assez d'argent.
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

//Ajoutez un bouton Equiper pour lancer la fonction
//Equipe une action si elle est acheté et si elle n'est pas déjà équipé
extern int equipe_action(int place, int * argent, action_t * tab_equipe[4], action_t * tab_action[]){

	//affiche_action();//A FAIRE MON P'TIT CHARLES :DDDDD

	int id;
	id = clic_choix_sdp();

	switch(id){
		//Si on clique sur la croix, on quitte
		case QUITTE_MENU: return QUITTE_MENU;
		//Si on clique sur un autre emplacement relance la fonction equipe_action avec la nouvelle place
		case EQUIP_4 : return equipe_action(3, argent, tab_equipe, tab_action); break;
		case EQUIP_3 : return equipe_action(2, argent, tab_equipe, tab_action); break;
		case EQUIP_2 : return equipe_action(1, argent, tab_equipe, tab_action); break;
		case EQUIP_1 : return equipe_action(0, argent, tab_equipe, tab_action); break;
		default : break;
	}

	//Sinon on fait soit un échange si l'action est déjà équipé, sinon ça l'équipe simplement (En écrasant l'action déjà placé)
	if(tab_action[id]->statut){

		if(!tab_action[id]->equipe){//Le cas où il n'est pas déjà présent dans l'équipe

			tab_equipe[place] = tab_action[id];
			tab_equipe[place]->equipe = place + 1;
			return 1;

		}
		else{ //Le cas où il est déjà présent dans l'équipé, on le change juste de place

			int p_switch = (tab_action[id]->equipe) - 1; //Je récupére l'endroit dans tab_equipe où se trouve mon action

			tab_equipe[p_switch] = tab_equipe[place];

			if(tab_equipe[p_switch] != NULL){ //Le cas où l'échange se fait avec une case non vide
				tab_equipe[p_switch]->equipe = p_switch + 1;
			}
			//Si la case est vide alors on ne fait pas l'opération au dessus vu qu'il n'y a rien

			tab_equipe[place] = tab_action[id];
			tab_equipe[place]->equipe = place + 1;

		}
	}
	//Si sur ce que l'on clique n'est pas acheté, ça veut dire qu'on veut l'acheter :D
	else if(achat_action(tab_action[id], argent )){

		return equipe_action(place,argent, tab_equipe, tab_action);//Si on achète je relance la procédure d'équipationnagization :D

	}
	else return  equipe_action(place,argent, tab_equipe, tab_action); //Si y a rien de tout ça c'est que le joueur a dû missclick où cliquer n'importe où, alors je recommence la procédure

}

//------------------------------Fonction principale des actions--------------------------------
//Lance l'affichage du menu et gère les différentes fonctions d'achat et d'équipage des actions
extern void menu_action(int * argent, action_t * tab_equipe[4], action_t * tab_action[]){

	int test_sortie = 0;
	int choix;

	//affichage_menu_action(); //A FAIIIIIIIIIIIIIIIIRE

	while(test_sortie != QUITTE_MENU){//Test_sortie vaut vrai quand on clique sur la croix

		choix = clic_choix_sdp();
		switch(choix){

			//Si on clique sur la croix, on sort.
			case QUITTE_MENU : test_sortie = QUITTE_MENU; break;
			//Si on choisis une case d'équipement, ça renvoie la fonction equipe_action a la bonne place.
			case EQUIP_4 : test_sortie = equipe_action(3, argent, tab_equipe, tab_action); break;
			case EQUIP_3 : test_sortie = equipe_action(2, argent, tab_equipe, tab_action); break;
			case EQUIP_2 : test_sortie = equipe_action(1, argent, tab_equipe, tab_action); break;
			case EQUIP_1 : test_sortie = equipe_action(0, argent, tab_equipe, tab_action); break;
			//Si on renvoie autre chose on s'en occupe pas
			default : test_sortie = 0; break;
		}

	}

	//fermer_menu_action();//A FAIIIIIIIIIIIIIIIIIRE AUSSI :D

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

//PHASE DE TEST du boss
/* Je suis une merde ça fonctionne pas si j'ai pas d'interface XDD
int main(){

	action_t test[4];
	int argent = 100;
	init_tab_action(test);


}*/

void afficher_icone(char * image, int place){
	switch(place){

		case 0: //afficher l'image au coordonnées de la case 1
		case 1: //afficher l'image au coordonnées de la case 1
		case 2: //afficher l'image au coordonnées de la case 1
		case 3: //afficher l'image au coordonnées de la case 1
	}
}