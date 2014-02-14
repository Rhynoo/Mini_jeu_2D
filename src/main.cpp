#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>

#include "App.h"
#include <iostream>
using namespace std;

int main ( int argc, char** argv )
{
	cout << "Game Started" << endl;
    SDL_Surface* screen = App_Init();

    App_Run(screen);

    App_End(screen);

    cout << "Game Ended" << endl;
    return 0;
}

