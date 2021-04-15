#ifndef _SELF_H_
#define _SELF_H_



extern void aff_texture_self(param_t *parametre, SDL_Texture *texture_self);
extern void lancement_self(param_t *parametre);
extern int achat_selection(param_t *parametre, SDL_Texture *texture_self, SDL_Texture *texture_mess ,char * menu_achat, int pourcentage_baisse_barre, int prix);
#endif