/**
* \file jeu_apremidi.c
* \brief Cette ensemble de fonction agit sur le cours de l'après-midi.
* \details On utilise cet ensemble de fonction lorsque le joueur commence le cour de l'après midi, elle permet d'envoyer le joueur
* au moment voulut dans la salle des profs.
* \author Quenault Maxime, Renoit Charles
*/


#include "commun.h"
#include "jeu_apremidi.h"
#include "timer.h"
#include "barre.h"
#include "salle_prof.h"



/**
* \brief Fonction qui s'occupe du cours de l'après-midi.
* 
* \details 
*/
void lancement_apremidi(param_t * parametre)
{
	pthread_t thread_minuteur;
	printf("bienvenue dans le cours de l'apres-midi\n");

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

	SDL_Rect *barre_depression;
	barre_depression=malloc(sizeof(SDL_Rect));

	SDL_Rect *barre_sonore;
	barre_sonore=malloc(sizeof(SDL_Rect));

	int status_menu = -1;

	int *achat = malloc(sizeof(int));
	(*achat) = 4;
	int score = 0;
	int test;

	
	ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
	aff_action(achat, parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);

	init_barre_depression(parametre->renderer, barre_depression);
	init_barre_sonore(parametre->renderer, barre_sonore);

	ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
	ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

	SDL_RenderPresent(parametre->renderer);

	(parametre->temps_jeu)->debut(parametre->temps_jeu);



	/*----------------------------------------------------------------------*/
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{

		SDL_Event event;//Créer un évènement

		while(SDL_PollEvent(&event) && program_launched)
		{
			switch (event.type)
			{
				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_a:
							if(((*barre_depression).h>(-250))&&status_menu == -1) 
							{
								score++;
								/*mise a jour de la barre sonore + remise en place de la texture associé*/
								update_barre_sonore(parametre->renderer, barre_sonore, score);
								SDL_DestroyTexture(texture_barre_son);
								ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

								/*mise a jour de la barre de depression + remise en place de la texture associé*/
								update_barre_depression(parametre->renderer, barre_depression, barre_sonore, score);
								SDL_DestroyTexture(texture_barre_depression);
								ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

								SDL_RenderPresent(parametre->renderer);
								continue;
							}
							else
								break;

						default:
							continue;
					}

				case SDL_MOUSEBUTTONDOWN:
					printf("tu es toujours dans la fonction jeu_matin\n");
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
						printf("%d ms\n", parametre->temps_jeu->get_ticks(parametre->temps_jeu));

						status_menu = -1;

						SDL_DestroyTexture(texture_menu_option);

						SDL_DestroyTexture(texture_classe);
						ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
						
						SDL_DestroyTexture(texture_action1);
						SDL_DestroyTexture(texture_action2);
						SDL_DestroyTexture(texture_action3);
						SDL_DestroyTexture(texture_action4);
						aff_action(achat, parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

						SDL_DestroyTexture(texture_btn_option);
						ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);

						update_barre_sonore(parametre->renderer, barre_sonore, 0);
						update_barre_depression(parametre->renderer, barre_depression, barre_sonore, 0);

						SDL_DestroyTexture(texture_barre_son);
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

						SDL_DestroyTexture(texture_barre_depression);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(parametre->renderer);
					};
					break;

				default:
					break;

			}
			if((parametre->temps_jeu)->get_ticks(parametre->temps_jeu) > 1000) 
				program_launched = SDL_FALSE;
		}
	}
	printf("tu quitte le cour de l'aprem\n");
	SDL_DestroyTexture(texture_action4);
	SDL_DestroyTexture(texture_action3);
	SDL_DestroyTexture(texture_action2);
	SDL_DestroyTexture(texture_action1);
	free(barre_sonore);
	free(barre_depression);
	SDL_DestroyTexture(texture_classe);
}
