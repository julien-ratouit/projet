#include <time.h>
#include "commun.h"
#include "timer.h"
#include "lancement_jeu.h"
#include "tuto.h"

int main (int argc, char ** argv)
{
	srand(time(NULL));
	system("cls");
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Surface *image = NULL;

	SDL_Texture *texture_menu = NULL;
	SDL_Texture *texture_btn_jouer = NULL;
	SDL_Texture *texture_btn_option = NULL;
	SDL_Texture *texture_btn_tuto = NULL;

	Timer_t *temps_jeu;
	temps_jeu = timer_init();

	SDL_bool program_launched = SDL_TRUE;


	int status_tuto = -1;
	int argent = 0;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ExitWithError("Initialisation SDL");

	if(SDL_CreateWindowAndRenderer(LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    	SDL_ExitWithError("Impossible de créer la fenêtre et le rendu");

	ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
	ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_LARGEUR, TUTO_HAUTEUR);

	SDL_RenderPresent(renderer);

	while(program_launched)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					printf("x : %i\ny : %i\n\n", event.button.x, event.button.y);
					if((event.button.x < BOUTON_PLAY_X_MAX && event.button.x > BOUTON_PLAY_X_MIN)&&(event.button.y < BOUTON_PLAY_Y_MAX && event.button.y > BOUTON_PLAY_Y_MIN) && status_tuto == -1)
					{
						/*si on appuie sur le bouton jouer*/
						SDL_DestroyTexture(texture_btn_jouer);
						SDL_DestroyTexture(texture_menu);
						SDL_DestroyTexture(texture_btn_tuto);

						lancement(renderer, window, temps_jeu, argent);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_LARGEUR, TUTO_HAUTEUR);

						SDL_RenderPresent(renderer);
					}
					if ((event.button.x < BOUTON_TUTO_X_MAX && event.button.x > BOUTON_TUTO_X_MIN)&&(event.button.y < BOUTON_TUTO_Y_MAX && event.button.y > BOUTON_TUTO_Y_MIN))
					{
						/*si on appuie sur le bouton tuto*/

						tuto(renderer, window);
						
						SDL_RenderClear(renderer);

						ajout_texture(texture_menu ,"images/menu.jpg" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture(texture_btn_jouer ,"images/jouer.bmp" , renderer, window, HAUTEUR , LARGEUR);
						ajout_texture_non_centre(texture_btn_tuto ,"images/tuto_petit.png" , renderer, window, TUTO_LARGEUR, TUTO_HAUTEUR);
					
						SDL_RenderPresent(renderer);
					}
					break;

				case SDL_QUIT:
					program_launched = SDL_FALSE;
					break;

				default : break;
			}
		}
	}
	SDL_DestroyTexture(texture_btn_jouer);
	SDL_DestroyTexture(texture_btn_tuto);
	SDL_DestroyTexture(texture_menu);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}