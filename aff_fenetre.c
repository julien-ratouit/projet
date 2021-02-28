#include <stdio.h>
#include <stdlib.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"
#include "jour.h"

#define HAUTEUR 600
#define LARGEUR 800

//temps en milliseconde
#define TIMER 2000

/*
* Rappel sur la compilation : gcc aff_fenetre.c -o bin/aff_fenetre -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/

int main (int argc, char ** argv)
{
	system("cls");
	SDL_Window *window = NULL;
	SDL_Window *window2 = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Renderer *renderer2 = NULL;
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	SDL_Texture *texture2 = NULL;
	SDL_Texture *texture3 = NULL;
	SDL_bool program_launched = SDL_TRUE;
	SDL_DisplayMode dm;
	int verif_exist = 0;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithFailure("Initialisation SDL");


	window = SDL_CreateWindow("Ma première Fenêtre"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
	if(window == NULL)
		SDL_ExitWithFailure("Creation fenetre echoue");

	renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
	if(renderer == NULL)
		SDL_ExitWithFailure("Creation renu echoue");

	ajout_texture(texture ,"images/fond.bmp" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture2 ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);

	SDL_RenderPresent(renderer);

	while(program_launched)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;
				

				case SDL_MOUSEBUTTONDOWN:
					//printf("x : %i\ny : %i", event.button.x, event.button.y);
					if((event.button.x < 475 && event.button.x > 325)&&(event.button.y < 328 && event.button.y > 270) && verif_exist == 0)
					{
						printf("tu as clique sur bouton jouer\n");
						verif_exist = 1;
						SDL_DestroyTexture(texture2);						
						SDL_DestroyTexture(texture);
						SDL_DestroyRenderer(renderer);
					
						renderer2 = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer2 == NULL)
							SDL_ExitWithFailure("Creation renu echoue");

						ajout_texture(texture3 ,"images/message.bmp" , renderer2, window, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);	
					
						compteur(TIMER);
					
						SDL_DestroyTexture(texture3);
						SDL_DestroyRenderer(renderer2);
						verif_exist = 0;
						

						renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer == NULL)
							SDL_ExitWithFailure("Creation renu echoue");

						ajout_texture(texture ,"images/fond.bmp" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture2 ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);

						SDL_RenderPresent(renderer);
					}
					break;

				default : break;
			}
		}
	}
	SDL_DestroyTexture(texture3);
	SDL_DestroyRenderer(renderer2);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}