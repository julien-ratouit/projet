/**
* \file argent.c
* \brief Ce programme permet de gerer l'affichage de la somme d'argent.
* \details On utilise ce programme pour afficher la somme d'argent du joueur en temps réel à des moments précis du jeu, 
* notamment le self et la salle des profs.
* \author Quenault Maxime
*/

#include "commun.h"
#include "argent.h"

/**
* \brief Affiche la somme d'argent 
* 
* \details On récupère la somme d'argent du joueurs en paramètre, ensuite on calcule le nombre de centaine, dizaine et d'unité a l'aide de calcule modulaire.
* une fois toutes ces données récupérés on affiche la bonne texture en fonction du nombre de centaine, dizaine et d'unité. L'emplacement est toujours le même
* quelques soit la pièce (self/salle prof), on utilise donc des variables globale pour positionner les textures.
*  
* \param argent_total est une variable tampon que l'on peut se permetre de modifier dans le programme.
* \param unite est le nombre d'unite de la somme d'argent du joueur.
* \param dizaine est le nombre de dizaine de la somme d'argent du joueur.
* \param centaine est le nombre de centaine de la somme d'argent du joueur.
*/
void affiche_argent(SDL_Window *window, SDL_Renderer *renderer, int argent)
{
	int argent_total = argent;


	int dizaine;
	int unite;
	int centaine;

	centaine = argent_total / 100;
	argent_total -= centaine * 100;
	
	dizaine = argent_total / 10;
	argent_total -= dizaine * 10;

	if(centaine == 0)
		unite = argent_total % 10;
	else
		unite = argent_total % 100;

	SDL_Texture *texture_centaine = NULL;
	SDL_Texture *texture_dizaine = NULL; 
	SDL_Texture *texture_unite = NULL; 

	SDL_Texture *texture_fond = NULL;
	SDL_Texture *texture_piece = NULL;

	ajout_texture_non_centre(texture_fond , "images/chiffres/fond_piece.png", renderer, window,FOND_X, FOND_Y);
	ajout_texture_non_centre(texture_piece , "images/chiffres/piece.png", renderer, window,PIECE_X, PIECE_Y);

	switch(centaine)
	{
		case 0:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/0.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 1:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/1.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 2:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/2.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 3:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/3.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 4:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/4.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 5:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/5.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 6:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/6.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 7:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/7.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 8:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/8.png", renderer, window, CENT_X, CENT_Y);
			break;
		case 9:
			ajout_texture_non_centre(texture_centaine , "images/chiffres/9.png", renderer, window, CENT_X, CENT_Y);
			break;
		default: break;
	}

	switch(dizaine)
	{
		case 0:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/0.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 1:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/1.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 2:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/2.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 3:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/3.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 4:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/4.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 5:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/5.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 6:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/6.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 7:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/7.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 8:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/8.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		case 9:
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/9.png", renderer, window, DIZ_X, DIZ_Y);
			break;
		default: break;
	}

	switch(unite)
	{
		case 0:
			ajout_texture_non_centre(texture_unite , "images/chiffres/0.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 1:
			ajout_texture_non_centre(texture_unite , "images/chiffres/1.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 2:
			ajout_texture_non_centre(texture_unite , "images/chiffres/2.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 3:
			ajout_texture_non_centre(texture_unite , "images/chiffres/3.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 4:
			ajout_texture_non_centre(texture_unite , "images/chiffres/4.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 5:
			ajout_texture_non_centre(texture_unite , "images/chiffres/5.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 6:
			ajout_texture_non_centre(texture_unite , "images/chiffres/6.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 7:
			ajout_texture_non_centre(texture_unite , "images/chiffres/7.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 8:
			ajout_texture_non_centre(texture_unite , "images/chiffres/8.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		case 9:
			ajout_texture_non_centre(texture_unite , "images/chiffres/9.png", renderer, window, UNIT_X, UNIT_Y);
			break;
		default: break;
	}
}