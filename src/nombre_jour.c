/**
* \file nombre_jour.c
* \brief Cette fonction permet de gerer l'affichage du numéros du jour
* \details On utilise cette fonction pour afficher le numeros du jour en temps réel dans le jeu.
* \author Quenault Maxime
*/

#include "../include/commun.h"
#include "../include/nombre_jour.h"



/**
* \brief Affiche le numéros du jour en jeu
* 
* \details Dans un premier temps, on récupère le numéros du jour en paramètre. On considère que notre jeu ne permettera pas de dépasser les 99 jours, donc on calcule une dizaine et une unité seulement.
* C'est à ce moment là qu'on affiche à l'ecrans le bon chiffre à la bonne place (même procédé que dans argent.c).
*
* \return On return aucunes valeur, cette fonction ne fait que de l'affichage.
*  
*/
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