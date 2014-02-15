#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include "Const.h"
#include "Menu.h"

/** Creates a menu
 * @return a pointer on the created menu
 * @warning the menu is created using malloc
*/
Menu::Menu(int type)
{
    police = TTF_OpenFont(FONT_FILE,20);

    active_option = 0;

    if(type==MAIN_MENU)
        InitApp();
    else
        InitGame();

    MenuOption_SetColor(options[active_option], 255, 0, 0);
}

/** Plays a menu on the screen
 * @param menu : the menu to play
 * @param screen : the main window of the app
 * @return the choice of the user in this menu
*/
int Menu::Play(SDL_Surface* screen)
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
                option = MenuOption_GetTreatment(options[active_option]);
                break;

            case SDLK_UP :
                SetActiveOption(active_option - 1);
                break;

            case SDLK_DOWN :
                SetActiveOption(active_option + 1);
                break;
            default :
                break;
            }
            break;
        default :
            break;
        }
        Draw(screen);
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
void Menu::SetActiveOption(int option)
{
    MenuOption_SetColor(options[active_option], 0, 255, 255);

    active_option = option;

    if(active_option >= option_count)
        active_option = option_count - 1;
    else if (active_option < 0)
        active_option = 0;

    MenuOption_SetColor(options[active_option], 255, 0, 0);
}

/** Draw a menu on the screen
 * @param menu : the menu to draw
 * @param screen : the main window of the app
*/
void Menu::Draw(SDL_Surface* screen)
{
    int i;
    SDL_Rect position = Create_Rect(MENU_INIT_POSITION, MENU_INIT_POSITION, MENU_WIDTH, MENU_HEIGHT);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    for(i=0 ; i<option_count ; i++)
    {
        MenuOption_Draw(options[i], screen, &position);
        position.y += MENU_OPTION_OFFSET;
    }

    SDL_Flip(screen);
}

/** Destroy a menu
 * @param menu : the menu to destroy
*/
Menu::~Menu()
{
    int i;
    for(i=0 ; i<option_count ; i++)
        MenuOption_Destroy(options[i]);

    free(options);

    TTF_CloseFont(police);
}

/** Get the menu option after a click on the menu
 * @param menu : the active menu
 * @param x : the horizontal coordinate of the clic
 * @param y : the vertical coordinate of the clic
 * @return the code of the menu option
 * @note unused because we use the key to control the menu in the app
*/
int Menu::TreatOption(int x, int y)
{
    if((x > MENU_INIT_POSITION) && (x < (MENU_INIT_POSITION + MENU_WIDTH))
        && (y > MENU_INIT_POSITION))
    {
        int i = 0;
        while((i < option_count) &&
               (y < MENU_INIT_POSITION + (option_count - 1)*(MENU_OPTION_OFFSET + MENU_HEIGHT)))
        {
            if((y >= (MENU_INIT_POSITION + i*MENU_OPTION_OFFSET))
               && (y <= (MENU_INIT_POSITION + MENU_HEIGHT + i*(MENU_OPTION_OFFSET))))
            {
                //we have the option, we can treat it
                return MenuOption_GetTreatment(options[i]);
            }
            i++;
        }
    }
    return OPTION_IN_MENU;
}

/** Init the menu as a game menu
 * @param menu : the menu to init
*/
void Menu::InitGame()
{
    option_count = 5;

    options = (MenuOption**)malloc(sizeof(MenuOption*)*option_count);
    if(options == NULL)
    {
        printf(MENU_OPTION_ALLOC_ERROR);
        exit(-1);
    }

    MenuOption* option1 = MenuOption_Create();
    MenuOption_Init(option1, OPTION_RESUME_GAME, "Resume Game", police);

    MenuOption* option2 = MenuOption_Create();
    MenuOption_Init(option2, OPTION_SAVE_GAME, "Save Game", police);

    MenuOption* option3 = MenuOption_Create();
    MenuOption_Init(option3, OPTION_LOAD_GAME, "Load Game", police);

    MenuOption* option4 = MenuOption_Create();
    MenuOption_Init(option4, OPTION_EXIT_TO_MAIN_MENU, "Exit to main menu", police);

    MenuOption* option5 = MenuOption_Create();
    MenuOption_Init(option5, OPTION_EXIT_TO_DESKTOP, "Exit Game", police);

    options[0] = option1;
    options[1] = option2;
    options[2] = option3;
    options[3] = option4;
    options[4] = option5;
}

/** Inits the menu as the first menu of the app
 * @param menu: the menu
*/
void Menu::InitApp()
{
    option_count = 3;

    options = (MenuOption**)malloc(sizeof(MenuOption*)*(option_count));
    if(options == NULL)
    {
        printf(MENU_OPTION_ALLOC_ERROR);
        exit(-1);
    }

    MenuOption* option1 = MenuOption_Create();
    MenuOption_Init(option1, OPTION_NEW_GAME, "New Game", police);

    MenuOption* option2 = MenuOption_Create();
    MenuOption_Init(option2, OPTION_LOAD_GAME, "Load game", police);

    MenuOption* option3 = MenuOption_Create();
    MenuOption_Init(option3, OPTION_EXIT_TO_DESKTOP, "Exit Game", police);

    options[0] = option1;
    options[1] = option2;
    options[2] = option3;
}
