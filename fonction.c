/**
* \file fonction.c
* \brief Ce programme rassemble quelques fonctions.
* \details On utilise ce programme pour définir des fonctions utile dans tout le programme.
* \author Vallet Guillaume, Quenault Maxime, Renoit Charles
*/


#include "commun.h"


/**
* \brief Quitte le programme en cas d'erreur
* 
* \details Cette fonction à pour but de quiter la SDL en affichant le message donner en parametre,
* on l'utilise pour gerer les erreures lors de la création d'une fenêtre ou d'un rendu notamment.
*  
*/
extern void SDL_ExitWithError(const char *message)
{ 
  SDL_Log("ERREUR : %s > %s\n",message, SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}


/**
* \brief Quitte le programme en cas d'erreur dans le rendu de l'image
* 
* \details Cette fonction à pour but de quiter la SDL en affichant le message donner en parametre,
* on l'utilise pour gerer les erreures lors de la création d'une texture. On prend bien soins de detrure le rendu et la fenêtre (existant obligatoirement car present en paramêtre),
* pour ensuite quitter la SDL en appelant la fonction \a SDL_ExitWithError
*  
*/
extern void SDL_ExitImageWithError(const char *message, void * renderer, void * window)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_ExitWithError(message);
}


/**
* \brief ajoute une texture à l'ecran.
* 
* \details Cette fonction réalise toute les étapes nécéssaire à la création d'une texture. Sa particularité est qu'elle ajoute une texture de façon
* centré par rapport aux coordonnée donnée en paramètre. Très souvant on lui donne la hauteur et la largeur de la fenêtre pour centrer une texture à l'ecran.
*  
*/
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


/**
* \brief ajoute une texture à l'ecran.
* 
* \details Cette fonction réalise toute les étapes nécéssaire à la création d'une texture. Sa particularité est qu'elle ajoute une texture de façon
* non centré. les valeurs x et y représente donc sont point de départ pour l'affichage.
*  
*/
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

/**
* \brief affiche les actions sur l'ecran de jeu.
* 
* \details Cette fonction affiche les actions, achetés par le joueur, en jeu. Elle agit seulement dans la salle de classe.
*  
*/
void aff_action(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture_achat1, SDL_Texture *texture_achat2, SDL_Texture *texture_achat3, SDL_Texture *texture_achat4)
{
  	if(action_equipe[0] != NULL)
    	ajout_texture_non_centre(texture_achat1, (action_equipe[0]->img_action_rond), renderer,window, ACTION1_HAUTEUR,ACTION1_LARGEUR);
    else
      ajout_texture_non_centre(texture_achat1 ,"images/bouton_action.png" , renderer, window, ACTION1_HAUTEUR , ACTION1_LARGEUR);

    if(action_equipe[1] != NULL)
		  ajout_texture_non_centre(texture_achat2, (action_equipe[1]->img_action_rond), renderer, window, ACTION2_HAUTEUR,  ACTION2_LARGEUR);
    else
      ajout_texture_non_centre(texture_achat2 ,"images/bouton_action.png" , renderer, window, ACTION2_HAUTEUR , ACTION2_LARGEUR);

    if(action_equipe[2] != NULL)
		  ajout_texture_non_centre(texture_achat3, (action_equipe[2]->img_action_rond), renderer, window, ACTION3_HAUTEUR , ACTION3_LARGEUR);
    else  
      ajout_texture_non_centre(texture_achat3 ,"images/bouton_action.png" , renderer, window, ACTION3_HAUTEUR , ACTION3_LARGEUR);
    
    if(action_equipe[3] != NULL)
		  ajout_texture_non_centre(texture_achat4, (action_equipe[3]->img_action_rond), renderer, window, ACTION4_HAUTEUR, ACTION4_LARGEUR);
    else
      ajout_texture_non_centre(texture_achat4 ,"images/bouton_action.png" , renderer, window, ACTION4_HAUTEUR , ACTION4_LARGEUR);
      
  SDL_RenderPresent(renderer);
}


/**
* \brief à définir
* 
* \details à définir
*  
*/
extern int press_action(SDL_Renderer *renderer, int num_action){
  int i = -50;
  printf("Vous avez appuyer sur l'action %i\n",num_action);

  return i;
}



