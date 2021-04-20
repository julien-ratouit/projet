/**
* \file salle_prof.c
* \brief Ensemble de fonction qui gère la salle des profs.
* \details c'est dans ces fonctions que l'on met en place les textures et les zones de cliques correspondante à la salle des profs.
* \author Quenault Maxime
*/

#include "../include/commun.h"
#include "../include/jeu_matin.h"
#include "../include/salle_prof.h"
#include "../include/save.h"

/**
* \brief fonction qui affiche des textures à l'ecran.
*
* \details Dans cette fonction nous affichons les textures qui sont toujours utile, à chaque fois que le joueur clique sur un menu (le menu info ou le menu des actions par exemple)
* il faut tout re-afficher, donc pour eviter la redondance dans le code on a opté pour ce système de fonction.
* 
* \param texture_prof est une variable de type \a SDL_Texture, on l'utilise pour toute nos textures à afficher à l'ecran.
*  
*/
void aff_texture_sp(param_t *parametre, SDL_Texture *texture_prof)
{
	ajout_texture(texture_prof ,"images/salle_prof.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);
	ajout_texture(texture_prof, "images/btn_restart.png", (parametre->renderer), (parametre->window), HAUTEUR*1.8 , LARGEUR*1.5);
	ajout_texture(texture_prof, "images/btn_save.png", (parametre->renderer), (parametre->window), HAUTEUR*1.835 , LARGEUR/1.75);
	ajout_texture_non_centre(texture_prof , "images/btn_info.png", (parametre->renderer), (parametre->window), OPTION_HAUTEUR, OPTION_LARGEUR);
	affiche_argent((parametre->window), (parametre->renderer), (parametre->argent));
}

/**
* \brief fonction qui gère la salle des profs.
*
* \details Dans cette fonction nous regardons ou est-ce que le joueur clique, si il clique sur un ordinateur alors on lance la fonction \a menu_action, au contraire si
* il décide de lancer une nouvelle journée alors on relance le programme et pour finir si il décide de sauvegarder alors on sauvegarde et on revient à la page principal.
* 
* \param statut_mess est une valeur de type \a int qui permet de savoir si oui ou non le message de début est ouvert ou pas, si oui alors sa valeur est 1 sinon 0.
* \param statut_info est une valeur de type \a int qui permet de savoir si oui ou non le message d'information est ouvert ou pas, si oui alors sa valeur est de 1 sinon 0.
*  
*/
void lancement_salle_prof(param_t *parametre)
{

	(parametre->argent) = (parametre->argent) + 3 + (parametre->nb_jour);

	SDL_Texture *texture_prof = NULL;
	SDL_Texture *texture_mess = NULL;
	SDL_Texture *texture_menu_info = NULL;

	SDL_RenderClear((parametre->renderer));

	aff_texture_sp(parametre, texture_prof);
	ajout_texture(texture_mess, "images/felicitation.png", (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

	SDL_RenderPresent((parametre->renderer));

	int statut_mess = 1;
	int statut_info = 0;
	int statut_menu_act = 0;

	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{

		SDL_Event event;

		while(SDL_PollEvent(&event) && program_launched)
		{

			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					if((event.button.x > 535 && event.button.x < 747)&&(event.button.y > 367 && event.button.y < 413) && statut_mess == 1)
					{
						statut_mess = 0;
						
						SDL_RenderClear((parametre->renderer));

						aff_texture_sp(parametre, texture_prof);

						SDL_RenderPresent((parametre->renderer));
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && statut_mess == 0 && statut_menu_act == 0)
					{
						//si on clique sur le bouton info

						statut_info = 1;
						SDL_RenderClear((parametre->renderer));

						aff_texture_sp(parametre, texture_prof);
						ajout_texture(texture_menu_info ,"images/info2.png" , (parametre->renderer), (parametre->window), HAUTEUR , LARGEUR);

						SDL_RenderPresent((parametre->renderer));

					}

					if((event.button.x < COMPRIS_X_MAX && event.button.x > COMPRIS_X_MIN)&&(event.button.y < COMPRIS_Y_MAX && event.button.y > COMPRIS_Y_MIN) && statut_info == 1)
					{
						//si on clique sur le bouton compris

						statut_info = 0;

						SDL_RenderClear((parametre->renderer));

						aff_texture_sp(parametre, texture_prof);

						SDL_RenderPresent((parametre->renderer));

					}

					if(((event.button.x > 210 && event.button.x < 345)&&(event.button.y > 270 && event.button.y < 345)||
              		(event.button.x > 435 && event.button.x < 570)&&(event.button.y > 270 && event.button.y < 345)||
              		(event.button.x > 670 && event.button.x < 805)&&(event.button.y > 270 && event.button.y < 345)||
              		(event.button.x > 915 && event.button.x < 1050)&&(event.button.y > 270 && event.button.y < 345))
					 && statut_mess == 0 && statut_menu_act == 0 && statut_info == 0){

						statut_menu_act = 1;
				  		int argent = (parametre->argent);
				  		int val_sortie = menu_action(action_equipe, liste_action, parametre,texture_prof);
						switch(val_sortie)
						{
							case 1 : 
								program_launched = SDL_FALSE;
								break;
							case -1 : 
								SDL_RenderClear((parametre->renderer));

								aff_texture_sp(parametre, texture_prof);

								SDL_RenderPresent((parametre->renderer));

								statut_menu_act = 0;

								break;
						}
			  		}

					if((event.button.x > BTN_RESTART_X_MIN && event.button.x < BTN_RESTART_X_MAX)&&(event.button.y > BTN_RESTART_Y_MIN && event.button.y < BTN_RESTART_Y_MAX) && statut_mess == 0 && statut_menu_act == 0)
					{
						//on clique sur bouton pour commencer une nouvelle journee


						SDL_DestroyTexture(texture_prof);
						SDL_DestroyTexture(texture_mess);
						SDL_DestroyTexture(texture_menu_info);
						program_launched = SDL_FALSE;
						sauvegarde(parametre->argent, (parametre->nb_jour)+1, liste_action, action_equipe);
					}

					if((event.button.x > BTN_SAVE_X_MIN && event.button.x < BTN_SAVE_X_MAX)&&(event.button.y > BTN_SAVE_Y_MIN && event.button.y < BTN_SAVE_Y_MAX) && statut_mess == 0 && statut_menu_act == 0)
					{
						//on clique pour sauvegarder et quitter
						
						parametre->quitte = SDL_TRUE;
						program_launched = SDL_FALSE;
						sauvegarde(parametre->argent, (parametre->nb_jour)+1, liste_action, action_equipe);
					}
					break;
					
				default: 
					break;
			}
		}
	}
}