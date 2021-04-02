#include "commun.h"
#include "lancement_jeu.h"
#include "self.h"



void textures(param_t *parametre, SDL_Texture *texture_self)
{
	ajout_texture(texture_self ,"images/self.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture_non_centre(texture_self , "images/btn_info.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);
	ajout_texture(texture_self, "images/bouton_suivant.png", (parametre->renderer), (parametre->window), HAUTEUR*1.85 , LARGEUR);
	ajout_texture_non_centre(texture_self, "images/plats/salade.png", (parametre->renderer), (parametre->window), 300, 350);
	ajout_texture_non_centre(texture_self, "images/plats/poulet.png", (parametre->renderer), (parametre->window), 415, 350);
	ajout_texture_non_centre(texture_self, "images/plats/steak.png", (parametre->renderer), (parametre->window), 530, 350);
	ajout_texture_non_centre(texture_self, "images/plats/kebab.png", (parametre->renderer), (parametre->window), 645, 350);
	ajout_texture_non_centre(texture_self, "images/plats/oeuf.png", (parametre->renderer), (parametre->window), 760, 350);
	ajout_texture_non_centre(texture_self, "images/plats/gateau.png", (parametre->renderer), (parametre->window), 875, 350);
	ajout_texture_non_centre(texture_self, "images/plats/bouteille.png", (parametre->renderer), (parametre->window), 928, 283);
	ajout_texture_non_centre(texture_self, "images/plats/bouteille.png", (parametre->renderer), (parametre->window), 961, 304);
}



void lancement_self(param_t *parametre)
{

	SDL_RenderClear((parametre->renderer));

	SDL_Texture *texture_self = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_menu_info = NULL;

	
	textures(parametre, texture_self);
	affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_info = 0;

	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{

		SDL_Event event;//Créer un évènement

		while(SDL_PollEvent(&event))
		{

			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("x : %i & y : %i\n", event.button.x, event.button.y);
					if((event.button.x > 535 && event.button.x < 747)&&(event.button.y > 367 && event.button.y < 413) && statut_mess == 1)
					{
						/*on clique sur continuer*/
						statut_mess = 0;
						
						SDL_RenderClear((parametre->renderer));
						textures(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));

						SDL_RenderPresent((parametre->renderer));

						
					}


					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0)
					{
						/*si on clique sur le bouton info*/
						statut_info = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_RenderClear((parametre->renderer));
						textures(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						ajout_texture(texture_menu_info ,"images/info.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x < COMPRIS_X_MAX && event.button.x > COMPRIS_X_MIN)&&(event.button.y < COMPRIS_Y_MAX && event.button.y > COMPRIS_Y_MIN) && statut_info == 1)
					{
						/*si on clique sur compris*/
						statut_info = 0;

						SDL_RenderClear((parametre->renderer));
						textures(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));

						SDL_RenderPresent((parametre->renderer));
					}


					if((event.button.x > BTN_SUIVANT_X_MIN && event.button.x < BTN_SUIVANT_X_MAX)&&(event.button.y > BTN_SUIVANT_Y_MIN && event.button.y < BTN_SUIVANT_Y_MAX) && statut_mess == 0 && statut_info == 0)
					{
						lancement((parametre->renderer), (parametre->window), (parametre->temps_jeu), 2, (parametre->argent));
					}
					break;
			}
		}
	}
}