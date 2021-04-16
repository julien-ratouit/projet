#ifndef _ACTION_H_
#define _ACTION_H_

/**
* \struct param_t Permet de définir l'ensemble des variables que l'on utilise dans plusieurs programmes
* nottament les threads qui prennent qu'un seul parametre, ici ils prennent une structure de plusieurs parametre. Nous avons notamment la fenêtre et le rendu qui en font partie.
*/
typedef struct param_s
{
	Timer_t *temps_jeu;
	int argent;
	int nb_jour;
	int val_depression;
	SDL_Rect *depression;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_bool perdu;
	SDL_bool quitte;
}
param_t;


/**
* \struct action_t Permet de définir l'ensemble des élément que contient une action
* sont id, sont prix, sont couldown, sont statut (acheté ou pas), sa place dans la barre
* des actions, ses images correspondantes et pour finir un pointeur sur une fonction qui permet d'agir sur le jeu.
*/
typedef struct action_s
{
	int id;
	int prix;
	int cd;
	bool statut;
	int equipe;

	const char *img_action_rond;
	const char *img_action_rect;
	void (*action_realise)(param_t *, SDL_Rect *, SDL_Rect *); 
}
action_t;





extern void affiche_barre_action(param_t *parametre);
extern void affiche_menu_action(param_t *parametre);

extern action_t *init_action(int id, int prix, int cd,void (*fonction)(param_t *, SDL_Rect *, SDL_Rect *), const char * lien_img_rect, const char * lien_img_rond);
extern void init_tab_action(action_t * tab[]);
extern int achat_action(action_t *action, int argent);
extern int equipe_action(int place, int argent, action_t * tab_equipe[4], action_t * tab_action[], param_t *parametre, SDL_Texture *texture_prof);
extern int menu_action(action_t * tab_equipe[4], action_t * tab_action[], param_t *parametre, SDL_Texture *texture_prof);
extern int clic_choix_sdp();


void fonc_action_1 (param_t *parametre, SDL_Rect *barre_sonore, SDL_Rect *barre_depression);
void fonc_action_2 (param_t *parametre, SDL_Rect *barre_sonore, SDL_Rect *barre_depression);
void fonc_action_3 (param_t *parametre, SDL_Rect *barre_sonore, SDL_Rect *barre_depression);
void fonc_action_4 (param_t *parametre, SDL_Rect *barre_sonore, SDL_Rect *barre_depression);

#endif