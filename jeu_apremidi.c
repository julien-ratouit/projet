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
* \brief Fonction de callback 
* 
* \details Cette fonction à pour seul but d'appeler une autre fonction. Cela permet d'evité les warnings lors de l'execution du programme.
*  
*/
void *fonc_pthread_timer2_cb(void *parametre)
{
	fonc_pthread_timer2(parametre);
}


/**
* \brief Fonction du pthread n°2 
* 
* \details Cette fonction va s'executer en même temps que la fonction \a lancement_apremidi , sont but est de comparé le temps passé en jeu
* avec le temps limite accordé par le developpeur. Si le temps arrive à sont terme alors la fonction \a lancement_salle_prof est lancé, le joueur se retrouve donc dans la salle des profs.
*  
*/
void fonc_pthread_timer2(param_t *parametre)
{
	while((parametre->temps_jeu)->get_ticks(parametre->temps_jeu) <= 1000);
	(parametre->temps_jeu)->stop(parametre->temps_jeu);	
	lancement_salle_prof(parametre);
	pthread_exit(NULL);
}



/**
* \brief Fonction qui s'occupe du cours de l'après-midi.
* 
* \details Lorsque cette fonction est lancé, un thread est lancé au même moment, ce dernier execute la fonction \a fonc_pthread_timer2. Le but de la fonction est de rendre le jeu 
* jouable, nous avons donc l'ajout de toute les textures necessaire au bon déroulement du jeu. Le switch est là pour regarder le clic du joueur, à partir de là le joueur à
* plusieurs possibilité, mettre en pause le jeu ou appuyer sur une action. Pendant ce temps nous avons la barre sonore qui augmente et la barre de depression qui augmente selon la
* barre sonore.
*
* \param statut_menu est un valeur qui permet de savoir si oui ou non le menu pause est afficher à l'ecran, si c'est le cas alors le joueur peut cliquer sur reprendre ou quitter,
* alors que si ce n'est pas le cas alors le joueur ne pourra pas y avoir accés.
*/
void lancement_apremidi(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent)
{
	pthread_t thread_minuteur;
	printf("bienvenue dans le cours de l'apres-midi\n");

	param_t *parametre = malloc(sizeof(param_t));

	parametre->temps_jeu = temps_jeu;
	parametre->argent = argent;
	parametre->window = window;
	parametre->renderer = renderer;

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

	ajout_texture(texture_classe ,"images/salle_de_classe.png" , renderer, window, HAUTEUR , LARGEUR);
	aff_action(achat, renderer, window, texture_action1, texture_action2, texture_action3, texture_action4);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", renderer, window, OPTION_HAUTEUR, OPTION_LARGEUR);

	init_barre_depression(renderer, barre_depression);
	init_barre_sonore(renderer, barre_sonore);

	ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);
	ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

	SDL_RenderPresent(renderer);

	temps_jeu->debut(temps_jeu);

	pthread_create(&thread_minuteur, NULL, fonc_pthread_timer2_cb, parametre);


	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{

		SDL_Event event;//Créer un évènement

		while(SDL_PollEvent(&event))
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
								update_barre_sonore(renderer, barre_sonore, score);
								SDL_DestroyTexture(texture_barre_son);
								ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", renderer, window, BARRE_SON_X, BARRE_SON_Y);

								/*mise a jour de la barre de depression + remise en place de la texture associé*/
								update_barre_depression(renderer, barre_depression, barre_sonore, score);
								SDL_DestroyTexture(texture_barre_depression);
								ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", renderer, window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

								SDL_RenderPresent(renderer);
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
						status_menu = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_DestroyTexture(texture_menu_option);
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
	printf("tu quitte le cour de l'apres-midi\n");
	SDL_DestroyTexture(texture_action4);
	SDL_DestroyTexture(texture_action3);
	SDL_DestroyTexture(texture_action2);
	SDL_DestroyTexture(texture_action1);
	free(barre_sonore);
	free(barre_depression);
	SDL_DestroyTexture(texture_classe);
}
