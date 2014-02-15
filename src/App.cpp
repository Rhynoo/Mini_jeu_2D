#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>

#include "App.h"
#include "Menu.h"
#include "Game.h"
#include "Const.h"
#include "Message.h"

static int App_InGame(SDL_Surface* screen, Game* game, Map* map, Character* ch);

/** Initialize the app by creating the main window (SDL_surface) of the app
 * @return the main window of the application
 * @note also initialize SDl_ttf
*/
SDL_Surface* App_Init()
{
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    if (TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de SDL TTF \n");
        exit(-1);
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    SDL_WM_SetCaption("Mini jeu 2D SDL", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP(ICON_FILE), NULL);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, 540, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if (screen == NULL)
    {
        printf("Unable to set 640x540 video: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_Flip(screen);//draws on the screen

    DisplayTitleScreen(screen);

    return screen;
}

/** Runs the app, initialising the game and playing it
 * @param screen : the main window of the application
*/
void App_Run(SDL_Surface* screen)
{
    Menu* menu;
    Game* game;
    Map* map = Map_Create();
    Character* ch = Character_Create();

    int code = OPTION_IN_MENU;
    int end_app = 0;
    menu = new Menu(MAIN_MENU);
    while(end_app == 0)
    {
        switch(code)
        {
            case OPTION_IN_MENU:
                SDL_Delay(250);
                code = menu->Play(screen);
                break;
            case OPTION_NEW_GAME:
                //new game
                game = new Game();
                Map_Init(map);
                Character_Init(ch, MAIN_CHAR_FILE);
                code = App_InGame(screen, game, map, ch);
                break;
            case OPTION_EXIT_TO_DESKTOP:
                end_app = 1;
                break;
            default:
                code = OPTION_IN_MENU;
                break;
        }

    }
    //end of the game
    delete game;
    delete menu;
    Character_Destroy(ch);
    Map_Destroy(map);
}

/** Runs the app while in a game status
 * @param screen : the main screen of the application
 * @param game : the game the player want to play
 * @param map : the map where the player plays
 * @param ch : the character played by the player
 * @return a code that indicates if we want to quit the game or return to the main menu
 * @warning all the params must have been initialised before in App_Run
*/
static int App_InGame(SDL_Surface* screen, Game* game, Map* map, Character* ch)
{
    Menu* game_menu = new Menu(GAME_MENU);

    int code = OPTION_RESUME_GAME;
    int end_game = 0;
    while(end_game == 0)
    {
        switch(code)
        {
        case OPTION_IN_MENU:
            SDL_Delay(250);
            code = game_menu->Play(screen);
            break;
        case OPTION_RESUME_GAME:
            code = game->Play(ch, map, screen);
            break;
        case OPTION_EXIT_TO_DESKTOP:
            end_game = OPTION_EXIT_TO_DESKTOP;
            break;
        case OPTION_EXIT_TO_MAIN_MENU:
            end_game = OPTION_EXIT_TO_MAIN_MENU;
            break;
        default:
            code = OPTION_RESUME_GAME;
            break;
        }
    }

    delete game_menu;

    return end_game;
}

/** Ends the application
 * @param screen : the main window of the application
 * @note exits SDL and TFF
*/
void App_End(SDL_Surface* screen)
{
    TTF_Quit();
    SDL_FreeSurface(screen);
    SDL_Quit();
}
