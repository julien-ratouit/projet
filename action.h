typedef struct action_s
{
	int id;
	int prix;
	bool statut;
	void (*action_realise)(int); 
}
action_t;

extern action_t *init_action(int id, int prix, void (*fonction)(int));
extern void init_tab_action(action_t * tab[]);
extern int achat_action(action_t *action, int argent);