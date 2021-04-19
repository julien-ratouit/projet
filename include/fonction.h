#ifndef _FONCTION_H_
#define _FONCTION_H_

extern void SDL_ExitWithError(const char *message);
extern void SDL_ExitImageWithError(const char *message, void * renderer, void * window);
extern void ajout_texture(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur);
extern void ajout_texture_non_centre(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int y, int x);
extern void aff_action(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *texture_achat1, SDL_Texture *texture_achat2, SDL_Texture *texture_achat3, SDL_Texture *texture_achat4);

#endif