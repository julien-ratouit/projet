#include "commun.h"
#include "lancement_jeu.h"
#include "salle_prof.h"


void textures_sp(param_t *parametre, SDL_Texture *texture_prof)
{
	ajout_texture(texture_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture(texture_prof, "images/btn_restart.png", (parametre->renderer), (parametre->window), HAUTEUR*1.8 , LARGEUR*1.5);
	ajout_texture(texture_prof, "images/btn_save.png", (parametre->renderer), (parametre->window), HAUTEUR*1.835 , LARGEUR/1.75);
	ajout_texture_non_centre(texture_prof , "images/btn_info.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);
	affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
}


void lancement_salle_prof(param_t *parametre)
{

	(parametre->argent) += 5;

	SDL_Texture *texture_prof = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_menu_info = NULL;

	SDL_RenderClear((parametre->renderer));

	textures_sp(parametre, texture_prof);
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_info = 0;

	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{

		SDL_Event event;

		while(SDL_PollEvent(&event))
		{

			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					//printf("x : %i & y : %i\n", event.button.x, event.button.y);
					if((event.button.x > 535 && event.button.x < 747)&&(event.button.y > 367 && event.button.y < 413) && statut_mess == 1)
					{
						statut_mess = 0;
						
						SDL_RenderClear((parametre->renderer));

						textures_sp(parametre, texture_prof);

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0)
					{
						//si on clique sur le bouton info

						statut_info = 1;
						SDL_RenderClear((parametre->renderer));

						textures_sp(parametre, texture_prof);
						ajout_texture(texture_menu_info ,"images/info2.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

						SDL_RenderPresent((parametre->renderer));

					}

					if((event.button.x < COMPRIS_X_MAX && event.button.x > COMPRIS_X_MIN)&&(event.button.y < COMPRIS_Y_MAX && event.button.y > COMPRIS_Y_MIN) && statut_info == 1)
					{
						//si on clique sur le bouton compris

						statut_info = 0;

						SDL_RenderClear((parametre->renderer));

						textures_sp(parametre, texture_prof);

						SDL_RenderPresent((parametre->renderer));

					}

					if((event.button.x > BTN_RESTART_X_MIN && event.button.x < BTN_RESTART_X_MAX)&&(event.button.y > BTN_RESTART_Y_MIN && event.button.y < BTN_RESTART_Y_MAX) && statut_mess == 0)
					{
						//on clique sur bouton pour commencer une nouvelle journee

						printf("tu as clique sur le bouton restart\n");
						lancement((parametre->renderer), (parametre->window), (parametre->temps_jeu), 1, (parametre->argent));
					}

					if((event.button.x > BTN_SAVE_X_MIN && event.button.x < BTN_SAVE_X_MAX)&&(event.button.y > BTN_SAVE_Y_MIN && event.button.y < BTN_SAVE_Y_MAX) && statut_mess == 0)
					{
						//on clique pour sauvegarder et quitter

						printf("tu as clique sur le bouton save\n");
						program_launched = SDL_FALSE;
					}

					break;
				default: 
					break;
			}
		}
	}
}