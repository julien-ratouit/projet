extern void SDL_ExitWithFailure(const char *message);
extern void SDL_ExitImageWithError(const char *message, void * renderer, void * window);
extern void ajout_texture(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur);
extern void ajout_texture_non_centre(SDL_Texture *texture ,const char * lien_img , SDL_Renderer *renderer, SDL_Window *window, int hauteur, int largeur);