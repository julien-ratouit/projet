/**
* \file self.c
* \brief Ensemble de fonction qui gère le self.
* \details c'est dans ces fonctions que l'on met en place les textures et les zones de cliques correspondante au self.
* \author Quenault Maxime
*/


#include "commun.h"
#include "jeu_apremidi.h"
#include "self.h"



/**
* \brief fonction qui affiche des textures à l'ecran.
*
* \details Dans cette fonction nous affichons les textures qui sont toujours utile, à chaque fois que le joueur clique sur un menu (le menu info ou un plat par exemple)
* il faut tout re-afficher, donc pour eviter la redondance dans le code on a opté pour ce système de fonction.
* 
* \param texture_self est une variable de type \a SDL_Texture, on l'utilise pour toute nos textures à afficher à l'ecran.
*  
*/
void aff_texture_self(param_t *parametre, SDL_Texture *texture_self)
{
	ajout_texture(texture_self ,"images/self.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture_non_centre(texture_self , "images/btn_info.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);
	ajout_texture(texture_self, "images/bouton_suivant.png", (parametre->renderer), (parametre->window), HAUTEUR*1.85 , LARGEUR);
	ajout_texture_non_centre(texture_self, "images/plats/salade.png", (parametre->renderer), (parametre->window), 300, 350);
	ajout_texture_non_centre(texture_self, "images/plats/poulet.png", (parametre->renderer), (parametre->window), 415, 350);
	ajout_texture_non_centre(texture_self, "images/plats/steak.png", (parametre->renderer), (parametre->window), 530, 350);
	ajout_texture_non_centre(texture_self, "images/plats/kebab.png", (parametre->renderer), (parametre->window), 645, 350);
	ajout_texture_non_centre(texture_self, "images/plats/oeuf.png", (parametre->renderer), (parametre->window), 760, 350);
	ajout_texture_non_centre(texture_self, "images/plats/gateau.png", (parametre->renderer), (parametre->window), 875, 350);
	ajout_texture_non_centre(texture_self, "images/plats/bouteille.png", (parametre->renderer), (parametre->window), 928, 283);
	ajout_texture_non_centre(texture_self, "images/plats/bouteille.png", (parametre->renderer), (parametre->window), 961, 304);
}


