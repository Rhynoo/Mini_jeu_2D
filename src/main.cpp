#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>

#include "App.h"

int main ( int argc, char** argv )
{
    SDL_Surface* screen = App_Init();

    App_Run(screen);

    App_End(screen);

    printf("Game Ended\n");
    return 0;
}

