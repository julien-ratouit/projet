#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "fonction.h"

extern void SDL_ExitWithError(const char *message){ // Quitte le programme si ERREUR
  SDL_Log("ERREUR : %s > %s\n",message, SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}

extern void SDL_ExitImageWithError(const char *message, void * renderer, void * window){// Quitte le programme si ERREUR dans le rendu de l'image
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_ExitWithError(message);
}

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

    if(SDL_RenderCopy(renderer, texture, NULL, &dimension_image) != 0)
      SDL_ExitImageWithError("Impossible d'afficher la texture", renderer, window);
}

extern void ajout_texture_non_centre(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int x, int y){
  SDL_Surface *image = NULL;
  image = IMG_Load(lien_img);

    if(image == NULL)
        SDL_ExitImageWithError("L'image n'a pas été récupéré", renderer, window);

    texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);

    if(texture == NULL)
        SDL_ExitImageWithError("La texture n'a pas été créé", renderer, window);

    SDL_Rect dimension_image;
    SDL_QueryTexture(texture, NULL, NULL, &dimension_image.w, &dimension_image.h);

    dimension_image.x = x;
    dimension_image.y = y;

    if(SDL_RenderCopy(renderer, texture, NULL, &dimension_image) != 0)
      SDL_ExitImageWithError("Impossible d'afficher la texture", renderer, window);
}


extern int press_action(SDL_Renderer *renderer, int num_action){
  int i = -50;
  printf("Vous avez pressé l'action %i\n",num_action);

  return i;
}