/**
* \brief fonction qui gère le self.
*
* \details Dans cette fonction nous regardons ou est-ce que le joueur clique, si il clique sur un plat alors on ouvre un shop pour acheter le plat, au contraire si
* il décide de lancer le cours de l'après-midi alors on appel la fonction \a lancement_apremidi.
* 
* \param statut_mess est une valeur de type \a int qui permet de savoir si oui ou non le message de début est ouvert ou pas, si oui alors sa valeur est 1 sinon 0.
* \param statut_info est une valeur de type \a int qui permet de savoir si oui ou non le message d'information est ouvert ou pas, si oui alors sa valeur est de 1 sinon 0.
*  
*/
void lancement_self(param_t *parametre)
{
	SDL_RenderClear((parametre->renderer));

	SDL_Texture *texture_self = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_menu_info = NULL;
	SDL_Texture *texture_background_plat = NULL;

	
	aff_texture_self(parametre, texture_self);
	affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
	affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_info = 0;
	int statut_plat = 0;
	int num_plat = 0;

	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{

		SDL_Event event;

		while(SDL_PollEvent(&event) && program_launched)
		{

			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("x : %i & y : %i\n", event.button.x, event.button.y);
					if((event.button.x > 535 && event.button.x < 747)&&(event.button.y > 367 && event.button.y < 413) && statut_mess == 1)
					{
						/*on clique sur continuer*/
						statut_mess = 0;
						
						SDL_RenderClear((parametre->renderer));
						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));

						SDL_RenderPresent((parametre->renderer));

						
					}


					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0 && statut_plat == 0)
					{
						/*si on clique sur le bouton info*/
						statut_info = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_RenderClear((parametre->renderer));

						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));

						ajout_texture(texture_menu_info ,"images/info.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));

						SDL_RenderPresent((parametre->renderer));
					}
					/*PLATS*/
					/*---------------------------------------------*/
					if((event.button.x > PLAT1_X_MIN && event.button.x < PLAT1_X_MAX)&&(event.button.y > PLAT1_Y_MIN && event.button.y < PLAT1_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 1;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat1.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > PLAT2_X_MIN && event.button.x < PLAT2_X_MAX)&&(event.button.y > PLAT2_Y_MIN && event.button.y < PLAT2_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 2;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat2.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > PLAT3_X_MIN && event.button.x < PLAT3_X_MAX)&&(event.button.y > PLAT3_Y_MIN && event.button.y < PLAT3_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 3;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat3.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > PLAT4_X_MIN && event.button.x < PLAT4_X_MAX)&&(event.button.y > PLAT4_Y_MIN && event.button.y < PLAT4_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 4;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat4.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > PLAT5_X_MIN && event.button.x < PLAT5_X_MAX)&&(event.button.y > PLAT5_Y_MIN && event.button.y < PLAT5_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 5;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat5.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > PLAT6_X_MIN && event.button.x < PLAT6_X_MAX)&&(event.button.y > PLAT6_Y_MIN && event.button.y < PLAT6_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						statut_plat = 1;
						num_plat = 6;
						ajout_texture(texture_background_plat, "images/plats/fond_achat_plat6.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > 949 && event.button.x < 991)&&(event.button.y > 111 && event.button.y < 153) && statut_mess == 0 && statut_info == 0 && statut_plat == 1)
					{
						statut_plat = 0;

						SDL_RenderClear((parametre->renderer));

						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x > 501 && event.button.x < 777)&&(event.button.y > 517 && event.button.y < 617) && statut_mess == 0 && statut_info == 0 && statut_plat == 1)
					{
						//si on clique sur le bouton acheter
						//cela change les donnée en fonction du plats que l'on achète.
						switch(num_plat)
						{
							case 1 : 
								if( ( parametre->argent ) >= 2 )
								{
									parametre->argent -= 2;
									parametre->val_depression += 12; //ici, on augmente la valeur de depression, (242*5)/100 = 12 avec 242 la hauteur de la barre à 100% et 5 le taux de pourcentage que l'on veut enlever.
									if( ( parametre->val_depression ) > -5 ) //ici on verifie de ne pas avoir de barre de depression dans le negatif, on la remet à -5 si elle est inferieur à -5.
										parametre->val_depression = -5;
								}
								break;
							case 2 :
								if( ( parametre->argent ) >= 5 )
								{
									parametre->argent -= 5;
									parametre->val_depression += 24;
									if( ( parametre->val_depression ) > -5 )
										parametre->val_depression = -5;
								}
								break;
							case 3 :
								if( ( parametre->argent ) >= 13 )
								{
									parametre->argent -= 13;
									parametre->val_depression += 36;
									if( ( parametre->val_depression ) > -5 )
										parametre->val_depression = -5;
									
								}
								break;
							case 4 :
								if( ( parametre->argent ) >= 15 )
								{
									parametre->argent -= 15;
									parametre->val_depression += 43;
									if( ( parametre->val_depression ) > -5 )
										parametre->val_depression = -5;
								}
								break;
							case 5 :
							if( ( parametre->argent ) >= 20 )
								{
									parametre->argent -= 20;
									parametre->val_depression += 55;
									if( ( parametre->val_depression ) > -5 )
										parametre->val_depression = -5;
								}
								break;
							case 6 :
								if( ( parametre->argent ) >= 25 )
								{
									parametre->argent -= 25;
									parametre->val_depression += 72;
									if( ( parametre->val_depression ) > -5 )
										parametre->val_depression = -5;
								}
								break;
						}
						statut_plat = 0;

						SDL_RenderClear((parametre->renderer));

						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));

						SDL_RenderPresent((parametre->renderer));

					}
					/*---------------------------------------------*/

					if((event.button.x < COMPRIS_X_MAX && event.button.x > COMPRIS_X_MIN)&&(event.button.y < COMPRIS_Y_MAX && event.button.y > COMPRIS_Y_MIN) && statut_info == 1)
					{
						/*si on clique sur compris*/
						statut_info = 0;

						SDL_RenderClear((parametre->renderer));
						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						affiche_depression((parametre->window), (parametre->renderer), (parametre->val_depression));

						SDL_RenderPresent((parametre->renderer));
					}


					if((event.button.x > BTN_SUIVANT_X_MIN && event.button.x < BTN_SUIVANT_X_MAX)&&(event.button.y > BTN_SUIVANT_Y_MIN && event.button.y < BTN_SUIVANT_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_plat == 0)
					{
						SDL_DestroyTexture(texture_self);
						SDL_DestroyTexture(texture_mess);
						SDL_DestroyTexture(texture_menu_info);
						program_launched = SDL_FALSE;
					}
					break;
			}
		}
	}
}