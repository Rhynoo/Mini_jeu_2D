#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Map.h"
#include "Character.h"

/** an error message that apears when the game's allocation fails*/
#define GAME_CREATION_ERROR "Impossible de creer le jeu"

/** the game structure */
typedef struct
{
    /** the score of the player */
    int score;
    /** the time spent in game */
    unsigned int time;
} Game;

Game* Game_Create();
void Game_Init(Game* game);
int Game_Play(Game* game, Character* ch, Map* map, SDL_Surface* screen);
void Game_Destroy(Game* game);

#endif // GAME_H_INCLUDED
