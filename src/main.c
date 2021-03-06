/**
* \file main.c
* \brief fonction principal du programme.
* \details c'est dans cette fonction que l'on initialise la SDL très utile pour notre projet, on initialise aussi la fenêtre et le rendu pour le reste de notre programme.
* \author Quenault Maxime, Ratouit Charles
*/

#include "../include/commun.h"
#include "../include/jeu_matin.h"
#include "../include/tuto.h"
#include "../include/timer.h"
#include "../include/barre.h"
#include "../include/self.h"
#include "../include/salle_prof.h"
#include "../include/action.h"
#include "../include/save.h"
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

	FILE * charge;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Surface *image = NULL;

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_bouton = NULL;
	SDL_Texture *texture_logo = NULL;

	Timer_t *temps_jeu;
	temps_jeu = timer_init();

	Timer_t *cd_action1;
	Timer_t *cd_action2;
	Timer_t *cd_action3;
	Timer_t *cd_action4;
	
	cd_action1 = timer_init();
	cd_action2 = timer_init();
	cd_action3 = timer_init();
	cd_action4 = timer_init();

	SDL_bool program_launched = SDL_TRUE;


	int status_tuto = -1;
	int argent = 5;
	bool antiOOM = true; //anti out of memory

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");

	if(SDL_CreateWindowAndRenderer(LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    	SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

	ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_bouton ,"images/boutons/jouer.png" , renderer, window, HAUTEUR , LARGEUR);

	if(charge = fopen("save.txt","r")){

		ajout_texture(texture_bouton ,"images/boutons/reprendre.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
		fclose(charge);
	}
		
	ajout_texture(texture_bouton ,"images/boutons/tuto.png", renderer, window, HAUTEUR*1.6, LARGEUR);
	ajout_texture(texture_logo ,"images/logo.png" , renderer, window, HAUTEUR/2 , LARGEUR);

	param_t * parametre = malloc(sizeof(param_t));
	
	SDL_RenderPresent(renderer);


	while(program_launched)
	{
		if (antiOOM == true)
		{
		ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
		ajout_texture(texture_bouton ,"images/boutons/jouer.png" , renderer, window, HAUTEUR , LARGEUR);
		ajout_texture(texture_bouton ,"images/boutons/reprendre.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
		ajout_texture(texture_bouton ,"images/boutons/tuto.png", renderer, window, HAUTEUR*1.6, LARGEUR);
		ajout_texture(texture_logo ,"images/logo.png" , renderer, window, HAUTEUR/2 , LARGEUR);

		antiOOM = false;
		parametre->temps_jeu = temps_jeu;
		parametre->cd_action1 = cd_action1;
		parametre->cd_action2 = cd_action2;
		parametre->cd_action3 = cd_action3;
		parametre->cd_action4 = cd_action4;
		parametre->argent = argent;
		parametre->nb_jour = 1;
		parametre->val_depression = -5;
		parametre->window = window;
		parametre->renderer = renderer;
		parametre->quitte = SDL_FALSE;
		parametre->perdu = SDL_FALSE;
		parametre->load = SDL_FALSE;

		init_tab_action(liste_action);
		action_equipe[0] = liste_action[0];
		action_equipe[1] = liste_action[1];
		action_equipe[2] = liste_action[2];
		action_equipe[3] = liste_action[3];
		liste_action[0]->equipe = 1;
		liste_action[0]->statut = true;

		SDL_RenderPresent(renderer);
		}
		
		SDL_Event event;

		while(SDL_PollEvent(&event) || parametre->load == SDL_TRUE)
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:

					if((event.button.x < BOUTON_PLAY_X_MAX && event.button.x > BOUTON_PLAY_X_MIN)&&(event.button.y < BOUTON_PLAY_Y_MAX && event.button.y > BOUTON_PLAY_Y_MIN) && status_tuto == -1)
					{
						//si on appuie sur le bouton jouer
						antiOOM = true;
						SDL_RenderClear(renderer);

						while(!(parametre->quitte) && !(parametre->perdu))
						{
							parametre->val_depression = -5;

							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_matin(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_self(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_matin(parametre);
							if(!(parametre->quitte) && !(parametre->perdu))
								lancement_salle_prof(parametre);
							parametre->nb_jour += 1;

						}
						if(parametre->perdu == SDL_TRUE){
							if(remove("save.txt") != 0)
								printf("Sauvegarde non effecté !\n");
						}
										
						parametre->quitte = SDL_FALSE;
						parametre->perdu = SDL_FALSE;

						SDL_RenderPresent(renderer);
					}

					if(((event.button.x < BTN_REP_X_MAX && event.button.x > BTN_REP_X_MIN)&&(event.button.y < BTN_REP_Y_MAX && event.button.y > BTN_REP_Y_MIN) && status_tuto == -1) || parametre->load == SDL_TRUE)
					{
						//si on clique sur reprendre
						antiOOM = true;
						if(charger(&(parametre->argent),&(parametre->nb_jour),liste_action,action_equipe)){
							SDL_RenderClear(renderer);

							while(!(parametre->quitte) && !(parametre->perdu))
							{
								parametre->val_depression = -5;

								if(!(parametre->quitte) && !(parametre->perdu))
									lancement_matin(parametre);
								if(!(parametre->quitte) && !(parametre->perdu))
									lancement_self(parametre);
								if(!(parametre->quitte) && !(parametre->perdu))
									lancement_matin(parametre);
								if(!(parametre->quitte) && !(parametre->perdu))
									lancement_salle_prof(parametre);
								parametre->nb_jour += 1;

							}
							if(parametre->perdu == SDL_FALSE){
								if(remove("save.txt") != 0)
									printf("Sauvegarde non effectué\n");
							}
							
							parametre->quitte = SDL_FALSE;
							parametre->perdu = SDL_FALSE;

							SDL_RenderPresent(renderer);


						}	
					}


					if ((event.button.x < BOUTON_TUTO_X_MAX && event.button.x > BOUTON_TUTO_X_MIN)&&(event.button.y < BOUTON_TUTO_Y_MAX && event.button.y > BOUTON_TUTO_Y_MIN))
					{
						//si on appuie sur le bouton tuto

						tuto(renderer, window);

						SDL_RenderClear(renderer);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_bouton ,"images/boutons/jouer.png" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_bouton ,"images/boutons/reprendre.png" , renderer, window, HAUTEUR*1.3, LARGEUR);
						ajout_texture(texture_bouton ,"images/boutons/tuto.png", renderer, window, HAUTEUR*1.6, LARGEUR);
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
	SDL_DestroyTexture(texture_bouton);
	SDL_DestroyTexture(texture_menu);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}