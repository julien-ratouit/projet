#include "commun.h"
#include "nombre_jour.h"


void affiche_nb_jour(SDL_Window *window, SDL_Renderer *renderer, int nb_jour)
{

	int dizaine;
	int unite;

	SDL_Texture *texture_dizaine = NULL; 
	SDL_Texture *texture_unite = NULL;
	SDL_Texture *texture_fond = NULL;

	dizaine = nb_jour / 10;
	nb_jour -= dizaine * 10;

	unite = nb_jour % 10;

	ajout_texture(texture_fond , "images/bckgrn_jour.png", renderer, window, HAUTEUR, LARGEUR);

	switch(dizaine)
	{
		case 0:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/0.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 1:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/1.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 2:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/2.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 3:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/3.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 4:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/4.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 5:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/5.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 6:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/6.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 7:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/7.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 8:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/8.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		case 9:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/9.png", renderer, window, DIZ_X_JR, DIZ_Y_JR);
			break;
		default: break;
	}

	switch(unite)
	{
		case 0:
			ajout_texture_non_centre(texture_unite , "images/chiffres/0.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 1:
			ajout_texture_non_centre(texture_unite , "images/chiffres/1.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 2:
			ajout_texture_non_centre(texture_unite , "images/chiffres/2.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 3:
			ajout_texture_non_centre(texture_unite , "images/chiffres/3.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 4:
			ajout_texture_non_centre(texture_unite , "images/chiffres/4.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 5:
			ajout_texture_non_centre(texture_unite , "images/chiffres/5.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 6:
			ajout_texture_non_centre(texture_unite , "images/chiffres/6.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 7:
			ajout_texture_non_centre(texture_unite , "images/chiffres/7.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 8:
			ajout_texture_non_centre(texture_unite , "images/chiffres/8.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		case 9:
			ajout_texture_non_centre(texture_unite , "images/chiffres/9.png", renderer, window, UNIT_X_JR, UNIT_Y_JR);
			break;
		default: break;
	}

}