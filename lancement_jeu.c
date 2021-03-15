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


void lancement(SDL_Renderer *renderer, SDL_Window *window){
  SDL_Texture *texture_classe = NULL;
  SDL_Texture *texture_action1 = NULL;//action 1
	SDL_Texture *texture_action2 = NULL;//action 2
	SDL_Texture *texture_action3 = NULL;//action 3
	SDL_Texture *texture_action4 = NULL;//action 4

  SDL_Rect *barre_depression;
  barre_depression=malloc(sizeof(SDL_Rect));

  SDL_Rect *barre_sonore;
  barre_sonore=malloc(sizeof(SDL_Rect));

  /*variables de test*/
  int score;
  int test;
  int *achat = malloc(sizeof(int));
  (*achat) = 4;
  /*-----------------*/

  ajout_texture(texture_classe ,"images/salle_de_classe.png" , renderer, window, HAUTEUR , LARGEUR);

  init_barre_depression(renderer, barre_depression);
  init_barre_sonore(renderer, barre_sonore);
  SDL_RenderPresent(renderer);

  aff_action(achat, renderer, window, texture_action1, texture_action2, texture_action3, texture_action4);


    /*----------------------------------------------------------------------*/
  SDL_bool program_launched = SDL_TRUE;
  while(program_launched)
  {

    SDL_Event event;//Créer un évènement

    while(SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_KEYUP:
          switch(event.key.keysym.sym){
            case SDLK_a:
              if((*barre_depression).h>(-250)){
                score++;
                update_barre_sonore(renderer, barre_sonore, score);
                update_barre_depression(renderer, barre_depression, barre_sonore, score);
                continue;
              }
              else
                break;

            default:
              continue;
          }

        case SDL_MOUSEBUTTONDOWN:
          printf("x : %i & y : %i\n", event.button.x, event.button.y);//test pour les coords du clique
          if((event.button.x > 70 && event.button.x < 134)&&(event.button.y > 530 && event.button.y < 594))
          {
            update_barre_sonore(renderer, barre_sonore, press_action(renderer, 1));
          }
          if((event.button.x < 1236 && event.button.x > 1184)&&(event.button.y < 417 && event.button.y > 177))
          {
            program_launched = SDL_FALSE;
          }
          break;

        default:
          break;

      }
    }
  }


  /*----------------------------------------------------------------------*/

  SDL_DestroyTexture(texture_action4);
  SDL_DestroyTexture(texture_action3);
  SDL_DestroyTexture(texture_action2);
  SDL_DestroyTexture(texture_action1);
  free(barre_sonore);
  free(barre_depression);
  SDL_DestroyTexture(texture_classe);
}
