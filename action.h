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
	//Fonction qui va être utilisé dans le jeu
	void (*action_realise)(int); 
}
action_t;

extern action_t *init_action(int id, int prix, int cd, void (*fonction)(int));
extern void init_tab_action(action_t * tab[]);
extern int achat_action(action_t *action, int *argent);
extern int equipe_action(int place, int * argent, action_t * tab_equipe[4], action_t * tab_action[]);
extern void menu_action(int * argent, action_t * tab_equipe[4], action_t * tab_action[]);
extern int clic_choix_sdp();
void fonc_action_1 (int jour);
void fonc_action_2 (int jour);
void fonc_action_3 (int jour);
void fonc_action_4 (int jour);