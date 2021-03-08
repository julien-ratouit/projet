#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "jour.h"
#include "fonction.h" 

//affiche les action en prenant en compte les achats passé
void aff_action(int *achat,  SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture_achat1, SDL_Texture *texture_achat2, SDL_Texture *texture_achat3, SDL_Texture *texture_achat4, SDL_Texture *texture_achat5)
{
	
	if(achat >= 0)
		ajout_texture_non_centre(texture_achat1 ,"images/bouton_action.png" , renderer, window, 703 , 38);
	if(achat >= 1)
		ajout_texture_non_centre(texture_achat2 ,"images/bouton_action.png" , renderer, window, 703 , 163);
	if(achat >= 2)
		ajout_texture_non_centre(texture_achat3 ,"images/bouton_action.png" , renderer, window, 612 , 72);
	if(achat >= 3)
		ajout_texture_non_centre(texture_achat4 ,"images/bouton_action.png" , renderer, window, 612 , 192);
	if(achat >= 4)
		ajout_texture_non_centre(texture_achat5 ,"images/bouton_action.png" , renderer, window, 521 , 89);
	SDL_RenderPresent(renderer);
}


//fonction qui s'occupe d'une demis journée
void demis_journee(int ms, int *achat, int *depression)
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
					if((event.button.x < 54 && event.button.x > 38) && (event.button.y < 719 && event.button.y > 703))
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
					if((event.button.x < 179 && event.button.x > 163)&&(event.button.y < 719 && event.button.y > 703) && *achat >= 1)
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
					if((event.button.x < 88 && event.button.x > 72)&&(event.button.y < 628 && event.button.y > 612) && *achat >= 2)
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
					if((event.button.x < 208 && event.button.x > 192)&&(event.button.y < 628 && event.button.y > 612) && *achat >= 3)
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

					//action 5
					if((event.button.x < 105 && event.button.x > 89)&&(event.button.y < 537 && event.button.y > 521) && *achat >= 4)
					{
						if(mana > 80)
						{
							agitation -= 90;
							if(agitation < 0)
								agitation = 0;
							mana -= 80;
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

void journee_complete(int ms, int *achat, int *depression, SDL_Renderer *renderer, SDL_Window *window/*, int *argent ???*/)
{
	SDL_Texture *texture_achat1 = NULL;
	SDL_Texture *texture_achat2 = NULL;
	SDL_Texture *texture_achat3 = NULL;
	SDL_Texture *texture_achat4 = NULL;
	SDL_Texture *texture_achat5 = NULL;

	aff_action(achat, renderer, window, texture_achat1, texture_achat2, texture_achat3, texture_achat4, texture_achat5);
	demis_journee(ms, achat, depression);
	//argent += 10; ??
	//fonction de self qui reduit la depression en achetant des plats
	demis_journee(ms, achat, depression);
	//argent += 10; ??
	//fonction de salle des profs qui permet d'acheter des actions

	SDL_DestroyTexture(texture_achat5);
	SDL_DestroyTexture(texture_achat4);
	SDL_DestroyTexture(texture_achat3);
	SDL_DestroyTexture(texture_achat2);
	SDL_DestroyTexture(texture_achat1);
}
