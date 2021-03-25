#include "commun.h"
#include "tuto.h"

void tuto(SDL_Renderer *renderer, SDL_Window *window)
{
	int page = 1; 

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_tuto = NULL;
	SDL_bool program_launched = SDL_TRUE; 
	
	ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR);
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
						if((event.button.x < FERMER_TUTO_X_MAX && event.button.x > FERMER_TUTO_X_MIN)&&(event.button.y < FERMER_TUTO_Y_MAX && event.button.y > FERMER_TUTO_Y_MIN)/* && status_tuto == 1*/)
						{
							/*si on clique sur la croix*/
							program_launched = SDL_FALSE;
						}	
						if((event.button.x < NEXT_TUTO_X_MAX && event.button.x > NEXT_TUTO_X_MIN)&&(event.button.y < NEXT_TUTO_Y_MAX && event.button.y > NEXT_TUTO_Y_MIN))
						{
							/*si on clique sur le tuto*/
							
							page++;

							SDL_SetRenderTarget(renderer, NULL);// Dorénavent, on modifie à nouveau le renderer

							switch(page)
							{
								case 1:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 2:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 3:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								default: program_launched = SDL_FALSE;
							}

							SDL_RenderPresent(renderer);
						}	
						if((event.button.x < PREV_TUTO_X_MAX && event.button.x > PREV_TUTO_X_MIN)&&(event.button.y < PREV_TUTO_Y_MAX && event.button.y > PREV_TUTO_Y_MIN) && page < 1)
						{
							/*si on clique sur le tuto*/
							
							page--;

							SDL_SetRenderTarget(renderer, NULL);// Dorénavent, on modifie à nouveau le renderer

							switch(page)
							{
								case 1:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 2:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 3:ajout_texture(texture_tuto ,"images/tuto-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								default: printf("ça a bugué\n"); break;
							}

							SDL_RenderPresent(renderer);
						}	
						break;

					default : break;
				}
		}
	}
}