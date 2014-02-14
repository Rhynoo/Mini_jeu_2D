#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include "Const.h"
#include "MenuOption.h"

/** Create a new menu option
 * @return a pointer on the menu option created
 * @warning the menu option is created using malloc
*/
MenuOption* MenuOption_Create()
{
    MenuOption* option =(MenuOption*)malloc(sizeof(MenuOption));
    if(option == NULL)
    {
        printf(OPTION_CREATION_ERROR);
        exit(-1);
    }

    option->text = NULL;

    return option;
}

/** Inits a menu option
 * @param option : the menu option
 * @param treat : the value of the option (corresponds to a specific treatment)
 * @param message : the message of the option
 * @param police : the font used for this option
*/
void MenuOption_Init(MenuOption* option, int treat, char* message, TTF_Font* police)
{
    MenuOption_SetColor(option, 0, 255, 255);

    option->treatment = treat;

    option->text = duplicateString(message);

    option->police = police;
}

/** Return the treatment of a menu
 * @param option : the menu option
 * @return the treatment of the option
*/
int MenuOption_GetTreatment(MenuOption* option)
{
    return option->treatment;
}

/** Sets the color of a menu option
 * @param option : the menu option
 * @param r : the red value of the color
 * @param g : the green value of the color
 * @param b : the blue value of the color
*/
void MenuOption_SetColor(MenuOption* option, int r, int g, int b)
{
    SDL_Color color;

    color.b=b;
    color.g=g;
    color.r=r;

    option->color = color;
}

/** Draw an option on the screen on the requested position
 * @param option : the option to draw
 * @param screen : the main screen of the application
 * @param position : the position where we draw
*/
void MenuOption_Draw(MenuOption* option, SDL_Surface* screen, SDL_Rect* position)
{
    SDL_Surface* text = TTF_RenderText_Solid(option->police, option->text, option->color);

    //Use this line to draw the background of the option
    Draw_Rect(screen, position->x, position->y, text->w, text->h, 0, 0, 0);

    SDL_BlitSurface(text, NULL, screen, position);

    SDL_FreeSurface(text);
}

/** Frees an option
 * @param option : the menu option
*/
void MenuOption_Destroy(MenuOption* option)
{
    free(option->text);
    free(option);
}
