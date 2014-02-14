#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>

#include "Interface.h"
#include "Character.h"
#include "Game.h"
#include "Const.h"

static void Interface_DrawBorder(Game* game, SDL_Surface* screen);
static void Interface_DrawGold(Character* ch, SDL_Surface* screen);
static void Interface_DrawTime(Game* game, SDL_Surface* screen);
static void Interface_DrawLifeBar(Character* ch, SDL_Surface* screen);
static void Interface_DrawItem(Inventory* inv, SDL_Surface* screen);

/** Draws the interface of the game
 * @param game : the game played
 * @param ch : the character used by the player
 * @param screen : the main screen of the application
*/
void Interface_Draw(Game* game, Character* ch, SDL_Surface* screen)
{
    Interface_DrawBorder(game, screen);

    Interface_DrawGold(ch, screen);
    Interface_DrawLifeBar(ch, screen);
    Interface_DrawTime(game, screen);
    Interface_DrawItem(ch->inventory, screen);
}

/** Draw the border on the screen
 * @param game : the game played
 * @param screen : the main screen of the app where the border is drown
 * @note the border contains usefull information like life, items, etc..
*/
static void Interface_DrawBorder(Game* game, SDL_Surface* screen)
{
    Draw_Rect(screen, 0, SCREEN_HEIGHT, SCREEN_WIDTH, 540 - SCREEN_HEIGHT, 0, 0, 0);
}

/** Draw on the border the ammount of gold of the player
 * @param game : the game actually played
 * @param screen : the surface where we draw
*/
static void Interface_DrawGold(Character* ch, SDL_Surface* screen)
{
    SDL_Rect position = Create_Rect(250, SCREEN_HEIGHT + 10, 0, 0);

    SDL_Color color;

    char* gold = (char*)malloc(sizeof(char)*9);
    if(gold == NULL)
    {
        printf(GOLD_DRAW_ERROR);
        exit(-1);
    }

    color.b = 255;
    color.g = 255;
    color.r = 255;

    sprintf(gold, "Gold %.3d", ch->inventory->gold);

    TTF_Font* police = TTF_OpenFont(FONT_FILE,15);
    SDL_Surface* text = TTF_RenderText_Solid(police, gold, color);

    SDL_BlitSurface(text, NULL, screen, &position);

    SDL_FreeSurface(text);
    TTF_CloseFont(police);
    free(gold);
}

/** Draw on the border the time the player played this game
 * @param game : the game actually played
 * @param screen : the surface where we draw
*/
static void Interface_DrawTime(Game* game, SDL_Surface* screen)
{
    SDL_Rect position = Create_Rect(250, SCREEN_HEIGHT + 30, 0, 0);
    SDL_Color color;

    char* s = (char*)malloc(sizeof(char)*14);
    if(s == NULL)
    {
        printf(TIME_DRAW_ERROR);
        exit(-1);
    }

    char* time = Parse_Time(game->time);

    color.b = 255;
    color.g = 255;
    color.r = 255;

    sprintf(s, "Time %s", time);

    TTF_Font* police = TTF_OpenFont(FONT_FILE,15);
    SDL_Surface* text = TTF_RenderText_Solid(police, s, color);

    SDL_BlitSurface(text, NULL, screen, &position);

    SDL_FreeSurface(text);
    TTF_CloseFont(police);
    free(time);
    free(s);
}

/** Draw the selected item on the screen
 * @param inv : the inventory of the player
 * @param screen : the main screen of the application
*/
static void Interface_DrawItem(Inventory* inv, SDL_Surface* screen)
{
    Item* it = inv->selected_item;

    SDL_Rect position = Create_Rect(400, SCREEN_HEIGHT + 10, 0, 0);
    SDL_Color color;

    color.b=255;
    color.g=255;
    color.r=255;

    TTF_Font* police = TTF_OpenFont(FONT_FILE,15);
    SDL_Surface* text = TTF_RenderText_Solid(police, "Item", color);

    SDL_BlitSurface(text, NULL, screen, &position);

    position.y += 20;
    if(it != NULL)
        Item_Draw(it, screen, &position);

    SDL_FreeSurface(text);
    TTF_CloseFont(police);
}

/** Draw the character's life bar on the screen
 * @param ch : the character played
 * @param screen : the screen where the life bar is drown
*/
static void Interface_DrawLifeBar(Character* ch, SDL_Surface* screen)
{
    SDL_Rect position;
    SDL_Color color;

    color.b=255;
    color.g=255;
    color.r=255;

    TTF_Font* police = TTF_OpenFont(FONT_FILE,15);
    SDL_Surface* text = TTF_RenderText_Solid(police, "Life", color);

    //draws the sub life bar
    Draw_Rect(screen, 50, SCREEN_HEIGHT + 10, MAX_LIFE, 11, 0, 0, 255);
    // draws the life bar
    Draw_Rect(screen, 50, SCREEN_HEIGHT + 10, ch->life, 10, 255, 0, 0);

    position.x = 10;
    position.y = SCREEN_HEIGHT + 10;
    SDL_BlitSurface(text, NULL, screen, &position);

    SDL_FreeSurface(text);
    TTF_CloseFont(police);
}
