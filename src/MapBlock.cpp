#include <SDL\SDL.h>

#include "MapBlock.h"
#include "Const.h"

/** Creates a map block and inits it
 * @param val : the value of the map block
 * @return a pointer on the map block created
 * @warning the map block is created using malloc
*/
MapBlock* MapBlock_Create()
{
    MapBlock* block = (MapBlock*) malloc(sizeof(MapBlock));
    if(block == NULL)
    {
        printf(BLOCK_CREATION_ERROR);
        exit(-1);
    }

    return block;
}

/** Inits a map block
 * @param block : the block to init
 * @param val ; the value of the block
*/
void MapBlock_Init(MapBlock* block, int val)
{
    block->width = BLOC_WIDTH;
    block->height = BLOC_HEIGHT;
    block->value = val;
}

int MapBlock_GetValue(MapBlock* block)
{
    return block->value;
}

/** Draw a map block on a screen at his position
 * @param block : the map block to draw on the screen
 * @param screen : the main window of the application
 * @param position : the position of the block on the screen
*/
void MapBlock_Draw(MapBlock* block, SDL_Surface* screen, SDL_Rect* position)
{
    SDL_Surface* surface = NULL;

    surface = SDL_CreateRGBSurface(SDL_HWSURFACE, BLOC_WIDTH, BLOC_HEIGHT, 16, 0, 0, 0, 0);

    switch(block->value)
    {
        case DANGEROUS:
            SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 255, 0, 0));
            break;
        case WALKABLE:
            SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
            break;
        case 1:
            SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            break;
        case WIN:
            SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 0, 0, 255));
            break;
        default:
            SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
            break;
    }

    SDL_BlitSurface(surface,NULL,screen,position);

    SDL_FreeSurface(surface);
}

/** Free a map block
 * @param block : the block to free
*/
void MapBlock_Destroy(MapBlock* block)
{
    free(block);
}
