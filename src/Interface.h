#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "Game.h"
#include "Character.h"

/** an error message that apears when the gold draw on the interface fails*/
#define GOLD_DRAW_ERROR "Impossible de déssiner le nombre de gold"
/** an error message that apears when the time draw on the interface fails*/
#define TIME_DRAW_ERROR "Impossible de déssiner le temps de jeu"

void Interface_Draw(Game* game, Character* ch, SDL_Surface* screen);

#endif // INTERFACE_H_INCLUDED
