#include <time.h>
#include <pthread.h>
#include "commun.h"
#include "timer.h"
#include "barre.h"
#include "lancement_jeu.h"

////////////////////////////////////
void func_barre(param_barre_t *barre_param){

	int nb_jour = 3;
	int agit = 2;
	printf("bou2\n");
	/*marche pas-------------------------------
	int temps;
	temps = rand()%(2000-200+1)+200;
	SDL_Delay(temps);
	printf("temps:%d\n", temps);*/
	SDL_Delay(500);
	if((*barre_param->barre_depression).h>(-250))
	{

		//mise a jour de la barre sonore + remise en place de la texture associé
		update_barre_sonore(barre_param->rendu, barre_param->barre_sonore, agit);
		SDL_DestroyTexture(barre_param->texture_barre_son_pthread);
		ajout_texture_non_centre(barre_param->texture_barre_son_pthread, "images/barre_son_depression.png", barre_param->rendu, barre_param->fenetre, BARRE_SON_X, BARRE_SON_Y);

		//mise a jour de la barre de depression + remise en place de la texture associé
		update_barre_depression(barre_param->rendu, barre_param->barre_depression, barre_param->barre_sonore, agit);
		SDL_DestroyTexture(barre_param->texture_barre_depression_pthread);
		ajout_texture_non_centre(barre_param->texture_barre_depression_pthread, "images/barre_son_depression.png", barre_param->rendu, barre_param->fenetre, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

		SDL_RenderPresent(barre_param->rendu);
	}
	pthread_exit(NULL);
}
//////////////////////////////////////
void *func_barre_cb(void* params){
	func_barre(params);
}

void lancement(SDL_Renderer *renderer, SDL_Window *window, Timer_t * temps_jeu, int argent)
{
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
	int score = 0;
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
    //----------PTHREAD----------------------------------------------------
	barre_param->barre_depression = barre_depression;
	barre_param->barre_sonore = barre_sonore;

	barre_param->texture_barre_son_pthread = texture_barre_son;
	barre_param->texture_barre_depression_pthread = texture_barre_depression;
	
	pthread_t b_sonnor;

	pthread_create(&b_sonnor, NULL, func_barre_cb, barre_param);
	/*----------------------------------------------------------------------*/
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{

		SDL_Event event;//Créer un évènement
		pthread_join(b_sonnor, NULL);
		if (status_menu != 1)
		{
			pthread_create(&b_sonnor, NULL, func_barre_cb, barre_param);
		}
	
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
