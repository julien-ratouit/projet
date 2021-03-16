#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"
#include "jour.h"
#include "coords.h"
#include "timer.h"
#include "barre.h"
#include "lancement_jeu.h"

/*
* Rappel sur la compilation : gcc aff_fenetre.c -o bin/aff_fenetre -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/
#define TIMER 2000

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

	SDL_bool program_launched = SDL_TRUE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");

	if(SDL_CreateWindowAndRenderer(LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    	SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

	ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_HAUTEUR , TUTO_LARGEUR);

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
						SDL_DestroyTexture(texture_btn_tuto);

						lancement(renderer, window);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_HAUTEUR , TUTO_LARGEUR);

						SDL_RenderPresent(renderer);
					}
					else if ((event.button.x < BOUTON_TUTO_X_MAX && event.button.x > BOUTON_TUTO_X_MIN)&&(event.button.y < BOUTON_TUTO_Y_MAX && event.button.y > BOUTON_TUTO_Y_MIN))
					{
						/*si on appuie sur le bouton tuto*/
						SDL_DestroyTexture(texture_btn_jouer);
						SDL_DestroyTexture(texture_menu);
						SDL_DestroyTexture(texture_btn_tuto);

						lancement(renderer, window);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_HAUTEUR , TUTO_LARGEUR);

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