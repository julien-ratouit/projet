#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "fonctions.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
/*
  drapeaux pour le renderer :
  SDL_RENDERER_SOFTWARE
  SDL_RENDERER_ACCELERATED
  SDL_RENDERER_PRESENTVSYNC
*/


/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

int main(int argc, char *arg[]){
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *texture_fond = NULL;
  SDL_Texture *texture_action1 = NULL;//action 1
	SDL_Texture *texture_action2 = NULL;//action 2
	SDL_Texture *texture_action3 = NULL;//action 3
	SDL_Texture *texture_action4 = NULL;//action 4
  SDL_Rect *barre_depression;
  barre_depression=malloc(sizeof(SDL_Rect));
  SDL_Rect *barre_sonore;
  barre_sonore=malloc(sizeof(SDL_Rect));
  int score;
  int test;


  // Lancement SDL
  if(SDL_Init(SDL_INIT_VIDEO) != 0) //Initialisation de la SDL
    SDL_ExitWithError("Initialisation SDL");

/*----------------------------------------------------------------------*/
  // Créer la fenêtre et le rendu en même temps
  if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

/*----------------------------------------------------------------------*/
  ajout_texture(texture_fond ,"img/salle_de_classe.png" , renderer, window, WINDOW_HEIGHT , WINDOW_WIDTH);

  // Raffraichie le rendu de la fenêtre

  init_barre_depression(renderer, barre_depression);
  init_barre_sonore(renderer, barre_sonore);
  SDL_RenderPresent(renderer);
  aff_action(window, renderer, texture_action1, texture_action2, texture_action3, texture_action4, 4);


    /*----------------------------------------------------------------------*/
  SDL_bool program_launched = SDL_TRUE;

  //Boucle qui vérifie tout les évènements jusqu'à ce qu'on appuie sur la croix pour fermer le programme
  while(program_launched){

    SDL_Event event;//Créer un évènement

    while(SDL_PollEvent(&event)){//Prend n'importe quels évènements
      switch (event.type) {

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
          if((event.button.x > 70 && event.button.x < 134)&&(event.button.y > 530 && event.button.y < 594)){
            update_barre_sonore(renderer, barre_sonore, press_action(renderer, 1));
          }
          continue;

        case SDL_QUIT:
          program_launched = SDL_FALSE;
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
  SDL_DestroyTexture(texture_fond);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS; //return 0;
}

//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
