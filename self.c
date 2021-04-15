#include "commun.h"
#include "jeu_apremidi.h"
#include "self.h"

//A enlever après a voir lu, la partie achat est en bas il y aura des choses a remplir
//C'est a remplir en dessous, vu que je fais pas l'affichage je sais pas qu'elle image vous allez mettre mais je vous mache le travail


//Donc dans le message d'achat il faut un bouton pour acheter et un bouton pour fermer
#define CASE_ACHAT_MIN_X 0
#define CASE_ACHAT_MAX_X 0
#define CASE_ACHAT_MIN_Y 0
#define CASE_ACHAT_MAX_Y 0

#define QUITTE_ACHAT_MIN_X 0
#define QUITTE_ACHAT_MAX_X 0
#define QUITTE_ACHAT_MIN_Y 0
#define QUITTE_ACHAT_MAX_Y 0


extern int achat_selection(param_t *parametre, SDL_Texture *texture_self, SDL_Texture *texture_mess ,char * menu_achat, int pourcentage_baisse_barre, int prix)
{

	int choix = 1;
	SDL_Event event;
	ajout_texture(texture_mess, menu_achat, (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	while(SDL_PollEvent(&event) && choix)
		{
			switch (event.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					if((event.button.x > CASE_ACHAT_MIN_X && event.button.x < CASE_ACHAT_MAX_X )&&(event.button.y > CASE_ACHAT_MIN_Y  && event.button.y < CASE_ACHAT_MAX_Y) && parametre-> argent > prix){
						parametre->argent -= prix;
						choix = 0;

						//Baisse de la barre de dépression... avec pourcentage_baisse_barre



						SDL_RenderClear(parametre->renderer);
						aff_texture_self(parametre, texture_self);

						return 1; // Si quelque chose est acheté on passe au cours d'après
					}
					if((event.button.x > QUITTE_ACHAT_MIN_X && event.button.x < QUITTE_ACHAT_MAX_X )&&(event.button.y > QUITTE_ACHAT_MIN_Y  && event.button.y < QUITTE_ACHAT_MAX_Y)){

						choix = 0;

						SDL_RenderClear(parametre->renderer);
						aff_texture_self(parametre, texture_self);

						return 0; //Si on clique sur la croix on ferme la fenetre et on repart dans le self
					}
				}

	}
	
}

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



void lancement_self(param_t *parametre)
{

	SDL_RenderClear((parametre->renderer));

	SDL_Texture *texture_self = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_menu_info = NULL;

	
	aff_texture_self(parametre, texture_self);
	affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_info = 0;
	int statut_achat = 0;

	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{

		SDL_Event event;//Créer un évènement

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

						SDL_RenderPresent((parametre->renderer));

						
					}


					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0  && statut_achat == 0)
					{
						/*si on clique sur le bouton info*/
						statut_info = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_RenderClear((parametre->renderer));
						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
						ajout_texture(texture_menu_info ,"images/info.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
						SDL_RenderPresent((parametre->renderer));

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x < COMPRIS_X_MAX && event.button.x > COMPRIS_X_MIN)&&(event.button.y < COMPRIS_Y_MAX && event.button.y > COMPRIS_Y_MIN) && statut_info == 1)
					{
						/*si on clique sur compris*/
						statut_info = 0;

						SDL_RenderClear((parametre->renderer));
						aff_texture_self(parametre, texture_self);
						affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));

						SDL_RenderPresent((parametre->renderer));
					}


					if((event.button.x > BTN_SUIVANT_X_MIN && event.button.x < BTN_SUIVANT_X_MAX)&&(event.button.y > BTN_SUIVANT_Y_MIN && event.button.y < BTN_SUIVANT_Y_MAX) && statut_mess == 0 && statut_info == 0 && statut_achat == 0)
					{
						SDL_DestroyTexture(texture_self);
						SDL_DestroyTexture(texture_mess);
						SDL_DestroyTexture(texture_menu_info);
						program_launched = SDL_FALSE;
					}

					//Partie achat---------------------------------------------------------------------------------------------------------------------------------------------

					//Salade
					if((event.button.x > 313 && event.button.x < 353 )&&(event.button.y > 372 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Salade\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}

					//Poulet
					if((event.button.x > 429 && event.button.x < 472 )&&(event.button.y > 372 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Poulet\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat du poulet*/, 15, 2))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}

					//Steack frite
					if((event.button.x > 540 && event.button.x < 587 )&&(event.button.y > 369 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Steack frite\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}

					//Kebab
					if((event.button.x > 654 && event.button.x < 704 )&&(event.button.y > 369 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Kebab\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}
					//Oeuf
					if((event.button.x > 774 && event.button.x < 820 )&&(event.button.y > 369 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Oeuf\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}

					//Gateau
					if((event.button.x > 883 && event.button.x < 936 )&&(event.button.y > 366 && event.button.y < 398) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Gateau\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}

					//Bouteille
					if((event.button.x > 941 && event.button.x < 1002 )&&(event.button.y > 289 && event.button.y < 358) && statut_mess == 0 && statut_info == 0  && statut_achat == 0){ 
						printf("Bouteille\n");
						statut_achat = 1;
						//if(achat_selection(parametre, texture_self, texture_mess, "" /*Texture du menu d'achat de la salade*/, 10, 1))
						//	program_launched = SDL_FALSE;
						statut_achat = 0;

					}
					break;
			}
		}
	}	
}