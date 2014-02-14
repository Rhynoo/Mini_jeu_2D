#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include "Const.h"
#include "Menu.h"

static void Menu_InitGame(Menu* menu);
static void Menu_InitApp(Menu* menu);

/** Creates a menu
 * @return a pointer on the created menu
 * @warning the menu is created using malloc
*/
Menu* Menu_Create()
{
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    if(menu == NULL)
    {
        printf(MENU_CREATION_ERROR);
        exit(-1);
    }

    menu->police = NULL;
    menu->options = NULL;

    return menu;
}

/** Inits a menu
 * @param menu : the menu to init
 * @param type : the type of the menu (main menu or game menu)
 * @note the menu must have been created previously
*/
void Menu_Init(Menu* menu, int type)
{
    menu->police = TTF_OpenFont(FONT_FILE,20);

    menu->active_option = 0;

    if(type==MAIN_MENU)
        Menu_InitApp(menu);
    else
        Menu_InitGame(menu);

    MenuOption_SetColor(menu->options[menu->active_option], 255, 0, 0);
}

/** Plays a menu on the screen
 * @param menu : the menu to play
 * @param screen : the main window of the app
 * @return the choice of the user in this menu
*/
int Menu_Play(Menu* menu, SDL_Surface* screen)
{
    SDL_Event event;

    int option=0;
    while(option == 0)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            option = OPTION_EXIT_TO_DESKTOP;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE :
                option = OPTION_RESUME_GAME;
                break;

            case SDLK_RETURN :
                option = MenuOption_GetTreatment(menu->options[menu->active_option]);
                break;

            case SDLK_UP :
                Menu_SetActiveOption(menu, menu->active_option - 1);
                break;

            case SDLK_DOWN :
                Menu_SetActiveOption(menu, menu->active_option + 1);
                break;
            default :
                break;
            }
            break;
        default :
            break;
        }
        Menu_Draw(menu, screen);
        SDL_Delay(100);
    }
    SDL_Delay(100);
    return option;
}

/** Set the new active Option of a menu
 * @param menu : the menu played
 * @param option : the int that defines the number of the option
 * @note this function set the older active option as a non-active option
*/
void Menu_SetActiveOption(Menu* menu, int option)
{
    MenuOption_SetColor(menu->options[menu->active_option], 0, 255, 255);

    menu->active_option = option;

    if(menu->active_option >= menu->option_count)
        menu->active_option = menu->option_count - 1;
    else if (menu->active_option < 0)
        menu->active_option = 0;

    MenuOption_SetColor(menu->options[menu->active_option], 255, 0, 0);
}

/** Draw a menu on the screen
 * @param menu : the menu to draw
 * @param screen : the main window of the app
*/
void Menu_Draw(Menu* menu, SDL_Surface* screen)
{
    int i;
    SDL_Rect position = Create_Rect(MENU_INIT_POSITION, MENU_INIT_POSITION, MENU_WIDTH, MENU_HEIGHT);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    for(i=0 ; i<menu->option_count ; i++)
    {
        MenuOption_Draw(menu->options[i], screen, &position);
        position.y += MENU_OPTION_OFFSET;
    }

    SDL_Flip(screen);
}

/** Destroy a menu
 * @param menu : the menu to destroy
*/
void Menu_Destroy(Menu* menu)
{
    int i;
    for(i=0 ; i<menu->option_count ; i++)
        MenuOption_Destroy(menu->options[i]);

    free(menu->options);

    TTF_CloseFont(menu->police);
    free(menu);
}

/** Get the menu option after a click on the menu
 * @param menu : the active menu
 * @param x : the horizontal coordinate of the clic
 * @param y : the vertical coordinate of the clic
 * @return the code of the menu option
 * @note unused because we use the key to control the menu in the app
*/
int Menu_TreatOption(Menu* menu, int x, int y)
{
    if((x > MENU_INIT_POSITION) && (x < (MENU_INIT_POSITION + MENU_WIDTH))
        && (y > MENU_INIT_POSITION))
    {
        int i = 0;
        while((i < menu->option_count) &&
               (y < MENU_INIT_POSITION + (menu->option_count - 1)*(MENU_OPTION_OFFSET + MENU_HEIGHT)))
        {
            if((y >= (MENU_INIT_POSITION + i*MENU_OPTION_OFFSET))
               && (y <= (MENU_INIT_POSITION + MENU_HEIGHT + i*(MENU_OPTION_OFFSET))))
            {
                //we have the option, we can treat it
                return MenuOption_GetTreatment(menu->options[i]);
            }
            i++;
        }
    }
    return OPTION_IN_MENU;
}

/** Init the menu as a game menu
 * @param menu : the menu to init
*/
static void Menu_InitGame(Menu* menu)
{
    menu->option_count = 5;

    menu->options = (MenuOption**)malloc(sizeof(MenuOption*)*menu->option_count);
    if(menu->options == NULL)
    {
        printf(MENU_OPTION_ALLOC_ERROR);
        exit(-1);
    }

    MenuOption* option1 = MenuOption_Create();
    MenuOption_Init(option1, OPTION_RESUME_GAME, "Resume Game", menu->police);

    MenuOption* option2 = MenuOption_Create();
    MenuOption_Init(option2, OPTION_SAVE_GAME, "Save Game", menu->police);

    MenuOption* option3 = MenuOption_Create();
    MenuOption_Init(option3, OPTION_LOAD_GAME, "Load Game", menu->police);

    MenuOption* option4 = MenuOption_Create();
    MenuOption_Init(option4, OPTION_EXIT_TO_MAIN_MENU, "Exit to main menu", menu->police);

    MenuOption* option5 = MenuOption_Create();
    MenuOption_Init(option5, OPTION_EXIT_TO_DESKTOP, "Exit Game", menu->police);

    menu->options[0] = option1;
    menu->options[1] = option2;
    menu->options[2] = option3;
    menu->options[3] = option4;
    menu->options[4] = option5;
}

/** Inits the menu as the first menu of the app
 * @param menu: the menu
*/
static void Menu_InitApp(Menu* menu)
{
    menu->option_count = 3;

    menu->options = (MenuOption**)malloc(sizeof(MenuOption*)*(menu->option_count));
    if(menu->options == NULL)
    {
        printf(MENU_OPTION_ALLOC_ERROR);
        exit(-1);
    }

    MenuOption* option1 = MenuOption_Create();
    MenuOption_Init(option1, OPTION_NEW_GAME, "New Game", menu->police);

    MenuOption* option2 = MenuOption_Create();
    MenuOption_Init(option2, OPTION_LOAD_GAME, "Load game", menu->police);

    MenuOption* option3 = MenuOption_Create();
    MenuOption_Init(option3, OPTION_EXIT_TO_DESKTOP, "Exit Game", menu->police);

    menu->options[0] = option1;
    menu->options[1] = option2;
    menu->options[2] = option3;
}
