#include <time.h>
#include <pthread.h>
#include "commun.h"
#include "timer.h"
#include "barre.h"
#include "lancement_jeu.h"

int gameOver(SDL_Renderer *renderer, SDL_Window *window){
	SDL_Texture *texture_game_over = NULL;
	ajout_texture(texture_classe ,"images/game_over.png" , renderer, window, HAUTEUR , LARGEUR);
	SDL_Event event;
	while(SDL_PollEvent(&event))
		{
			

			switch (event.type)
			{

				case SDL_MOUSEBUTTONDOWN:
					if((event.button.x > BOUTONN_LOAD_SAVE_X_MAX && event.button.x < BOUTONN_LOAD_SAVE_X_MIN)&&(event.button.y > BOUTONN_LOAD_SAVE_Y_MAX && event.button.y < BOUTONN_LOAD_SAVE_X_MIN))
					{
						return 1;//defaite = 1 et on retourne a l'ecran d'aceuille
					}
					if((event.button.x > BOUTONN_FIN_X_MAX && event.button.x < BOUTONN_FIN_X_MIN)&&(event.button.y > BOUTONN_FIN_Y_MAX && event.button.y < BOUTONN_FIN_X_MIN))
					{
						return 0;//defaite = 0 et on charge la derniere sauvegarde
					};
					break;

				default:
					break;

			}
		}
}

