extern void init_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre);
extern void init_barre_depression(SDL_Renderer *renderer, SDL_Rect *barre);
extern void update_barre_sonore(SDL_Renderer *renderer, SDL_Rect *barre, int score);
extern void update_barre_depression(SDL_Renderer *renderer, SDL_Rect *barre_depression, SDL_Rect *barre_sonore, int score);