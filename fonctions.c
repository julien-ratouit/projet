#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "fonctions.h"

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

extern void aff_action(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture_action1, SDL_Texture *texture_action2, SDL_Texture *texture_action3, SDL_Texture *texture_action4, int nb_action_acheter){

  if(nb_action_acheter >= 1)
    ajout_texture_non_centre(texture_action1, "img/bonton.png", renderer, window, 70, 530);
  if(nb_action_acheter >= 2)
    ajout_texture_non_centre(texture_action1, "img/bonton.png", renderer, window, 155, 530);
  if(nb_action_acheter >= 3)
    ajout_texture_non_centre(texture_action1, "img/bonton.png", renderer, window, 45, 615);
  if(nb_action_acheter >= 4)
    ajout_texture_non_centre(texture_action1, "img/bonton.png", renderer, window, 130, 615);

  SDL_RenderPresent(renderer);
}

extern int press_action(SDL_Renderer *renderer, int num_action){
  int i = -50;
  printf("Vous avez pressé l'action %i\n",num_action);

  return i;
}

//Initialisation de la barre sonore
extern void init_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre){

  SDL_Rect contour_barre;
  contour_barre.x = 250;
  contour_barre.y = 15;
  contour_barre.w = 50;
  contour_barre.h = 250;

  (*barre).x = 251;
  (*barre).y = 264;
  (*barre).w = 48;
  (*barre).h = -5;

  if(SDL_SetRenderDrawColor(renderer, 50, 50, 150, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderFillRect(renderer, barre) != 0)//Pour dessiner un rectangle remplit
    SDL_ExitWithError("Impossible de dessiner un rectange");

  if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)//changer la couleur du dessin
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderDrawRect(renderer, &contour_barre) != 0)//Pour dessiner un rectangle
    SDL_ExitWithError("Impossible de dessiner un rectange");

}
//Initialisation de la barre de depression
extern void init_barre_depression(SDL_Renderer *renderer, SDL_Rect *barre){

  SDL_Rect contour_barre;
  contour_barre.x = 1065;
  contour_barre.y = 15;
  contour_barre.w = 50;
  contour_barre.h = 250;

  (*barre).x = 1066;
  (*barre).y = 264;
  (*barre).w = 48;
  (*barre).h = -5;

  if(SDL_SetRenderDrawColor(renderer, 240, 130, 5, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderFillRect(renderer, barre) != 0)//Pour dessiner un rectangle remplit
    SDL_ExitWithError("Impossible de dessiner un rectange");

  if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)//changer la couleur du dessin
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderDrawRect(renderer, &contour_barre) != 0)//Pour dessiner un rectangle
    SDL_ExitWithError("Impossible de dessiner un rectange");

}
//Mise à jour de la barre sonore
extern void update_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre, int score){
  int tempo = 0;
  //printf("Score de la barre sonore : %i et score : %i\n", (*barre).h, score);
  if((*barre).h-score > -248 && score > 0){
    (*barre).h = (*barre).h-score;
    printf("INCREMENTATION\n");
  }
  else if((*barre).h-score <= -248 && score > 0){
    (*barre).h = -248;
    printf("FULL\n");
  }
  else if(score < 0){
    (*barre).y = (*barre).y + (*barre).h;
    if((*barre).h-score >= -5){
      (*barre).h = 264 - (*barre).y - 5;
      printf("VIDE\n");
    }
    else{
      tempo = (*barre).h;
      (*barre).h = -score;
      printf("DECREMENTATION et tempo = %i et h= %i\n",tempo ,(*barre).h);
    }
  }

  if(score > 0 || (*barre).h == -5){
    if(SDL_SetRenderDrawColor(renderer, 50, 50, 150, SDL_ALPHA_OPAQUE) != 0)
      SDL_ExitWithError("Impossible de changer la couleur du rendu");
  }
  else{
    if(SDL_SetRenderDrawColor(renderer, 153, 147, 137, SDL_ALPHA_OPAQUE) != 0)
      SDL_ExitWithError("Impossible de changer la couleur du rendu");
  }


  if(SDL_RenderFillRect(renderer, barre) != 0)//Pour dessiner un rectangle remplit
    SDL_ExitWithError("Impossible de dessiner un rectange");

  SDL_RenderPresent(renderer);
  if(score < 0 ){
    if(tempo-score >= -5){
      (*barre).h = -5;
    }
    else{
      printf("test tempo score\n");
      (*barre).h = tempo - score;
    }
    (*barre).y = 264;
  }
  printf("%i\n",(*barre).h);
}
//Mise à jour de la barre de depression
extern void update_barre_depression(SDL_Renderer *renderer, SDL_Rect *barre_depression, SDL_Rect *barre_sonore, int score){

  //printf("Score de la barre de depression : %i et score : %i\n", (*barre_depression).h, score);
  if((*barre_sonore).h == -248 && ((*barre_depression).h-score/2) > -248){
    (*barre_depression).h = (*barre_depression).h - score/2;
  }
  else if(((*barre_depression).h-score/2) < -248){
    (*barre_depression).h = -248;
    //printf("DEPRESSION BARRE IS FULL\n");
  }

  if(SDL_SetRenderDrawColor(renderer, 240, 130, 5, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderFillRect(renderer, barre_depression) != 0)//Pour dessiner un rectangle remplit
    SDL_ExitWithError("Impossible de dessiner un rectange");

  SDL_RenderPresent(renderer);
}
