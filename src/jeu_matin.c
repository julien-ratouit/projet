/**
* \file jeu_matin.c
* \brief Cette fonction agit sur le cours du matin.
* \details On utilise cette fonction lorsque le joueur commence le cours du matin ou le cours de l'après-midi.
* \author Quenault Maxime, Renoit Charles
*/

#include "../include/commun.h"
#include "../include/jeu_matin.h"
#include "../include/timer.h"
#include "../include/barre.h"
#include "../include/self.h"
#include <time.h>

#define VITESSE_BARRES 1
#define TEMPS_COUR 30000

/**
* \fn void lancement_matin(param_t * parametre)
* \brief Fonction qui s'occupe du cours du matin.
* 
* \details Lorsque cette fonction est lancé, plusieurs variables et textures sont créées. Le programme va egalement lancé 5 timer qui s'occuperont du déroulement du jeu. Une fois les timers
* lancés on entre dans une boucle while qui s'arrêtera seulement si le joueur quitte la partie ou si il perd le jeu. C'est dans cette boucle que l'ont effectue une misa à jour aléatoire de la barre
* sonore et de la barre de depression, une augmentation aléatoire qui utilise le numéros du jour pour que le jeu devienne de plus en plus dure. Nous avons ensuite une grande partie (ligne 157-346)
* qui permet d'afficher les 10 dernières secondes au joueurs, cela lui permet d'avoir une petite idée du temps qu'il lui reste. Juste en dessous, nous avons un ensemble de if() qui permettent
* de changer les texture des boutons d'actions ne fonction de la veleur des couldown (gerer par les timers cd_actionX). Une fois tout cela effectué, nous entrons dans une seconde boucle while
* qui elle à pour objectif d'attendre un clique de la part du joueur et d'agire de la bonne manière. 
*
* \param statut_menu est un valeur qui permet de savoir si oui ou non le menu pause est afficher à l'ecran, si c'est le cas alors le joueur peut cliquer sur reprendre ou quitter,
* dans le cas contraire le joueur ne pourra pas y avoir accés.
* \param cd_actionX sont des timers qui permettent de vérifier le couldown de chaque action. Si le timer 1 est inferieur au couldown de l'action 1 alors l'action enquestion est inutilisable.
* \param temps_jeu est un timer qui permet de verifier le temps du jeu, si on le definit à 15 000 alors le joueur devra rester en jeu pendant 15s.
*
*/

