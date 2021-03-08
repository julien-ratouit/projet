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

// Créer une texture centré
extern void ajout_texture(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur){
  SDL_Surface *image = NULL;
  image = IMG_Load(lien_img);

    if(image == NULL)
        SDL_ExitImageWithError("L'image n'as pas été récupéré", renderer, window);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if(texture == NULL)
        SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

    SDL_Rect dimension_image;
    SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

    dimension_image.x = (largeur - dimension_image.w) / 2;
    dimension_image.y = (hauteur - dimension_image.h) / 2;

    SDL_RenderCopy(renderer, texture, NULL, &dimension_image);
}

//ajoute une texture non centré
extern void ajout_texture_non_centre(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur){
  SDL_Surface *image = NULL;
  image = IMG_Load(lien_img);

    if(image == NULL)
        SDL_ExitImageWithError("L'image n'as pas été récupéré", renderer, window);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if(texture == NULL)
        SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

    SDL_Rect dimension_image;
    SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

    dimension_image.x = largeur;
    dimension_image.y = hauteur; 

    SDL_RenderCopy(renderer, texture, NULL, &dimension_image);
}

//ajoute une texture non centré
extern void ajout_texture_non_centre(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur){
  SDL_Surface *image = NULL;
  image = IMG_Load(lien_img);

    if(image == NULL)
        SDL_ExitImageWithError("L'image n'as pas été récupéré", renderer, window);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if(texture == NULL)
        SDL_ExitImageWithError("La texture n'as pas été créé", renderer, window);

    SDL_Rect dimension_image;
    SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

    dimension_image.x = largeur;
    dimension_image.y = hauteur; 

    SDL_RenderCopy(renderer, texture, NULL, &dimension_image);
  free(image);
  image = NULL;
}
