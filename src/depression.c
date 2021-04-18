/**
* \file argent.c
* \brief Ce programme permet de gerer l'affichage de la depression.
* \details On utilise ce programme pour afficher le taux de depression du joueur en temps réel dans la salle des profs.
* \author Quenault Maxime
*/

#include "../include/commun.h"
#include "../include/depression.h"

void affiche_depression(SDL_Window *window, SDL_Renderer *renderer, int val)
{

	int pourcentage;
	int dizaine;
	int unite;

	SDL_Texture *texture_dizaine = NULL; 
	SDL_Texture *texture_unite = NULL;
	SDL_Texture *texture_pourc = NULL;
	SDL_Texture *texture_log = NULL;
	SDL_Texture *texture_fond = NULL;

	val *= -1;
	val -= 5;

	pourcentage = (val * 100)/243;

	dizaine = pourcentage / 10;
	pourcentage -= dizaine * 10;

	unite = pourcentage % 10;

	ajout_texture_non_centre(texture_fond , "images/chiffres/fond_chiffres.png", renderer, window,FOND_X_DEP, FOND_Y_DEP);
	ajout_texture_non_centre(texture_log , "images/chiffres/logo_barre_depression.png", renderer, window, DEP_X, DEP_Y);
	ajout_texture_non_centre(texture_pourc , "images/chiffres/pourcentage.png", renderer, window,POURC_X_DEP, POURC_Y_DEP);

	switch(dizaine)
	{
		case 0:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/0.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 1:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/1.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 2:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/2.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 3:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/3.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 4:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/4.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 5:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/5.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 6:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/6.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 7:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/7.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 8:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/8.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		case 9:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/9.png", renderer, window, DIZ_X_DEP, DIZ_Y_DEP);
			break;
		default: break;
	}

	switch(unite)
	{
		case 0:
			ajout_texture_non_centre(texture_unite , "images/chiffres/0.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 1:
			ajout_texture_non_centre(texture_unite , "images/chiffres/1.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 2:
			ajout_texture_non_centre(texture_unite , "images/chiffres/2.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 3:
			ajout_texture_non_centre(texture_unite , "images/chiffres/3.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 4:
			ajout_texture_non_centre(texture_unite , "images/chiffres/4.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 5:
			ajout_texture_non_centre(texture_unite , "images/chiffres/5.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 6:
			ajout_texture_non_centre(texture_unite , "images/chiffres/6.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 7:
			ajout_texture_non_centre(texture_unite , "images/chiffres/7.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 8:
			ajout_texture_non_centre(texture_unite , "images/chiffres/8.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		case 9:
			ajout_texture_non_centre(texture_unite , "images/chiffres/9.png", renderer, window, UNIT_X_DEP, UNIT_Y_DEP);
			break;
		default: break;
	}

}