void lancement_matin(param_t * parametre)
{
	
	//variables pour les barres
	int cpt1 = 0;
	int agit = 0;
	int temps = 30;
	srand(time(NULL));
	bool gameOver_actif = false;

	int decompte = 0;
	int nombre_decompte = 10;
	///////////////////////////

	SDL_Texture *texture_classe = NULL;
	SDL_Texture *texture_self = NULL;

	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_menu_option = NULL;

	SDL_Texture *texture_barre_son = NULL;
	SDL_Texture *texture_barre_depression = NULL;

	SDL_Texture *texture_action1 = NULL;//action 1
	SDL_Texture *texture_action2 = NULL;//action 2
	SDL_Texture *texture_action3 = NULL;//action 3
	SDL_Texture *texture_action4 = NULL;//action 4

	SDL_Texture *texture_cd_action1 = NULL;
	SDL_Texture *texture_cd_action2 = NULL;
	SDL_Texture *texture_cd_action3 = NULL;
	SDL_Texture *texture_cd_action4 = NULL;

	SDL_Texture *texture_centaine = NULL;
	SDL_Texture *texture_dizaine = NULL; 
	SDL_Texture *texture_unite = NULL; 

	SDL_Texture *texture_game_over = NULL;

	SDL_Rect *barre_depression;
	barre_depression=malloc(sizeof(SDL_Rect));

	SDL_Rect *barre_sonore;
	barre_sonore=malloc(sizeof(SDL_Rect));

	int status_menu = -1;

	(parametre->cd_action1)->debut(parametre->cd_action1);
	(parametre->cd_action2)->debut(parametre->cd_action2);
	(parametre->cd_action3)->debut(parametre->cd_action3);
	(parametre->cd_action4)->debut(parametre->cd_action4);

	ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
	aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);
	ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
	affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);

	init_barre_depression(parametre->renderer, barre_depression, parametre->val_depression);
	init_barre_sonore(parametre->renderer, barre_sonore);

	ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
	ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

	SDL_RenderPresent(parametre->renderer);

	(parametre->temps_jeu)->debut(parametre->temps_jeu);

	/*----------------------------------------------------------------------*/
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched && parametre->perdu != SDL_TRUE)
	{





		//mise a jour des barres atomatic
		//printf("debut barre:\n");
		agit = parametre->nb_jour + VITESSE_BARRES;
		//printf("temps:%d\n", temps);
		
		if(((*barre_depression).h>(-250)) && status_menu == -1 && temps == ((cpt1 % 181)+20))
		{
			temps = rand()%(181)+20;
			/*mise a jour de la barre sonore + remise en place de la texture associé*/
			update_barre_sonore(parametre->renderer, barre_sonore, agit);
			SDL_DestroyTexture(texture_barre_son);
			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			
			/*mise a jour de la barre de depression + remise en place de la texture associé*/
			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			SDL_DestroyTexture(texture_barre_depression);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

			SDL_RenderPresent(parametre->renderer);
		}
		///////////////////////////////////

		//detection de la defaite
		if ((*barre_depression).h<=(-247) && status_menu == -1)
		{
			status_menu = 1;
			gameOver_actif = true;
			(parametre->temps_jeu)->stop(parametre->temps_jeu);
			ajout_texture(texture_game_over ,"images/game_over.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			SDL_RenderPresent(parametre->renderer);
		}
		/////////////////////////	
		//test
		//printf("nb boucles: %d\n",cpt1);
		SDL_Delay(1);
		cpt1++;
		//////

		decompte = (parametre->temps_jeu)->get_ticks(parametre->temps_jeu);
		agit = 0;

		if(decompte > TEMPS_COUR) 
			program_launched = SDL_FALSE;




		


		if (decompte > (TEMPS_COUR-10000) && nombre_decompte == 10)
		{
			nombre_decompte--;
			ajout_texture_non_centre(texture_centaine , "images/chiffres/1.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);
			ajout_texture_non_centre(texture_dizaine , "images/chiffres/0.png", parametre->renderer, parametre->window, DIZ_X, DIZ_Y);	

			SDL_RenderPresent(parametre->renderer);		
		}	
		if (decompte > (TEMPS_COUR-9000) && nombre_decompte == 9)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
			SDL_DestroyTexture(texture_centaine);
			SDL_DestroyTexture(texture_dizaine);
			ajout_texture_non_centre(texture_centaine , "images/chiffres/9.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-8000) && nombre_decompte == 8)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
		
			ajout_texture_non_centre(texture_centaine , "images/chiffres/8.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-7000) && nombre_decompte == 7)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
		
			ajout_texture_non_centre(texture_centaine , "images/chiffres/7.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-6000) && nombre_decompte == 6)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
		
			ajout_texture_non_centre(texture_centaine , "images/chiffres/6.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-5000) && nombre_decompte == 5)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
	
			ajout_texture_non_centre(texture_centaine , "images/chiffres/5.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-4000) && nombre_decompte == 4)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
	
			ajout_texture_non_centre(texture_centaine , "images/chiffres/4.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-3000) && nombre_decompte == 3)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
		
			ajout_texture_non_centre(texture_centaine , "images/chiffres/3.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);
		}
		if (decompte > (TEMPS_COUR-2000) && nombre_decompte == 2)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));

			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);
		
			ajout_texture_non_centre(texture_centaine , "images/chiffres/2.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}
		if (decompte > (TEMPS_COUR-1000) && nombre_decompte == 1)
		{
			nombre_decompte--;
			SDL_RenderClear((parametre->renderer));
			ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
			
			ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);
			affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);
			aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);

			update_barre_depression(parametre->renderer, barre_depression, barre_sonore, agit);
			update_barre_sonore(parametre->renderer, barre_sonore, agit);

			ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);
			ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

			ajout_texture_non_centre(texture_centaine , "images/chiffres/1.png", parametre->renderer, parametre->window, CENT_X, CENT_Y);

			SDL_RenderPresent(parametre->renderer);	
		}




		/*if ( (parametre->cd_action1)->get_ticks(parametre->cd_action1) <= action_equipe[0]->cd && action_equipe[0]->statut == true)
		{
			ajout_texture_non_centre(texture_cd_action1, (action_equipe[0]->img_action_flou), parametre->renderer, parametre->window, ACTION1_HAUTEUR,ACTION1_LARGEUR);
			SDL_RenderPresent(parametre->renderer);
		}
		if ( (parametre->cd_action1)->get_ticks(parametre->cd_action1) > action_equipe[0]->cd && action_equipe[0]->statut == true)
		{
			SDL_DestroyTexture(texture_cd_action1);
			SDL_RenderPresent(parametre->renderer);
		}



		if ( (parametre->cd_action2)->get_ticks(parametre->cd_action2) <= action_equipe[1]->cd && action_equipe[1]->statut == true)
		{
			ajout_texture_non_centre(texture_cd_action2, (action_equipe[1]->img_action_flou), parametre->renderer, parametre->window, ACTION2_HAUTEUR,ACTION2_LARGEUR);
			SDL_RenderPresent(parametre->renderer);
		}
		if ( (parametre->cd_action2)->get_ticks(parametre->cd_action2) > action_equipe[1]->cd && action_equipe[1]->statut == true)
		{
			SDL_DestroyTexture(texture_cd_action2);
			SDL_RenderPresent(parametre->renderer);
		}



		if ( (parametre->cd_action3)->get_ticks(parametre->cd_action3) <= action_equipe[2]->cd && action_equipe[2]->statut == true)
		{
			ajout_texture_non_centre(texture_cd_action3, (action_equipe[2]->img_action_flou), parametre->renderer, parametre->window, ACTION3_HAUTEUR,ACTION3_LARGEUR);
			SDL_RenderPresent(parametre->renderer);
		}
		if ( (parametre->cd_action3)->get_ticks(parametre->cd_action3) > action_equipe[2]->cd && action_equipe[2]->statut == true)
		{
			SDL_DestroyTexture(texture_cd_action3);
			SDL_RenderPresent(parametre->renderer);
		}



		if ( (parametre->cd_action4)->get_ticks(parametre->cd_action4) <= action_equipe[3]->cd && action_equipe[3]->statut == true)
		{
			ajout_texture_non_centre(texture_cd_action4, (action_equipe[3]->img_action_flou), parametre->renderer, parametre->window, ACTION4_HAUTEUR,ACTION4_LARGEUR);
			SDL_RenderPresent(parametre->renderer);
		}
		if ( (parametre->cd_action4)->get_ticks(parametre->cd_action4) > action_equipe[3]->cd && action_equipe[3]->statut == true)
		{
			SDL_DestroyTexture(texture_cd_action4);
			SDL_RenderPresent(parametre->renderer);
		}*/
		




		SDL_Event event;//Créer un évènement

		while(SDL_PollEvent(&event) && program_launched)
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					//printf("x : %i & y : %i\n", event.button.x, event.button.y);
					if((event.button.x > BOUTON_LOAD_SAVE_X_MAX && event.button.x < BOUTON_LOAD_SAVE_X_MIN)&&(event.button.y > BOUTON_LOAD_SAVE_Y_MAX && event.button.y < BOUTON_LOAD_SAVE_X_MIN) && status_menu == 1 && gameOver_actif == true)
					{
						parametre->perdu = SDL_FALSE;//defaite = 1 et on retourne a l'ecran d'aceuille
						parametre->quitte = SDL_TRUE;
						program_launched = SDL_FALSE;
						parametre->load = SDL_TRUE;
					}
					if((event.button.x > BOUTON_FIN_X_MAX && event.button.x < BOUTON_FIN_X_MIN)&&(event.button.y > BOUTON_FIN_Y_MAX && event.button.y < BOUTON_FIN_X_MIN) && status_menu == 1 && gameOver_actif == true)
					{

						parametre->perdu = SDL_TRUE;//defaite = 0 et on charge la derniere sauvegarde
						program_launched = SDL_FALSE;
						parametre->load = SDL_FALSE;
					}
			
					if((event.button.x > ACTION1_X_MIN && event.button.x < ACTION1_X_MAX)&&(event.button.y > ACTION1_Y_MIN && event.button.y < ACTION1_Y_MAX)&&status_menu == -1)
					{
						//si on clique sur l'action 1, on vérifie que le couldown est terminé
						if( (parametre->cd_action1)->get_ticks(parametre->cd_action1) > action_equipe[0]->cd && action_equipe[0]->statut == true)
						{
							(parametre->cd_action1)->stop(parametre->cd_action1);
							(parametre->cd_action2)->stop(parametre->cd_action2);
							(parametre->cd_action3)->stop(parametre->cd_action3);
							(parametre->cd_action4)->stop(parametre->cd_action4);


							action_equipe[0]->action_realise(parametre, barre_sonore, barre_depression);

							SDL_DestroyTexture(texture_barre_son);
							ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

							SDL_DestroyTexture(texture_barre_depression);
							ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer,parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

							SDL_RenderPresent(parametre->renderer);

							(parametre->cd_action1)->debut(parametre->cd_action1);
							(parametre->cd_action2)->debut(parametre->cd_action2);
							(parametre->cd_action3)->debut(parametre->cd_action3);
							(parametre->cd_action4)->debut(parametre->cd_action4);
						}
					}

					if((event.button.x > ACTION2_X_MIN && event.button.x < ACTION2_X_MAX)&&(event.button.y > ACTION2_Y_MIN && event.button.y < ACTION2_Y_MAX)&&status_menu == -1)
					{
						/*si on clique sur l'action 2*/
						if( (parametre->cd_action2)->get_ticks(parametre->cd_action2) > action_equipe[1]->cd  && action_equipe[1]->statut == true)
						{
							(parametre->cd_action1)->stop(parametre->cd_action1);
							(parametre->cd_action2)->stop(parametre->cd_action2);
							(parametre->cd_action3)->stop(parametre->cd_action3);
							(parametre->cd_action4)->stop(parametre->cd_action4);


							action_equipe[1]->action_realise(parametre, barre_sonore, barre_depression);	

							SDL_DestroyTexture(texture_barre_son);
							ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

							SDL_DestroyTexture(texture_barre_depression);
							ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer,parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

							SDL_RenderPresent(parametre->renderer);

							(parametre->cd_action1)->debut(parametre->cd_action1);
							(parametre->cd_action2)->debut(parametre->cd_action2);
							(parametre->cd_action3)->debut(parametre->cd_action3);
							(parametre->cd_action4)->debut(parametre->cd_action4);
						}
					}


					if((event.button.x > ACTION3_X_MIN && event.button.x < ACTION3_X_MAX)&&(event.button.y > ACTION3_Y_MIN && event.button.y < ACTION3_Y_MAX)&&status_menu == -1)
					{
						/*si on clique sur l'action 3*/
						if( (parametre->cd_action3)->get_ticks(parametre->cd_action3) > action_equipe[2]->cd  && action_equipe[2]->statut == true)
						{
							(parametre->cd_action1)->stop(parametre->cd_action1);
							(parametre->cd_action2)->stop(parametre->cd_action2);
							(parametre->cd_action3)->stop(parametre->cd_action3);
							(parametre->cd_action4)->stop(parametre->cd_action4);


							action_equipe[2]->action_realise(parametre, barre_sonore, barre_depression);

							SDL_DestroyTexture(texture_barre_son);
							ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

							SDL_DestroyTexture(texture_barre_depression);
							ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer,parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

							SDL_RenderPresent(parametre->renderer);

							(parametre->cd_action1)->debut(parametre->cd_action1);
							(parametre->cd_action2)->debut(parametre->cd_action2);
							(parametre->cd_action3)->debut(parametre->cd_action3);
							(parametre->cd_action4)->debut(parametre->cd_action4);
						}
					}

					if((event.button.x > ACTION4_X_MIN && event.button.x < ACTION4_X_MAX)&&(event.button.y > ACTION4_Y_MIN && event.button.y < ACTION4_Y_MAX)&&status_menu == -1)
					{
						/*si on clique sur l'action 4*/
						if( (parametre->cd_action4)->get_ticks(parametre->cd_action4) > action_equipe[3]->cd  && action_equipe[3]->statut == true)
						{
							(parametre->cd_action1)->stop(parametre->cd_action1);
							(parametre->cd_action2)->stop(parametre->cd_action2);
							(parametre->cd_action3)->stop(parametre->cd_action3);
							(parametre->cd_action4)->stop(parametre->cd_action4);


							action_equipe[3]->action_realise(parametre, barre_sonore, barre_depression);

							SDL_DestroyTexture(texture_barre_son);
							ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

							SDL_DestroyTexture(texture_barre_depression);
							ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer,parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

							SDL_RenderPresent(parametre->renderer);

							(parametre->cd_action1)->debut(parametre->cd_action1);
							(parametre->cd_action2)->debut(parametre->cd_action2);
							(parametre->cd_action3)->debut(parametre->cd_action3);
							(parametre->cd_action4)->debut(parametre->cd_action4);
						}
					}

					if((event.button.x < OPTION_X_MAX && event.button.x > OPTION_X_MIN)&&(event.button.y < OPTION_Y_MAX && event.button.y > OPTION_Y_MIN) && gameOver_actif == false)
					{

						/*si on clique sur le menu*/

						(parametre->temps_jeu)->pause(parametre->temps_jeu);

						(parametre->cd_action1)->pause(parametre->cd_action1);
						(parametre->cd_action2)->pause(parametre->cd_action2);
						(parametre->cd_action3)->pause(parametre->cd_action3);
						(parametre->cd_action4)->pause(parametre->cd_action4);
						
						status_menu = 1;//variable qui permet d'evite d'agire sur les autres bouton pendant le menu pause

						SDL_DestroyTexture(texture_menu_option);
						ajout_texture(texture_menu_option ,"images/menu_pause.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);

						SDL_RenderPresent(parametre->renderer);
					}

					if((event.button.x < QUIT_X_MAX && event.button.x > QUIT_X_MIN)&&(event.button.y < QUIT_Y_MAX && event.button.y > QUIT_Y_MIN)&&status_menu == 1 && gameOver_actif == false)
					{
						/*si on clique sur le bouton 'quitter le jeu'*/

						(parametre->temps_jeu)->stop(parametre->temps_jeu);

						(parametre->cd_action1)->stop(parametre->cd_action1);
						(parametre->cd_action2)->stop(parametre->cd_action2);
						(parametre->cd_action3)->stop(parametre->cd_action3);
						(parametre->cd_action4)->stop(parametre->cd_action4); 
						/*si on clique sur le bouton 'quitter le jeu'*/ 
						parametre->quitte = SDL_TRUE;
						program_launched = SDL_FALSE;
						parametre->load = SDL_FALSE;
					}

					if((event.button.x < REPRENDRE_X_MAX && event.button.x > REPRENDRE_X_MIN)&&(event.button.y < REPRENDRE_Y_MAX && event.button.y > REPRENDRE_Y_MIN)&&status_menu == 1 && gameOver_actif == false)
					{
						/*si on clique sur le bouton 'reprendre le jeu'*/

						(parametre->temps_jeu)->unpause(parametre->temps_jeu);

						(parametre->cd_action1)->unpause(parametre->cd_action1);
						(parametre->cd_action2)->unpause(parametre->cd_action2);
						(parametre->cd_action3)->unpause(parametre->cd_action3);
						(parametre->cd_action4)->unpause(parametre->cd_action4);
						
						//printf("%d ms\n", parametre->temps_jeu->get_ticks(parametre->temps_jeu));

						status_menu = -1;

						SDL_DestroyTexture(texture_menu_option);

						SDL_DestroyTexture(texture_classe);
						ajout_texture(texture_classe ,"images/salle_de_classe.png" , parametre->renderer, parametre->window, HAUTEUR , LARGEUR);
						
						SDL_DestroyTexture(texture_action1);
						SDL_DestroyTexture(texture_action2);
						SDL_DestroyTexture(texture_action3);
						SDL_DestroyTexture(texture_action4);
						aff_action(parametre->renderer, parametre->window, texture_action1, texture_action2, texture_action3, texture_action4);
						affiche_nb_jour(parametre->window, parametre->renderer, parametre->nb_jour);

						SDL_DestroyTexture(texture_btn_option);
						ajout_texture_non_centre(texture_btn_option , "images/option.png", parametre->renderer, parametre->window, OPTION_HAUTEUR, OPTION_LARGEUR);

						update_barre_sonore(parametre->renderer, barre_sonore, 0);
						update_barre_depression(parametre->renderer, barre_depression, barre_sonore, 0);

						SDL_DestroyTexture(texture_barre_son);
						ajout_texture_non_centre(texture_barre_son, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_SON_X, BARRE_SON_Y);

						SDL_DestroyTexture(texture_barre_depression);
						ajout_texture_non_centre(texture_barre_depression, "images/barre_son_depression.png", parametre->renderer, parametre->window, BARRE_DEPRESSION_X, BARRE_DEPRESSION_Y);

						SDL_RenderPresent(parametre->renderer);
					};
					break;

				default:
					break;

			}		
		}
	}
	(parametre->cd_action1)->stop(parametre->cd_action1);
	(parametre->cd_action2)->stop(parametre->cd_action2);
	(parametre->cd_action3)->stop(parametre->cd_action3);
	(parametre->cd_action4)->stop(parametre->cd_action4);
	parametre->val_depression = (*barre_depression).h;
	SDL_DestroyTexture(texture_action4);
	SDL_DestroyTexture(texture_action3);
	SDL_DestroyTexture(texture_action2);
	SDL_DestroyTexture(texture_action1);
	free(barre_sonore);
	barre_sonore = NULL;
	free(barre_depression);
	barre_depression = NULL;
	SDL_DestroyTexture(texture_classe);
}
