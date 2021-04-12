/**
* \file main.c
* \brief fonction principal du programme.
* \details c'est dans cette fonction que l'on initialise la SDL très utile pour notre projet, on initialise aussi la fenêtre et le rendu pour le reste de notre programme.
* \author Quenault Maxime, Ratouit Charles
*/

#include "commun.h"
#include "jeu_matin.h"
#include "jeu_apremidi.h"
#include "tuto.h"
#include "timer.h"
#include "barre.h"
#include "self.h"
#include "salle_prof.h"
#include "action.h"
/**
* \brief fonction main.
*
* \details Dans cette fonction le joueur à trois choix, soit commencer une nouvelle partie, soit reprendre sont anciènne sauvegarde si il y en a une, et pour finir il peut ausi
* acceder à une page "tuto" qui presente les specificité du jeu et donne des tips pour bien jouer.
* 
* \param temps_jeu est le timer de notre partie, on l'utilise dans le cours du matin et de l'après-midi.
* \param program_lauched est de type \a SDL_bool et permet de maintenir le programme en route, si jamais il passe à false alors on quitte le programme.
*  
*/

int main (int argc, char ** argv)
{
	system("cls");
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Surface *image = NULL;

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_btn_jouer = NULL;
	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_btn_tuto = NULL;
	SDL_Texture *texture_logo = NULL;

	Timer_t *temps_jeu;
	temps_jeu = timer_init();

	SDL_bool program_launched = SDL_TRUE;


	int status_tuto = -1;
	int argent = 200;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");

	if(SDL_CreateWindowAndRenderer(LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    	SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

	ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_btn_jouer ,"images/jouer.png" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_btn_tuto ,"images/tuto.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
	ajout_texture(texture_logo ,"images/logo.png" , renderer, window, HAUTEUR/2 , LARGEUR);

	param_t * parametre = malloc(sizeof(param_t));
	parametre->temps_jeu = temps_jeu;
	parametre->argent = argent;
	parametre->val_depression = -5;
	parametre->window = window;
	parametre->renderer = renderer;
	parametre->quitte = SDL_FALSE;
	parametre->perdu = SDL_FALSE;

	init_tab_action(action_equipe);
	init_tab_action(liste_action);
	SDL_RenderPresent(renderer);
	while(program_launched)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("x : %i\ny : %i\n\n", event.button.x, event.button.y);
					if((event.button.x < BOUTON_PLAY_X_MAX && event.button.x > BOUTON_PLAY_X_MIN)&&(event.button.y < BOUTON_PLAY_Y_MAX && event.button.y > BOUTON_PLAY_Y_MIN) && status_tuto == -1)
					{
						//si on appuie sur le bouton jouer
						
						SDL_DestroyTexture(texture_btn_jouer);
						SDL_DestroyTexture(texture_menu);
						SDL_DestroyTexture(texture_btn_tuto);

						while(!(parametre->quitte) && !(parametre->perdu))
						{

							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_matin(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_self(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_apremidi(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_salle_prof(parametre);

						}
										

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.png" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_tuto ,"images/tuto.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
						ajout_texture(texture_logo ,"images/logo.png" , renderer, window, HAUTEUR/2 , LARGEUR);

						parametre->quitte = SDL_FALSE;
						parametre->perdu = SDL_FALSE;

						SDL_RenderPresent(renderer);
					}
					if ((event.button.x < BOUTON_TUTO_X_MAX && event.button.x > BOUTON_TUTO_X_MIN)&&(event.button.y < BOUTON_TUTO_Y_MAX && event.button.y > BOUTON_TUTO_Y_MIN))
					{
						//si on appuie sur le bouton tuto

						tuto(renderer, window);

						SDL_RenderClear(renderer);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.png" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_tuto ,"images/tuto.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
						ajout_texture(texture_logo ,"images/logo.png" , renderer, window, HAUTEUR/2 , LARGEUR);
					
						SDL_RenderPresent(renderer);
					}
					break;

				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;

				default : break;
			}
		}
	}
	SDL_DestroyTexture(texture_btn_jouer);
	SDL_DestroyTexture(texture_btn_tuto);
	SDL_DestroyTexture(texture_menu);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}