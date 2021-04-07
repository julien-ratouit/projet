#ifndef _ACTION_H_
#define _ACTION_H_


typedef struct action_s
{
	//Identifiant dans le tableau des actions
	int id;
	//Prix a l'achat
	int prix;
	//Temps avant la prochaine réutilisation en seconde
	int cd;
	//Savoir si l'action est acheté ou pas
	bool statut;
	int equipe;

	const char *img_action_rond;
	const char *img_action_rect;
	//Fonction qui va être utilisé dans le jeu
	void (*action_realise)(int); 
}
action_t;

typedef struct
{
	Timer_t *temps_jeu;
	int argent;
	SDL_Rect *depression;
	SDL_Renderer *renderer;
	SDL_Window *window;
}
param_t;


extern void affiche_barre_action(param_t *parametre);
extern void affiche_menu_action(param_t *parametre);

extern action_t *init_action(int id, int prix, int cd,void (*fonction)(int), const char * lien_img_rect, const char * lien_img_rond);
extern void init_tab_action(action_t * tab[]);
extern int achat_action(action_t *action, int *argent);
extern int equipe_action(int place, int * argent, action_t * tab_equipe[4], action_t * tab_action[], param_t *parametre);
extern void menu_action(int * argent, action_t * tab_equipe[4], action_t * tab_action[], param_t *parametre);
extern int clic_choix_sdp();
void fonc_action_1 (int jour);
void fonc_action_2 (int jour);
void fonc_action_3 (int jour);
void fonc_action_4 (int jour);

#endif