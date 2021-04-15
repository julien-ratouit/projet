/**
* \file action.c
* \brief Ce programme permet de gerer les actions possibles lors de la partie.
* \details On utilise ce programme quand le joueur se trouve dans la salle des profs mais également en jeu pour permettre d'agir en fonction de l'action utilisé.
* \author Vallet Guillaume
*/

#include "commun.h"
#include "salle_prof.h"
#include "texture_sdp.h"


//Constantes renvoyer quand on clique sur les emplacement d'équipement respectifs
#define EQUIP_1 -1
#define EQUIP_2 -2
#define EQUIP_3 -3
#define EQUIP_4 -4

#define QUITTE_MENU -5
#define QUITTE_SDP -6



/**
* \brief Affiche la barre contenant les actions
* 
* \details On commence par afficher le fond de la barre et ensuite on affiche les actions en fonction de leur état, si elles sont acheté ou non. 
* \param action_equipe est le tableau contenant l'ensemble des actions acheté par le joueurs, leur id correspond à leur emplacement.
* \return La fonction ne return aucune valeurs, elle ne fait que de l'affichage
*  
*/
void affiche_barre_action(param_t *parametre)
{
	SDL_Texture *texture_prof = NULL;
	aff_texture_sp(parametre, texture_prof);
    ajout_texture_non_centre(background_menu_action,"images/barre_action.png", parametre->renderer, parametre->window, 420, 450);

	if(action_equipe[0] != NULL)
    	ajout_texture_non_centre(action_barre_n1, (action_equipe[0]->img_action_rond), parametre->renderer,parametre->window, 481, 471);
    if(action_equipe[1] != NULL)
		ajout_texture_non_centre(action_barre_n2, (action_equipe[1]->img_action_rond), parametre->renderer, parametre->window, 558, 471);
    if(action_equipe[2] != NULL)
		ajout_texture_non_centre(action_barre_n3, (action_equipe[2]->img_action_rond), parametre->renderer, parametre->window, 635, 471);
    if(action_equipe[3] != NULL)
		ajout_texture_non_centre(action_barre_n4, (action_equipe[3]->img_action_rond), parametre->renderer, parametre->window, 712, 471);
	
    SDL_RenderPresent(parametre->renderer);
	
}


/**
* \brief Affiche le menu des actions
* 
* \details On commence par afficher le fond du tableau contenant toutes les actions achetés pour ensuite les achiffer sous forme de liste, à ne pas confondre avec 
* \a affiche_barre_action car ici on affiche sous forme de liste alors que dans \a affiche_barre_action on affiche sous forme d'icone. 
* \param action_equipe[] action_equipe est le tableau contenant l'ensemble des actions acheté par le joueurs, leur id correspond à leur emplacement.
*
* \return La fonction ne return aucune valeurs, elle ne fait que de l'affichage
*  
*/
void affiche_menu_action(param_t *parametre){

	ajout_texture_non_centre(croix_rouge, "images/bouton_croix_rouge.png", parametre->renderer, parametre->window, 781, 64);
	ajout_texture_non_centre(background_menu_action,"images/background_menu_action.png", parametre->renderer, parametre->window,420 , 50);
	//printf("Ca crash ?");
	if(action_equipe[0] != NULL){
		//printf("Invisible 0 :)))");
    	ajout_texture_non_centre(action_barre_n1, (action_equipe[0]->img_action_rect), parametre->renderer,parametre->window, 480, 80);
	}
    if(action_equipe[1] != NULL){
		//printf("Invisible 1 :)))");
		ajout_texture_non_centre(action_barre_n2, (action_equipe[1]->img_action_rect), parametre->renderer, parametre->window, 480, 155);
	}
		
    if(action_equipe[2] != NULL){
		//printf("Invisible 2 :)))");
		ajout_texture_non_centre(action_barre_n3, (action_equipe[2]->img_action_rect), parametre->renderer, parametre->window,480, 225);
	}
		
    if(action_equipe[3] != NULL){
		//printf("Invisible 3 :)))");
		ajout_texture_non_centre(action_barre_n4, (action_equipe[3]->img_action_rect), parametre->renderer, parametre->window, 480, 300);
	}

	//printf("Ca passe presque :'(\n");
    SDL_RenderPresent(parametre->renderer);
	//printf("C'est passé ! :D\n");


}