void lancement(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent)
{
	//variables pour les barres
	int cpt1 = 0;
	int defaite = 0; //si defaite = 1 c'est perdu
	int nb_jour = 0;
	int agit = 0;
	int temps;
	///////////////////////////

	SDL_Texture *texture_classe = NULL;
	SDL_Texture *texture_self = NULL;

	param_barre_t *barre_param = malloc(sizeof(param_barre_t));
	barre_param->rendu = renderer;
	barre_param->fenetre = window;

	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_menu_option = NULL;

	SDL_Texture *texture_barre_son = NULL;
	SDL_Texture *texture_barre_depression = NULL;

	SDL_Texture *texture_action1 = NULL;//action 1
	SDL_Texture *texture_action2 = NULL;//action 2
	SDL_Texture *texture_action3 = NULL;//action 3
	SDL_Texture *texture_action4 = NULL;//action 4

	SDL_Rect *barre_depression;
	barre_depression=malloc(sizeof(SDL_Rect));

	SDL_Rect *barre_sonore;
	barre_sonore=malloc(sizeof(SDL_Rect));

	int status_menu = -1;
	int indice_salle = 0;

	/*variables de test*/
	int *achat = malloc(sizeof(int));
	(*achat) = 4;
	int test;
	
	/*-----------------*/

	ajout_texture(texture_classe ,"images/salle_de_classe.png" , renderer, window, HAUTEUR , LARGEUR);
	aff_action(achat, renderer, window, texture_action1, texture_action2, texture_action3, texture_action4);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", renderer, window, OPTION_HAUTEUR, OPTION_LARGEUR);

	init_barre_depression(renderer, barre_depression);
	init_barre_sonore(renderer, barre_sonore);

	ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);
	ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

	SDL_RenderPresent(renderer);

	temps_jeu->debut(temps_jeu);

	SDL_bool program_launched = SDL_TRUE;
	while(program_launched && defaite != 1)
	{

		SDL_Event event;

		//mise a jour des barres atomatic
		printf("debut barre:\n");
		agit = nb_jour + 15;
		temps = rand()%(200-20+1)+20;
		SDL_Delay(temps);
		printf("temps:%d\n", temps);
		if(((*barre_depression).h>(-250))&&status_menu == -1)
			{
				/*mise a jour de la barre sonore + remise en place de la texture associé*/
				update_barre_sonore(renderer, barre_sonore, agit);
				SDL_DestroyTexture(texture_barre_son);
				ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);

				/*mise a jour de la barre de depression + remise en place de la texture associé*/
				update_barre_depression(renderer, barre_depression, barre_sonore, agit);
				SDL_DestroyTexture(texture_barre_depression);
				ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

				SDL_RenderPresent(renderer);
			}
		///////////////////////////////////

		//detection de la defaite
		if ((*barre_depression).h<=(-247))
			{
				defaite = gameOver(renderer, window);
				//si defaite = 0 charger last sauvegarde
				//sinon go ecran d'aceuille
				if (defaite = 0)
				{
					charger(argent, jour, )
				}
			}	
		/////////////////////////	
		//test
		printf("nb boucles: %d\n",cpt1);
		cpt1++;
		//////
		while(SDL_PollEvent(&event))
		{
			

			switch (event.type)
			{

				case SDL_MOUSEBUTTONDOWN:
					//printf("x : %i & y : %i\n", event.button.x, event.button.y);
					/*je vais realiser plusieurs destroy et creation à la suite, c'est pour eviter l'acumulation des textures*/
					if((event.button.x > 70 && event.button.x < 134)&&(event.button.y > 530 && event.button.y < 594)&&status_menu == -1)
					{
						/*si on clique sur le bouton 1*/
						update_barre_sonore(renderer, barre_sonore, press_action(renderer, 1));

						SDL_DestroyTexture(texture_barre_son);
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);

						SDL_DestroyTexture(texture_barre_depression);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(renderer);
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN))
					{
						temps_jeu->pause(temps_jeu);
						/*si on clique sur le menu*/
						status_menu = 1;
						//SDL_DestroyTexture(texture_menu_option);
						ajout_texture(texture_menu_option ,"images/menu_pause.png" , renderer, window, HAUTEUR , LARGEUR);

						SDL_RenderPresent(renderer);
					}

					if((event.button.x < QUIT_X_MAX && event.button.x > QUIT_X_MIN)&&(event.button.y < QUIT_Y_MAX && event.button.y > QUIT_Y_MIN)&&status_menu == 1)
					{
						temps_jeu->stop(temps_jeu); 
						/*si on clique sur le bouton 'quitter le jeu'*/ 
						program_launched = SDL_FALSE;
					}

					if((event.button.x < REPRENDRE_X_MAX && event.button.x > REPRENDRE_X_MIN)&&(event.button.y < REPRENDRE_Y_MAX && event.button.y > REPRENDRE_Y_MIN)&&status_menu == 1)
					{

						temps_jeu->unpause(temps_jeu);
						/*si on clique sur le bouton 'reprendre le jeu'*/
						printf("%d ms\n", temps_jeu->get_ticks(temps_jeu));

						status_menu = -1;

						
						SDL_DestroyTexture(texture_menu_option);

						SDL_DestroyTexture(texture_classe);
						ajout_texture(texture_classe ,"images/salle_de_classe.png" , renderer, window, HAUTEUR , LARGEUR);
						
						SDL_DestroyTexture(texture_action1);
						SDL_DestroyTexture(texture_action2);
						SDL_DestroyTexture(texture_action3);
						SDL_DestroyTexture(texture_action4);
						aff_action(achat, renderer, window, texture_action1, texture_action2, texture_action3, texture_action4);

						SDL_DestroyTexture(texture_btn_option);
						ajout_texture_non_centre(texture_btn_option , "images/option.png", renderer, window, OPTION_HAUTEUR, OPTION_LARGEUR);

						update_barre_sonore(renderer, barre_sonore, 0);
						update_barre_depression(renderer, barre_depression, barre_sonore, 0);

						SDL_DestroyTexture(texture_barre_son);
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);

						SDL_DestroyTexture(texture_barre_depression);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(renderer);
					};
					break;

				default:
					break;

			}
		}
	}

	SDL_DestroyTexture(texture_action4);
	SDL_DestroyTexture(texture_action3);
	SDL_DestroyTexture(texture_action2);
	SDL_DestroyTexture(texture_action1);
	free(barre_sonore);
	free(barre_depression);
	SDL_DestroyTexture(texture_classe);
}
