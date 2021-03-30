#include "commun.h"
#include "lancement_jeu.h"
#include "salle_prof.h"


void lancement_salle_prof(param_t *parametre)
{

	SDL_Texture *texture_salle_prof = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_menu_option = NULL;

	SDL_RenderClear((parametre->renderer));

	ajout_texture(texture_salle_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_opt = 0;

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

						ajout_texture(texture_salle_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_option , "images/option.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0)
					{
						/*si on clique sur le bouton option*/
						statut_opt = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_DestroyTexture(texture_menu_option);
						ajout_texture(texture_menu_option ,"images/menu_pause.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

						SDL_RenderPresent((parametre->renderer));
					}


					if((event.button.x < QUIT_X_MAX && event.button.x > QUIT_X_MIN)&&(event.button.y < QUIT_Y_MAX && event.button.y > QUIT_Y_MIN) && statut_opt == 1)
					{
						/*si on clique sur le bouton 'quitter le jeu'*/ 
						program_launched = SDL_FALSE;
					}

					if((event.button.x < REPRENDRE_X_MAX && event.button.x > REPRENDRE_X_MIN)&&(event.button.y < REPRENDRE_Y_MAX && event.button.y > REPRENDRE_Y_MIN) && statut_opt == 1)
					{
						/*si on clique sur reprendre*/
						statut_opt = 0;
						SDL_RenderClear((parametre->renderer));
						ajout_texture(texture_salle_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_option , "images/option.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}
					break;
					default: break;
			}
		}
	}
}