/**
* \brief Initialise les informations d'une action
* 
* \details Ici, on va initialiser les informations pour chaque action en \a static pour ne pas qu'elle se retrouve modifer dans la fonction main. 
*
* \return On return un \a action_t qui est notre action initialisé.
*  
*/
extern action_t *init_action(int id, int prix, int cd,void (*fonction)(int), const char * lien_img_rect, const char * lien_img_rond)
{
	action_t *action = malloc(sizeof(action_t));
	action->id = id;
	action->prix = prix;
	action->statut = false;
	action->equipe = 0;
	action->cd = cd;
	action->action_realise = fonction;
	action->img_action_rond = lien_img_rond;
	action->img_action_rect = lien_img_rect;

	return action;
}


/**
* \brief Initialise un tableau d'action
* 
* \details Ici, on va initialiser un tableau d'action, chaque case correspond à une action initialisé par la fonction \a init_action , elle est la
* seul fonction a utiliser dans le code, elle s'occupe d'initialiser les actions avec les paramètres que le programmeur aura choisi.
*
* \return On return aucune valeur car on modifie un pointeur sur un tableau.
*  
*/
extern void init_tab_action(action_t * tab[])
{
	tab[0] = init_action(0, 1 , 1,fonc_action_1, "images/action_barre_n1.png", "images/action_n1.png");
	tab[1] = init_action(1, 1 , 2,fonc_action_2, "images/action_barre_n2.png", "images/action_n2.png");
	tab[2] = init_action(2, 1 , 3,fonc_action_3, "images/action_barre_n3.png", "images/action_n3.png");
	tab[3] = init_action(3, 1 , 4,fonc_action_4, "images/action_barre_n3.png", "images/action_n3.png");
}

