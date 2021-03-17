#include "commun.h"
#include "argent.h"

void affiche_argent(SDL_Window *window, SDL_Renderer *renderer,int argent_total)
{
	int dizaine;
	int unite;
	int centaine;

	//je calcule la quantité d'unite, de dizaine et de centaine en fonction de l'argent donné en paramettre
	centaine = argent_total / 100;
	dizaine = argent_total / 10;
	if(centaine == 0)
		unite = argent_total % 10;
	else
		unite = argent_total % 100;

	//je creer les textures necessaire pour l'affichage de notre moula
	SDL_Texture *texture_centaine = NULL;
	SDL_Texture *texture_dizaine = NULL; 
	SDL_Texture *texture_unite = NULL; 

	SDL_Texture *texture_fond = NULL;
	SDL_Texture *texture_piece = NULL;

	ajout_texture_non_centre(texture_fond , "images/chiffres/fond_piece.png", renderer, window,0, 0);
	ajout_texture_non_centre(texture_piece , "images/chiffres/piece.png", renderer, window,5, 5);

	//j'affiche la bonne image en fonction du montant
	switch(centaine)
	{
		case 0:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/0.png", renderer, window,0, 0);
			break;
		case 1:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/1.png", renderer, window,0, 0);
			break;
		case 2:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/2.png", renderer, window,0, 0);
			break;
		case 3:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/3.png", renderer, window,0, 0);
			break;
		case 4:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/4.png", renderer, window,0, 0);
			break;
		case 5:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/5.png", renderer, window,0, 0);
			break;
		case 6:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/6.png", renderer, window,0, 0);
			break;
		case 7:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/7.png", renderer, window,0, 0);
			break;
		case 8:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/8.png", renderer, window,0, 0);
			break;
		case 9:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/9.png", renderer, window,0, 0);
			break;
		default: break;
	}

	switch(dizaine)
	{
		case 0:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/0.png", renderer, window,0, 0);
			break;
		case 1:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/1.png", renderer, window,0, 0);
			break;
		case 2:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/2.png", renderer, window,0, 0);
			break;
		case 3:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/3.png", renderer, window,0, 0);
			break;
		case 4:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/4.png", renderer, window,0, 0);
			break;
		case 5:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/5.png", renderer, window,0, 0);
			break;
		case 6:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/6.png", renderer, window,0, 0);
			break;
		case 7:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/7.png", renderer, window,0, 0);
			break;
		case 8:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/8.png", renderer, window,0, 0);
			break;
		case 9:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/9.png", renderer, window,0, 0);
			break;
		default: break;
	}

	switch(unite)
	{
		case 0:
			ajout_texture_non_centre(texture_unite , "images/chiffres/0.png", renderer, window,0, 0);
			break;
		case 1:
			ajout_texture_non_centre(texture_unite , "images/chiffres/1.png", renderer, window,0, 0);
			break;
		case 2:
			ajout_texture_non_centre(texture_unite , "images/chiffres/2.png", renderer, window,0, 0);
			break;
		case 3:
			ajout_texture_non_centre(texture_unite , "images/chiffres/3.png", renderer, window,0, 0);
			break;
		case 4:
			ajout_texture_non_centre(texture_unite , "images/chiffres/4.png", renderer, window,0, 0);
			break;
		case 5:
			ajout_texture_non_centre(texture_unite , "images/chiffres/5.png", renderer, window,0, 0);
			break;
		case 6:
			ajout_texture_non_centre(texture_unite , "images/chiffres/6.png", renderer, window,0, 0);
			break;
		case 7:
			ajout_texture_non_centre(texture_unite , "images/chiffres/7.png", renderer, window,0, 0);
			break;
		case 8:
			ajout_texture_non_centre(texture_unite , "images/chiffres/8.png", renderer, window,0, 0);
			break;
		case 9:
			ajout_texture_non_centre(texture_unite , "images/chiffres/9.png", renderer, window,0, 0);
			break;
		default: break;
	}
}