#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "fonction.h"
#include "coords.h"
#include "timer.h"
#include "argent.h"
#include "action.h"

action_t * liste_action[10];
action_t * action_acheter[10];
action_t * action_equipe[4];

#endif