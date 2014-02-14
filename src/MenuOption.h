#ifndef MENUOPTION_H_INCLUDED
#define MENUOPTION_H_INCLUDED

#include "Const.h"

#define OPTION_CREATION_ERROR "Impossible de crée l'option"

typedef struct
{
    /** the color of the option */
    SDL_Color color;
    /** the text information of the option */
    char* text;
    /** the code of the option that describes its treatement */
    int treatment;
    /** the police of the option */
    TTF_Font* police;
}MenuOption;

MenuOption* MenuOption_Create();
void MenuOption_Init(MenuOption* option, int treatment, char* message, TTF_Font* police);
void MenuOption_Draw(MenuOption* option, SDL_Surface* screen, SDL_Rect* position);
void MenuOption_Destroy(MenuOption* option);
void MenuOption_SetColor(MenuOption* option, int r, int g, int b);
int MenuOption_GetTreatment(MenuOption* option);
#endif // MENUOPTION_H_INCLUDED
