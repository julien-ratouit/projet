#include <stdio.h>
#include <stdlib.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"

//Cette fonction me permet d'arrêter le programme si les choses se passe mal
extern void SDL_ExitWithFailure(const char *message)
{
	SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

// Quitte le programme si ERREUR dans le rendu de l'image
extern void SDL_ExitImageWithError(const char *message, void * renderer, void * window)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_ExitWithFailure(message);
}