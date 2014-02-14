#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>

#include "Message.h"
#include "Const.h"
#include "Game.h"

#include "Map.h"
#include "Character.h"
#include "Interface.h"

static int Game_Update(Game* game, Character* ch, Map* map, SDL_Surface* screen);
static void Game_Draw(Game* game, Character* ch, Map* map, SDL_Surface* screen);

/** Create a new empty game
 * @return a pointer on the game created
 * @warning the game is created using malloc
*/
Game* Game_Create()
{
    Game* game = (Game*)malloc(sizeof(Game));
    if(game == NULL)
    {
        printf(GAME_CREATION_ERROR);
        exit(-1);
    }

    return game;
}

/** Inits a game
 * @param game : the game to init
 * @note game must have been created before
*/
void Game_Init(Game* game)
{
    SDL_EnableKeyRepeat(35, 10);//permit the repeated press on a key
    SDL_ShowCursor(SDL_DISABLE);//hides the cursor

    game->score = 0;
    game->time = 0;
}

/** Main function of the game, runs the game
 * @param game : the game to play
 * @param ch : the character used in the game
 * @param map : the map used by the game
 * @param screen : the main window of the application
 * @note : the game must have been initialised previously
 * @return the new status of the app
*/
int Game_Play(Game* game, Character* ch, Map* map, SDL_Surface* screen)
{
    SDL_Event event;
    int end_game = NO_OPTION;
    int begin_time = SDL_GetTicks();
    int new_time = 0;
    while (end_game == NO_OPTION)//while we don't want to quit the game
    {
        if(SDL_PollEvent(&event))//we catch the new event if there is one
            switch(event.type)
            {
                case SDL_QUIT:
                    return OPTION_EXIT_TO_DESKTOP;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) // check if the event is a keypressed
                    {
                        case SDLK_UP: // UP ARROW
                            Character_SetDirection(ch,UP);
                            break;
                        case SDLK_DOWN: // DOWN ARROW
                            Character_SetDirection(ch,DOWN);
                            break;
                        case SDLK_RIGHT: // RIGHT ARROW
                            Character_SetDirection(ch,RIGHT);
                            break;
                        case SDLK_LEFT:// LEFT ARROW
                            Character_SetDirection(ch,LEFT);
                            break;
                        case SDLK_RETURN: //the ENTER KEY
                            return OPTION_IN_MENU;
                            break;
                        case SDLK_SPACE:
                            Character_UseSelectedItem(ch);
                            SDL_Delay(75); //prevent double use of an item on one key press
                            break;
                        default :
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                        case SDLK_DOWN:
                        case SDLK_RIGHT:
                        case SDLK_LEFT:
                            Character_SetDirection(ch,NO_DIRECTION);
                            // if we release a key, the character don't move on his own
                            break;
                        default :
                            break;
                    }
                    break;
                default :
                    break;
            }

        new_time = SDL_GetTicks(); //we update the game time
        game->time += new_time - begin_time;
        begin_time = new_time;

        end_game = Game_Update(game, ch, map, screen);

        SDL_Delay(15);
    }
    return end_game;
}

/** Update the game and the character
 * @param game : the game currently played
 * @param ch : the character used by the player
 * @param screen : the main window of the application
 * @return the status of the app
*/
static int Game_Update(Game* game, Character* ch, Map* map, SDL_Surface* screen)
{
    SDL_Event event;
    int status;
    status = Character_Update(ch, map);
    switch(status)
    {
        case STATUS_GAMELOSE:
            SDL_Delay(1000);
            Display_GameOver(screen);

            SDL_WaitEvent(&event);
            while(event.key.keysym.sym == SDLK_END);
            // wait for enter key press

            return OPTION_EXIT_TO_MAIN_MENU;
            break;

        case STATUS_GAMEWIN:
            SDL_Delay(1000);
            Display_GameWin(screen, ch->inventory->gold, game->time);

            SDL_WaitEvent(&event);
            while(event.key.keysym.sym == SDLK_END);
            // wait for enter key press

            return OPTION_EXIT_TO_MAIN_MENU;
            break;

        case STATUS_INGAME:
            Game_Draw(game, ch, map, screen);
            return NO_OPTION;
            break;

        default:
            return NO_OPTION;
            break;
    }
}

/** Draw on the screen the game played
 * @param game : the game currently played
 * @param ch : the character used by the player
 * @param map : the map used by the game
 * @param screen : the main window of the application
*/
static void Game_Draw(Game* game, Character* ch, Map* map, SDL_Surface* screen)
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    Map_Draw(map,screen);

    Character_Draw(ch,screen);

    Interface_Draw(game, ch, screen);

    SDL_Flip(screen);
}

/** Frees a game at the end of it
 * @param game : the game to free
*/
void Game_Destroy(Game* game)
{
    free(game);
}
