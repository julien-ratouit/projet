#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "jour.h" 

//un systeme de compteur qui renvoie vrai quand il atteind sont objectif
void compteur(int ms)
{
	clock_t timeDelay = ms + clock();
	while(timeDelay > clock() );
}
