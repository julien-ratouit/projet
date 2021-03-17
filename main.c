#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"
#include "coords.h"
#include "timer.h"
#include "barre.h"
#include "lancement_jeu.h"

int main (int argc, char ** argv)
{
	system("cls");
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Surface *image = NULL;

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_btn_jouer = NULL;
	SDL_Texture *texture_btn_option = NULL;

	Timer_t *temps_jeu;
	temps_jeu = timer_init();

	SDL_bool program_launched = SDL_TRUE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");

	if(SDL_CreateWindowAndRenderer(LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    	SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

	ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);

	//SDL_SetWindowIcon(SDL_Window* window, SDL_Surface* surface);

	SDL_RenderPresent(renderer);

	while(program_launched)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					//printf("x : %i\ny : %i\n\n", event.button.x, event.button.y);
					if((event.button.x < BOUTON_PLAY_X_MAX && event.button.x > BOUTON_PLAY_X_MIN)&&(event.button.y < BOUTON_PLAY_Y_MAX && event.button.y > BOUTON_PLAY_Y_MIN))
					{
						/*si on appuie sur le bouton jouer*/
						SDL_DestroyTexture(texture_btn_jouer);
						SDL_DestroyTexture(texture_menu);

						lancement(renderer, window, temps_jeu);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);

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
	SDL_DestroyTexture(texture_menu);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}