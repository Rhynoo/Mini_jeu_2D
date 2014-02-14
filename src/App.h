#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

/** defines the path of the file for the processus icon */
#define ICON_FILE "ressources\\img\\p.bmp"

SDL_Surface* App_Init();
void App_Run(SDL_Surface* screen);
void App_End(SDL_Surface* screen);

#endif // APP_H_INCLUDED