/**
* \brief Attend un clic du joueur
* 
* \details Ici, la fonction va attendre un clic du joueur, elle va permettre de modifier l'emplacement des actions achetés par le joueur. Quand le joueur
*  clic sur une action alors la fonction renvoie l'id de l'action allant de 0 à 4 (sa position dans le tableau)
*  ou alors, si le joueur clic sur un emplacement alors la fonction renvoie le numéros de l'emplacement en valeur negative allant de -1 à -4.
*
* \return On return soit le numero de l'emplacement, l'id de l'action ou une valeur indiquant que l'on quitte le menu.
*  
*/
extern int clic_choix_sdp(){

	SDL_Event event;

	while(SDL_PollEvent(&event)){

		switch(event.type)
		{
				case SDL_MOUSEBUTTONDOWN:
				printf("x : %i & y : %i\n", event.button.x, event.button.y);
				//Si on clique sur la croix //Salle des profs
				if((event.button.x < 831 && event.button.x > 785) && (event.button.y < 109 && event.button.y > 67)){

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
}


/**
* \brief Modifie le statut d'une action
* 
* \details Si le joueur clic sur une action la fonction se lance et regarde la somme d'argent du joueur. Si la somme en question est assez grande alors l'action change de statut est
* devient acheté, or, si la somme n'est pas assez grande rien ne se passe.
*
* \return On return un \a int qui défini si oui ou non l'action à changé de statut.
*  
*/
extern int achat_action(action_t *action, int argent)
{
	if(argent >= action->prix)
	{
		action->statut = true;
		argent -= action->prix;
		return argent;
	}
	else
		return argent;
}

//Ajoutez un bouton Equiper pour lancer la fonction
//Equipe une action si elle est acheté et si elle n'est pas déjà équipé
/**
* \brief Equipe une action
* 
* \details à remplir
*
* \return à remplir
*  
*/
extern int equipe_action(int place, int argent, action_t * tab_equipe[4], action_t * tab_action[],param_t *parametre, SDL_Texture *texture_prof){

	affiche_menu_action(parametre);
	int id;
	id = clic_choix_sdp();

	switch(id){
		//Si on clique sur la croix, on quitte
		case QUITTE_SDP: return QUITTE_SDP;
		//Si on clique sur un autre emplacement relance la fonction equipe_action avec la nouvelle place
		case EQUIP_4 : return equipe_action(3, argent, tab_equipe, tab_action,parametre, texture_prof); break;
		case EQUIP_3 : return equipe_action(2, argent, tab_equipe, tab_action,parametre, texture_prof); break;
		case EQUIP_2 : return equipe_action(1, argent, tab_equipe, tab_action,parametre, texture_prof); break;
		case EQUIP_1 : return equipe_action(0, argent, tab_equipe, tab_action,parametre, texture_prof); break;
		case QUITTE_MENU : return QUITTE_MENU; break;
		default : break;
	}

	//printf("On sort !\n");

	id--; //Car clic_choix renvoie 0 quand il n'a pas de clic, donc je décale tout mes indices d'actions de 1 et je les remets bien ici


	//Sinon on fait soit un échange si l'action est déjà équipé, sinon ça l'équipe simplement (En écrasant l'action déjà placé)
	if(tab_action[id]->statut){
		printf("Action %d déja acheté \n",id);
		if(!(tab_action[id]->equipe)){//Le cas où il n'est pas déjà présent dans l'équipe

			tab_equipe[place] = tab_action[id];
			tab_equipe[place]->equipe = place + 1;
			

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

		SDL_RenderClear(parametre->renderer);
		aff_texture_sp(parametre,texture_prof);
		affiche_barre_action(parametre);
		affiche_menu_action(parametre);
		return equipe_action(place,argent, tab_equipe, tab_action,parametre,texture_prof);
	}
	//Si sur ce que l'on clique n'est pas acheté, ça veut dire qu'on veut l'acheter :D
	else{
		parametre->argent = achat_action(tab_action[id], argent );
		argent = parametre->argent;
		SDL_RenderClear(parametre->renderer);
		aff_texture_sp(parametre,texture_prof);
		affiche_barre_action(parametre);
		affiche_menu_action(parametre);
		return equipe_action(place,argent, tab_equipe, tab_action,parametre,texture_prof);//Si on achète je relance la procédure d'équipationnagization :D

	}

}


/**
* \brief Fonction principale des actions
* 
* \details Lance l'affichage du menu et gère les différentes fonctions d'achat et d'équipage des actions
*  
*/
extern int menu_action(action_t * tab_equipe[4], action_t * tab_action[],param_t *parametre, SDL_Texture *texture_prof){

	int test_sortie = 0;
	int choix;

	affiche_barre_action(parametre);
	while(test_sortie != QUITTE_MENU && test_sortie != QUITTE_SDP){//Test_sortie vaut vrai quand on clique sur la croix

		choix = clic_choix_sdp();
		
		switch(choix){

			//Si on clique sur la croix, on sort.
			//case QUITTE_MENU : test_sortie = QUITTE_MENU; break;
			case QUITTE_SDP : test_sortie = QUITTE_SDP; break;
			//Si on choisis une case d'équipement, ça renvoie la fonction equipe_action a la bonne place.
			case EQUIP_4 : test_sortie = equipe_action(3, parametre->argent, tab_equipe, tab_action, parametre, texture_prof); break;
			case EQUIP_3 : test_sortie = equipe_action(2, parametre->argent, tab_equipe, tab_action, parametre, texture_prof); break;
			case EQUIP_2 : test_sortie = equipe_action(1, parametre->argent, tab_equipe, tab_action, parametre, texture_prof); break;
			case EQUIP_1 : test_sortie = equipe_action(0, parametre->argent, tab_equipe, tab_action, parametre, texture_prof); break;
			case QUITTE_MENU : test_sortie = QUITTE_MENU; break;
			//Si on renvoie autre chose on s'en occupe pas
			default : test_sortie = 0; break;
		}

	}

	if(test_sortie == QUITTE_SDP) 
		return 1;
	if(test_sortie == QUITTE_MENU)
		return -1;

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
