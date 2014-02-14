#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL\SDL_ttf.h>
#include "MenuOption.h"

#define MENU_CREATION_ERROR "Impossible de creer le menu"
#define MENU_OPTION_ALLOC_ERROR "impossible d'allouer le tableau d'option du menu"

#define FONT_FILE "ressources\\font\\Tr2n.ttf"

#define MAIN_MENU 0
#define GAME_MENU 1

#define MENU_INIT_POSITION 100
#define MENU_OPTION_OFFSET 50
#define MENU_WIDTH 250
#define MENU_HEIGHT 20

typedef struct
{
    /** the number of options */
    int option_count;
    /** the selected option */
    int active_option;
    /** the array of options */
    MenuOption** options;
    /** the police used in the menu */
    TTF_Font* police;
}Menu;

Menu* Menu_Create();
void Menu_Init(Menu* menu, int type);
int Menu_Play(Menu* menu, SDL_Surface* screen);
void Menu_SetActiveOption(Menu* menu, int option);
void Menu_Draw(Menu* menu, SDL_Surface* screen);
void Menu_Destroy(Menu* menu);
int Menu_TreatOption(Menu* menu, int x, int y);

#endif // MENU_H_INCLUDED
