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

/*
* Rappel sur la compilation : gcc aff_fenetre.c -o bin/aff_fenetre -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/
#define TIMER 2000

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

	SDL_Rect *barre_sonor = NULL;
	SDL_Rect *barre_depression = NULL;
	int verif_exist = 0;
	int *achat = malloc(sizeof(int));
	int *depression = malloc(sizeof(int));
	Timer_t * temps_jeu = timer_init();

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");


	window = SDL_CreateWindow("Ma première Fenêtre"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
	if(window == NULL)
		SDL_ExitWithError("Creation fenetre echoue");

	renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
	if(renderer == NULL)
		SDL_ExitWithError("Creation renu echoue");

	ajout_texture(texture ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
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
					printf("x : %i\ny : %i\n\n", event.button.x, event.button.y);
					if((event.button.x < BOUTON_PLAY_X_MAX && event.button.x > BOUTON_PLAY_X_MIN)&&(event.button.y < BOUTON_PLAY_Y_MAX && event.button.y > BOUTON_PLAY_Y_MIN) && verif_exist == 0)
					{
						
						//printf("tu as clique sur bouton jouer\n");
						verif_exist = 1;
						SDL_DestroyTexture(texture2);						
						SDL_DestroyTexture(texture);
						SDL_DestroyRenderer(renderer);
						SDL_DestroyWindow(window);

						window2 = SDL_CreateWindow("Survive Student", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);
						if(window2 == NULL)
							SDL_ExitWithError("Creation fenetre echoue");
					
						renderer2 = SDL_CreateRenderer(window2/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer2 == NULL)
							SDL_ExitWithError("Creation renu echoue");

						ajout_texture(texture3 ,"images/salle_de_classe.png" , renderer2, window2, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);
						*achat = 5;
						*depression = 0;

						timer_debut(temps_jeu);
						while(timer_get_ticks(temps_jeu) <= 5000)
						{
							/*init_barre_sonore(renderer2, barre_sonor);
							init_barre_depression(renderer2, barre_depression);*/
							journee_complete(achat, depression, renderer2, window2);
						}
						while(timer_get_ticks(temps_jeu) > 5000 && timer_get_ticks(temps_jeu) <= 10000)
						{
							ajout_texture(texture3, "images/self.png", renderer2, window2, HAUTEUR , LARGEUR);
							SDL_RenderPresent(renderer2);
						}
						while(timer_get_ticks(temps_jeu) > 5000 && timer_get_ticks(temps_jeu) <= 10000)
						{
							ajout_texture(texture3, "images/salle_de_classe.png", renderer2, window2, HAUTEUR , LARGEUR);
							SDL_RenderPresent(renderer2);
							journee_complete(achat, depression, renderer2, window2);
						}
						while(timer_get_ticks(temps_jeu) > 10000 && timer_get_ticks(temps_jeu) <= 15000)
						{
							ajout_texture(texture3, "images/salle_prof.png", renderer2, window2, HAUTEUR , LARGEUR);
							SDL_RenderPresent(renderer2);
						}
						SDL_DestroyTexture(texture3);
						SDL_DestroyRenderer(renderer2);
						SDL_DestroyWindow(window2);

						window = SDL_CreateWindow("Ma première Fenêtre"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
						if(window == NULL)
							SDL_ExitWithError("Creation fenetre echoue");

						renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer == NULL)
							SDL_ExitWithError("Creation renu echoue");

						ajout_texture(texture ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture2 ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);

						SDL_RenderPresent(renderer);

					}
					/*if((event.button.x < 1236 && event.button.x > 1184)&&(event.button.y < 417 && event.button.y > 177) && verif_exist == 1)
					{
						ajout_texture(texture3, "images/self.png", renderer2, window2, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);
					}
					if((event.button.x < 524 && event.button.x > 448)&&(event.button.y < 49 && event.button.y > 17) && verif_exist == 1)
					{
						ajout_texture(texture3, "images/salle_de_classe.png", renderer2, window2, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);
					}
					if((event.button.x < 280 && event.button.x > 145)&&(event.button.y < 390 && event.button.y > 311) && verif_exist == 1)
					{
						ajout_texture(texture3, "images/salle_prof.png", renderer2, window2, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);
					}
					if((event.button.x < 419 && event.button.x > 167)&&(event.button.y < 217 && event.button.y > 12) && verif_exist == 1)
					{
						ajout_texture(texture3, "images/salle_de_classe.png", renderer2, window2, HAUTEUR , LARGEUR);
						SDL_RenderPresent(renderer2);
					}*/
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