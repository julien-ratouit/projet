/**
* \file tuto.c
* \brief Ensemble de fonction qui gère la page du tuto.
* \details c'est dans cette fonction que l'on gère l'affichage et les zones de cliques liées à la page du tuto.
* \author Ratouit Julien
*/

#include "../include/commun.h"
#include "../include/tuto.h"


/**
* \brief fonction qui gère le tuto.
*
* \details Dans cette fonction nous affichonsles textures liées a la page tuto de notre jeu, le joueur à la possibilité de quitter le tuto en cliquant sur la croix en haute à gauche,
* il peut aussi naviguer entre les pages avec un bouton next et pred. Une fois arrivé à la dernière page le bouton nexte se transforme en bouton pour quitter le tuto.
* 
* \param page est un entier de type \a int qui nous permet de savoir sur qu'elle page du tuto on se trouve.
*  
*/
void tuto(SDL_Renderer *renderer, SDL_Window *window)
{
	int page = 1; 

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_tuto = NULL;
	SDL_bool program_launched = SDL_TRUE; 
	
	ajout_texture(texture_tuto ,"images/tuto1-600-900.png" , renderer, window, HAUTEUR , LARGEUR);
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
								case 1:ajout_texture(texture_tuto ,"images/tuto1-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 2:ajout_texture(texture_tuto ,"images/tuto2-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 3:ajout_texture(texture_tuto ,"images/tuto3-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
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
								case 1:ajout_texture(texture_tuto ,"images/tuto1-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 2:ajout_texture(texture_tuto ,"images/tuto2-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
								case 3:ajout_texture(texture_tuto ,"images/tuto3-600-900.png" , renderer, window, HAUTEUR , LARGEUR); break;
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