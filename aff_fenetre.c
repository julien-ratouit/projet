#include <stdio.h>
#include <stdlib.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"

#define HAUTEUR 600
#define LARGEUR 800

/*
* Rappel sur la compilation : gcc aff_fenetre.c -o bin/aff_fenetre -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
*/

int main (int argc, char ** argv)
{
	/*Déclaration des varaibles*/
	/*<------------------------------------------------>*/
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

	/*<------------------------------------------------>*/



	/*Initialisation*/
	/*<------------------------------------------------>*/
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithFailure("Initialisation SDL");
	/*<------------------------------------------------>*/


	/*Créations*/
	/*<------------------------------------------------>*/
	//Création de la fenêtre
	window = SDL_CreateWindow("Ma première Fenêtre"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
	if(window == NULL)
		SDL_ExitWithFailure("Creation fenetre echoue");

	
	//Création d'un rendu
	renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
	if(renderer == NULL)
		SDL_ExitWithFailure("Creation renu echoue");

	//Création d'une couleur de pinceau pour dessiner sur sa fenêtre
	if(SDL_SetRenderDrawColor(renderer/*nom du rendu*/, 112/*taux Rouge*/, 168/*taux de vert*/, 237/*taux de bleu*/, SDL_ALPHA_OPAQUE/*constante qui vaut 255, elle gere la transparance*/) != 0)
		SDL_ExitWithFailure("Impossible de charger la couleur");
	/*<------------------------------------------------>*/

	//Dessiner un point
	//if(SDL_RenderDrawPoint(renderer/*nom du rendu*/, 100/* val X*/, 400/*val Y*/) != 0)
		//SDL_ExitWithFailure("Impossible de dessiner un point");

	//Dessine une ligne
	//if(SDL_RenderDrawLine(renderer/*nom du rendu*/, 50/* val X1*/, 50/*val Y1*/, 500/* val X2*/, 500/*val Y2*/) != 0)
		//SDL_ExitWithFailure("Impossible de dessiner une ligne");

	//Dessine un rectangle

	/*SDL_Rect rectanglePlein;
	rectanglePlein.x = 500;
	rectanglePlein.y = 50;
	rectanglePlein.w = 100;
	rectanglePlein.h = 50;

	SDL_Rect rectangleVide;
	rectangleVide.x = 500;
	rectangleVide.y = 150;
	rectangleVide.w = 100;
	rectangleVide.h = 50;*/

	//if(SDL_RenderFillRect(renderer/*nom du rendu*/, &rectanglePlein) != 0)
		//SDL_ExitWithFailure("Impossible de dessiner un rectangle");
	//if(SDL_RenderDrawRect(renderer/*nom du rendu*/, &rectangleVide) != 0)
		//SDL_ExitWithFailure("Impossible de dessiner un rectangle");

	//SDL_GetCurrentDisplayMode(0, &dm);
	//int SCREEN_HEIGHT = dm.h;
	//int SCREEN_WIDTH = dm.w;

	/*PREMIERE TEXTURE*/
	/*<------------------------------------------------>*/
	image = IMG_Load("images/fond.bmp");

	if(image == NULL)
		SDL_ExitImageWithError("L'image n'as pas été récupéré", renderer, window);

	texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

	if(texture == NULL)
		SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

	SDL_Rect dimension_image;
	SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

	dimension_image.x = (LARGEUR - dimension_image.w) / 2;
	dimension_image.y = (HAUTEUR - dimension_image.h) / 2;

	SDL_RenderCopy(renderer, texture, NULL, &dimension_image);
	/*<------------------------------------------------>*/

	/*DEUXIEME TEXTURE*/
	/*<------------------------------------------------>*/
	image = IMG_Load("images/jouer.bmp");

	if(image == NULL)
		SDL_ExitImageWithError("L'image \"jouer\" n'as pas été récupéré", renderer, window);

	texture2 = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

	if(texture2 == NULL)
		SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

	SDL_Rect dimension_image2;
	SDL_QueryTexture(texture2, NULL, NULL, &dimension_image2.w, &dimension_image2.h);

	dimension_image2.x = (LARGEUR - dimension_image2.w) / 2;
	dimension_image2.y = (HAUTEUR - dimension_image2.h) / 2;

	SDL_RenderCopy(renderer, texture2, NULL, &dimension_image2);
	/*<------------------------------------------------>*/

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
					if((event.button.x < 475 && event.button.x > 325)&&(event.button.y < 328 && event.button.y > 270))
					{
						SDL_DestroyTexture(texture2);
						//on detruit la texture
						SDL_DestroyTexture(texture);
						//on detruit le rendu
						SDL_DestroyRenderer(renderer);
						//on detruit la fenetre
						SDL_DestroyWindow(window);
						//printf("tu as cliquer sur le bouton jouer\n");
						window2 = SDL_CreateWindow("Survive Student"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
						if(window2 == NULL)
							SDL_ExitWithFailure("Creation deuxieme fenetre echoue");
						renderer2 = SDL_CreateRenderer(window2/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer2 == NULL)
							SDL_ExitWithFailure("Creation renu echoue");
						image = IMG_Load("images/message.bmp");

						if(image == NULL)
							SDL_ExitImageWithError("L'image \"message\" n'as pas été récupéré", renderer, window);

						texture3 = SDL_CreateTextureFromSurface(renderer2, image);

						SDL_FreeSurface(image);

						if(texture3 == NULL)
							SDL_ExitImageWithError("La texture3 n'as pas été créé", renderer, window);

						SDL_Rect dimension_image3;
						SDL_QueryTexture(texture3, NULL, NULL, &dimension_image3.w, &dimension_image3.h);

						dimension_image3.x = (LARGEUR - dimension_image2.w) / 2;
						dimension_image3.y = (HAUTEUR - dimension_image2.h) / 2;
						SDL_RenderCopy(renderer2, texture3, NULL, &dimension_image3);
						SDL_RenderPresent(renderer2);	
					}
					if((event.button.x < 591 && event.button.x > 457)&&(event.button.y < 555 && event.button.y > 526))
					{
						//printf("Tu as cliquer sur le bouton revenir a accueille");
						SDL_DestroyTexture(texture3);
						SDL_DestroyRenderer(renderer2);
						SDL_DestroyWindow(window2);
						//Création de la fenêtre
						window = SDL_CreateWindow("Ma première Fenêtre"/*nom*/, SDL_WINDOWPOS_CENTERED/*pos du X*/, SDL_WINDOWPOS_CENTERED/*pos du Y*/, LARGEUR/*largeur*/, HAUTEUR/*hauteur*/, SDL_WINDOW_SHOWN/*differentes options d'affichages*/);
						if(window == NULL)
							SDL_ExitWithFailure("Creation fenetre echoue");

	
						//Création d'un rendu
						renderer = SDL_CreateRenderer(window/*la fenêtre concerné*/, -1/*cherche pas à comprendre*/, SDL_RENDERER_SOFTWARE/*differentes options*/);
						if(renderer == NULL)
							SDL_ExitWithFailure("Creation renu echoue");

						/*PREMIERE TEXTURE*/
						/*<------------------------------------------------>*/
						image = IMG_Load("images/fond.bmp");

						if(image == NULL)
							SDL_ExitImageWithError("L'image n'as pas été récupéré", renderer, window);

						texture = SDL_CreateTextureFromSurface(renderer, image);

						SDL_FreeSurface(image);

						if(texture == NULL)
							SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

						SDL_Rect dimension_image;
						SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

						dimension_image.x = (LARGEUR - dimension_image.w) / 2;
						dimension_image.y = (HAUTEUR - dimension_image.h) / 2;

						SDL_RenderCopy(renderer, texture, NULL, &dimension_image);
						/*<------------------------------------------------>*/

						/*DEUXIEME TEXTURE*/
						/*<------------------------------------------------>*/
						image = IMG_Load("images/jouer.bmp");

						if(image == NULL)
							SDL_ExitImageWithError("L'image \"jouer\" n'as pas été récupéré", renderer, window);

						texture2 = SDL_CreateTextureFromSurface(renderer, image);

						SDL_FreeSurface(image);

						if(texture2 == NULL)
							SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

						SDL_Rect dimension_image2;
						SDL_QueryTexture(texture2, NULL, NULL, &dimension_image2.w, &dimension_image2.h);

						dimension_image2.x = (LARGEUR - dimension_image2.w) / 2;
						dimension_image2.y = (HAUTEUR - dimension_image2.h) / 2;

						SDL_RenderCopy(renderer, texture2, NULL, &dimension_image2);
						SDL_RenderPresent(renderer);
					}

					break;
				

				default : break;
			}
		}

	}


	/*Déstructions*/
	/*<------------------------------------------------>*/
	SDL_DestroyTexture(texture2);
	//on detruit la texture
	SDL_DestroyTexture(texture);
	//on detruit le rendu
	SDL_DestroyRenderer(renderer);
	//on detruit la fenetre
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture3);
	SDL_DestroyRenderer(renderer2);
	SDL_DestroyWindow(window2);
	//On quitte la SDL
	SDL_Quit();
	/*<------------------------------------------------>*/


	return EXIT_SUCCESS;
}