#include "commun.h"
#include "lancement_jeu.h"
#include "self.h"




void lancement_self(param_t *parametre)
{

	SDL_Texture *texture_self = NULL;

	SDL_RenderClear((parametre->renderer));
	ajout_texture(texture_self ,"images/self.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

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
					//printf("x : %i & y : %i\n", event.button.x, event.button.y);
					if((event.button.x > 453 && event.button.x < 516)&&(event.button.y > 26 && event.button.y < 43))
					{
						lancement((parametre->renderer), (parametre->window), (parametre->temps_jeu), 2);
					}
					break;
			}
		}
	}
}