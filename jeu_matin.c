/**
* \file jeu_matin.c
* \brief Cette ensemble de fonction agit sur le cours du matin.
* \details On utilise cet ensemble de fonction lorsque le joueur commence le cour du matin, elle permet d'envoyer le joueur
* au moment voulut dans le self.
* \author Quenault Maxime, Renoit Charles
*/

#include "commun.h"
#include "jeu_matin.h"
#include "timer.h"
#include "barre.h"
#include "self.h"
#include <time.h>

/**
* a doxigéner
*
*/
void gameOver_matin(param_t * parametre){
	SDL_Texture *texture_game_over = NULL;
	ajout_texture(texture_game_over ,"images/game_over.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
	SDL_Event event;
	while(SDL_PollEvent(&event))
		{
			

			switch (event.type)
			{

				case SDL_MOUSEBUTTONDOWN:
					if((event.button.x > BOUTON_LOAD_SAVE_X_MAX && event.button.x < BOUTON_LOAD_SAVE_X_MIN)&&(event.button.y > BOUTON_LOAD_SAVE_Y_MAX && event.button.y < BOUTON_LOAD_SAVE_X_MIN))
					{
						parametre->perdu = SDL_TRUE;//defaite = 1 et on retourne a l'ecran d'aceuille
					}
					if((event.button.x > BOUTON_FIN_X_MAX && event.button.x < BOUTON_FIN_X_MIN)&&(event.button.y > BOUTON_FIN_Y_MAX && event.button.y < BOUTON_FIN_X_MIN))
					{

						parametre->perdu = SDL_FALSE;//defaite = 0 et on charge la derniere sauvegarde
					};
					break;

				default:
					break;

			}
		}
}

/**
* \brief Fonction qui s'occupe du cours du matin.
* 
* \details Lorsque cette fonction est lancé, un thread est lancé au même moment, ce dernier execute la fonction \a fonc_pthread_timer1. Le but de la fonction est de rendre le jeu 
* jouable, nous avons donc l'ajout de toute les textures necessaire au bon déroulement du jeu. Le switch est là pour regarder le clic du joueur, à partir de là le joueur à
* plusieurs possibilité, mettre en pause le jeu ou appuyer sur une action. Pendant ce temps nous avons la barre sonore qui augmente et la barre de depression qui augmente selon la
* barre sonore.
*
* \param statut_menu est un valeur qui permet de savoir si oui ou non le menu pause est afficher à l'ecran, si c'est le cas alors le joueur peut cliquer sur reprendre ou quitter,
* alors que si ce n'est pas le cas alors le joueur ne pourra pas y avoir accés.
*
*/

void lancement_matin(param_t * parametre)
{
	//variables pour les barres
	int cpt1 = 0;
	int defaite = 0; //si defaite = 1 c'est perdu
	int agit = 0;
	int temps = 30;
	srand(time(NULL));
	///////////////////////////

	printf("bienvenue dans le cours du matin\n");

	SDL_Texture *texture_classe = NULL;
	SDL_Texture *texture_self = NULL;

	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_menu_option = NULL;

	SDL_Texture *texture_barre_son = NULL;
	SDL_Texture *texture_barre_depression = NULL;

	SDL_Texture *texture_action1 = NULL;//action 1
	SDL_Texture *texture_action2 = NULL;//action 2
	SDL_Texture *texture_action3 = NULL;//action 3
	SDL_Texture *texture_action4 = NULL;//action 4

	SDL_Texture *texture_backgrnd_jour = NULL;

	SDL_Rect *barre_depression;
	barre_depression=malloc(sizeof(SDL_Rect));

	SDL_Rect *barre_sonore;
	barre_sonore=malloc(sizeof(SDL_Rect));

	int status_menu = -1;

	ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
	aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
	
	affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);

	init_barre_depression(parametre->renderer, barre_depression, -5);
	init_barre_sonore(parametre->renderer, barre_sonore);

	ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
	ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

	SDL_RenderPresent(parametre->renderer);

	(parametre->temps_jeu)->debut(parametre->temps_jeu);

	/*----------------------------------------------------------------------*/
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched && parametre->perdu != SDL_TRUE)
	{





		//mise a jour des barres atomatic
		//printf("debut barre:\n");
		agit = parametre->nb_jour + 15;
		SDL_Delay(1);
		//printf("temps:%d\n", temps);
		
		if(((*barre_depression).h>(-250)) && status_menu == -1 && temps == ((cpt1 % 181)+20))
			{
				temps = rand()%(181)+20;
				/*mise a jour de la barre sonore + remise en place de la texture associé*/
				update_barre_sonore(parametre->renderer, barre_sonore, agit);
				SDL_DestroyTexture(texture_barre_son);
				ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
				
				/*mise a jour de la barre de depression + remise en place de la texture associé*/
				update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
				SDL_DestroyTexture(texture_barre_depression);
				ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

				SDL_RenderPresent(parametre->renderer);
			}
		///////////////////////////////////

		//detection de la defaite
		if ((*barre_depression).h<=(-247))
			{
				(parametre->temps_jeu)->stop(parametre->temps_jeu);
				gameOver_matin(parametre);

				//si defaite = 0 charger last sauvegarde
				//sinon go ecran d'aceuille
				/*if (parametre->perdu == SDL_False)
				{
					charger(argent, jour, )
				}*/
			}	
		/////////////////////////	
		//test
		//printf("nb boucles: %d\n",cpt1);
		cpt1++;
		//////
		if((parametre->temps_jeu)->get_ticks(parametre->temps_jeu) > 10000) 
			program_launched = SDL_FALSE;




		SDL_Event event;//Créer un évènement

		while(SDL_PollEvent(&event) && program_launched)
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("x : %i & y : %i\n", event.button.x, event.button.y);
					/*je vais realiser plusieurs destroy et creation à la suite, c'est pour eviter l'acumulation des textures*/
					if((event.button.x > 70 && event.button.x < 134)&&(event.button.y > 530 && event.button.y < 594)&&status_menu == -1)
					{
						/*si on clique sur le bouton 1*/
						update_barre_sonore(parametre->renderer, barre_sonore, press_action(parametre->renderer, 1));

						SDL_DestroyTexture(texture_barre_son);
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

						SDL_DestroyTexture(texture_barre_depression);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer,parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(parametre->renderer);
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN))
					{
						(parametre->temps_jeu)->pause(parametre->temps_jeu);
						/*si on clique sur le menu*/
						status_menu = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_DestroyTexture(texture_menu_option);
						ajout_texture(texture_menu_option ,"images/menu_pause.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);

						SDL_RenderPresent(parametre->renderer);
					}

					if((event.button.x < QUIT_X_MAX && event.button.x > QUIT_X_MIN)&&(event.button.y < QUIT_Y_MAX && event.button.y > QUIT_Y_MIN)&&status_menu == 1)
					{
						(parametre->temps_jeu)->stop(parametre->temps_jeu); 
						/*si on clique sur le bouton 'quitter le jeu'*/ 
						parametre->quitte = SDL_TRUE;
						program_launched = SDL_FALSE;
					}

					if((event.button.x < REPRENDRE_X_MAX && event.button.x > REPRENDRE_X_MIN)&&(event.button.y < REPRENDRE_Y_MAX && event.button.y > REPRENDRE_Y_MIN)&&status_menu == 1)
					{

						(parametre->temps_jeu)->unpause(parametre->temps_jeu);
						/*si on clique sur le bouton 'reprendre le jeu'*/
						//printf("%d ms\n", parametre->temps_jeu->get_ticks(parametre->temps_jeu));

						status_menu = -1;

						SDL_RenderClear(parametre->renderer);

						
						ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
						affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
						
						
						aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

						ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);

						update_barre_sonore(parametre->renderer, barre_sonore, 0);
						update_barre_depression(parametre->renderer, barre_depression, barre_sonore, 0);

						
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(parametre->renderer);
					};
					break;

				default:
					break;

			}		
		}
	}
	parametre->val_depression = (*barre_depression).h;
	printf("tu quitte le cour du matin\n");
	SDL_DestroyTexture(texture_action4);
	SDL_DestroyTexture(texture_action3);
	SDL_DestroyTexture(texture_action2);
	SDL_DestroyTexture(texture_action1);
	free(barre_sonore);
	barre_sonore = NULL;
	free(barre_depression);
	barre_depression = NULL;
	SDL_DestroyTexture(texture_classe);
}
