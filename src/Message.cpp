#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "message.h"
#include "const.h"

/** Display a screen title at the begenning of the app
 * @param screen : the main window of the application
*/
void DisplayTitleScreen(SDL_Surface* screen)
{
    SDL_Surface* img = LoadImage(TITLE_SCREEN_FILE);
    SDL_Rect position;
    int i;

    position.x = (screen->w - img->w)/2;
    position.y = (screen->h - img->h)/2;

    for(i = 0 ; i<255 ; i+=5)
    {
        SDL_SetAlpha(img, SDL_SRCALPHA, i);
        SDL_BlitSurface(img, NULL, screen, &position);
        SDL_Flip(screen);
    }

    for(i = 255 ; i>0 ; i-=10)
    {
        SDL_SetAlpha(img, SDL_SRCALPHA, i);
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
        SDL_BlitSurface(img, NULL, screen, &position);
        SDL_Flip(screen);
    }
    SDL_Delay(250);

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,255,255,255));
    SDL_Flip(screen);//draws on the screen

    SDL_FreeSurface(img);
}

/** Display a game over
 * @param screen : the main window of the application
*/
void Display_GameOver(SDL_Surface* screen)
{
    SDL_Rect position;
    SDL_Color color;
    color.b=0;
    color.g=0;
    color.r=255;

    TTF_Font* police = TTF_OpenFont(FONT_FILE,50);
    SDL_Surface* text = TTF_RenderText_Solid(police, "GAME OVER", color);

    position.x = (screen->w - text->w)/2;
    position.y = (screen->h - text->h)/2;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,255,255,255));
    SDL_BlitSurface(text, NULL, screen, &position);

    SDL_FreeSurface(text);
    TTF_CloseFont(police);

    SDL_Flip(screen);
}

/** Display a game won message
 * @param screen : the main window of the application
 * @param score : the player's score
 * @param time : the game time
*/
void Display_GameWin(SDL_Surface* screen, int score, int time)
{
    SDL_Rect position;
    SDL_Color color;
    color.b=0;
    color.g=0;
    color.r=0;

    TTF_Font* police = TTF_OpenFont(FONT_FILE,40);
    SDL_Surface* text1 = TTF_RenderText_Solid(police, "You have won the game", color);
    SDL_Surface* text2 = TTF_RenderText_Solid(police, "Press enter", color);

    position.x = (screen->w - text1->w)/2;
    position.y = 100;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,255,255,255));
    SDL_BlitSurface(text1, NULL, screen, &position);

    char* s= (char*)malloc(sizeof(char)*14);
    if(s == NULL)
    {
        printf("Message Win Error");
        exit(-1);
    }

    char* stime = Parse_Time(time);
    sprintf(s, "In %s", stime);

    char* gold = (char*)malloc(sizeof(char)*9);
    if(gold == NULL)
    {
        printf("Message Win Error");
        exit(-1);
    }

    sprintf(gold, "With %d Score", score);

    position.y += 50;

    SDL_Surface* text3 = TTF_RenderText_Solid(police, s, color);
    SDL_BlitSurface(text3, NULL, screen, &position);

    position.y += 50;

    SDL_Surface* text4 = TTF_RenderText_Solid(police, gold, color);
    SDL_BlitSurface(text4, NULL, screen, &position);

    position.y += 50;

    SDL_BlitSurface(text2, NULL, screen, &position);

    SDL_FreeSurface(text1);
    SDL_FreeSurface(text2);
    SDL_FreeSurface(text3);
    SDL_FreeSurface(text4);

    TTF_CloseFont(police);

    free(s);
    free(stime);
    free(gold);

    SDL_Flip(screen);
}
