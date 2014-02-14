#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <SDL/SDL.h>

#define TITLE_SCREEN_FILE "ressources\\img\\poly.bmp"

void DisplayTitleScreen(SDL_Surface* screen);
void Display_GameOver(SDL_Surface* screen);
void Display_GameWin(SDL_Surface* screen, int score, int time);

#endif // MESSAGE_H_INCLUDED
