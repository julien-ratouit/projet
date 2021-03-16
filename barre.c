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

//Initialisation de la barre sonore
extern void init_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre){

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

}
//Initialisation de la barre de depression
extern void init_barre_depression(SDL_Renderer *renderer, SDL_Rect *barre){

  (*barre).x = 1066;
  (*barre).y = 264;
  (*barre).w = 48;
  (*barre).h = -5;

  if(SDL_SetRenderDrawColor(renderer, 240, 130, 5, SDL_ALPHA_OPAQUE) != 0)
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

  if(SDL_RenderFillRect(renderer, barre) != 0)//Pour dessiner un rectangle remplit
  	SDL_ExitWithError("Impossible de dessiner un rectangle");

  if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)//changer la couleur du dessin
    SDL_ExitWithError("Impossible de changer la couleur du rendu");

}
//Mise à jour de la barre sonore
extern void update_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre, int score){
  int tempo = 0;
  //printf("Score de la barre sonore : %i et score : %i\n", (*barre).h, score);
  if((*barre).h-score > -248 && score > 0){
    (*barre).h = (*barre).h-score;
    //printf("INCREMENTATION\n");
  }
  else if((*barre).h-score <= -248 && score > 0){
    (*barre).h = -248;
    //printf("FULL\n");
  }
  else if(score < 0){
    (*barre).y = (*barre).y + (*barre).h;
    if((*barre).h-score >= -5){
      (*barre).h = 264 - (*barre).y - 5;
      //printf("VIDE\n");
    }
    else{
      tempo = (*barre).h;
      (*barre).h = -score;
      //printf("DECREMENTATION et tempo = %i et h= %i\n",tempo ,(*barre).h);
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
    SDL_ExitWithError("Impossible de dessiner un rectangle");

  SDL_RenderPresent(renderer);
  if(score < 0 ){
    if(tempo-score >= -5){
      (*barre).h = -5;
    }
    else{
      //printf("test tempo score\n");
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
    SDL_ExitWithError("Impossible de dessiner un rectangle");

  SDL_RenderPresent(renderer);
}