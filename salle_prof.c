#include "commun.h"
#include "salle_prof.h"
#include "lancement_jeu.h"

void lancement_salle_prof(param_t *parametre)
{
	SDL_Texture *texture_salle_prof = NULL;

	SDL_RenderClear((parametre->renderer));
	ajout_texture(texture_salle_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

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
					if((event.button.x > 453 && event.button.x < 516)&&(event.button.y > 26 && event.button.y < 43))
					{
						printf("tu as bien cliqué pour quitter le jeu\n");
					}
					break;
			}
		}
	}
}