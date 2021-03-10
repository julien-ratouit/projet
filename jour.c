#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "jour.h"
#include "fonction.h"  
#include "coords.h"

//affiche les action en prenant en compte les achats passé
void aff_action(int *achat,  SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture_achat1, SDL_Texture *texture_achat2, SDL_Texture *texture_achat3, SDL_Texture *texture_achat4)
{
	
	if((*achat) >= 0)
		ajout_texture_non_centre(texture_achat1 ,"images/bouton_action.png" , renderer, window, ACTION1_HAUTEUR , ACTION1_LARGEUR);
	if((*achat) >= 1)
		ajout_texture_non_centre(texture_achat2 ,"images/bouton_action.png" , renderer, window, ACTION2_HAUTEUR , ACTION2_LARGEUR);
	if((*achat) >= 2)
		ajout_texture_non_centre(texture_achat3 ,"images/bouton_action.png" , renderer, window, ACTION3_HAUTEUR , ACTION3_LARGEUR);
	if((*achat) >= 3)
		ajout_texture_non_centre(texture_achat4 ,"images/bouton_action.png" , renderer, window, ACTION4_HAUTEUR , ACTION4_LARGEUR);
	SDL_RenderPresent(renderer);
}


//fonction qui s'occupe d'une demis journée
void demis_journee(int *achat, int *depression)
{
	SDL_Event event;
	
	int agitation = 0;
	int mana = 100;
	switch(event.type)
	{
			case SDL_MOUSEBUTTONDOWN:
				//printf("x : %i\ny : %i\n\n", event.button.x, event.button.y);
				if(  *depression < 100  ) 
				{
					agitation ++;
					mana += 10;

					//action 1
					if((event.button.x < ACTION1_X_MAX && event.button.x > ACTION1_X_MIN) && (event.button.y < ACTION1_Y_MAX && event.button.y > ACTION1_Y_MIN))
					{
						if(mana > 10)
						{
							agitation -= 10;
							if(agitation < 0)
								agitation = 0;
							mana -= 10;
							if(mana < 0)
								mana = 0;
						}	
						if(agitation >= 100)
							depression += 20;
					
					}

					//action 2
					if((event.button.x < ACTION2_X_MAX && event.button.x > ACTION2_X_MIN)&&(event.button.y < ACTION2_Y_MAX && event.button.y > ACTION2_Y_MIN) && *achat >= 1)
					{
						if(mana > 20)
						{
							agitation -= 20;
							if(agitation < 0)
								agitation = 0;
							mana -= 20;
							if(mana < 0)
								mana = 0;
						}
						if(agitation >= 100)
							depression += 20;
			
					}

					//action 3
					if((event.button.x < ACTION3_X_MAX && event.button.x > ACTION3_X_MIN)&&(event.button.y < ACTION3_Y_MAX && event.button.y > ACTION3_Y_MIN) && *achat >= 2)
					{
						if(mana > 40)
						{
							agitation -= 35;
							if(agitation < 0)
								agitation = 0;
							mana -= 40;
							if(mana < 0)
								mana = 0;
						}
						if(agitation >= 100)
							depression += 20;
			
					}

					//action 4
					if((event.button.x < ACTION4_X_MAX && event.button.x > ACTION4_X_MIN)&&(event.button.y < ACTION4_Y_MAX && event.button.y > ACTION4_Y_MIN) && *achat >= 3)
					{
						if(mana > 50)
						{
							agitation -= 55;
							if(agitation < 0)
								agitation = 0;
							mana -= 50;
							if(mana < 0)
						mana = 0;
						}
						if(agitation >= 100)
							depression += 20;
			
					}
				};
				break;
	}
}

void journee_complete(int *achat, int *depression, SDL_Renderer *renderer, SDL_Window *window/*, int *argent ???*/)
{
	SDL_Texture *texture_achat1 = NULL;
	SDL_Texture *texture_achat2 = NULL;
	SDL_Texture *texture_achat3 = NULL;
	SDL_Texture *texture_achat4 = NULL;

	aff_action(achat, renderer, window, texture_achat1, texture_achat2, texture_achat3, texture_achat4);
	demis_journee(achat, depression);
	//argent += 10; ??
	//fonction de self qui reduit la depression en achetant des plats
	demis_journee(achat, depression);
	//argent += 10; ??
	//fonction de salle des profs qui permet d'acheter des actions

	SDL_DestroyTexture(texture_achat4);
	SDL_DestroyTexture(texture_achat3);
	SDL_DestroyTexture(texture_achat2);
	SDL_DestroyTexture(texture_achat1);
}
