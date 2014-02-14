#ifndef MAPBLOCK_H_INCLUDED
#define MAPBLOCK_H_INCLUDED

#include <SDL/SDL.h>
#include "Item.h"

#define BLOC_WIDTH 32
#define BLOC_HEIGHT 32

#define BLOCK_CREATION_ERROR "Impossible de creer le bloc"

/** the structure of a map block*/
typedef struct
{
    /** height of a block */
    int height;
    /** width of a block */
    int width;
    /** the value of a block in order to determinate his color/picture */
    int value;
} MapBlock;

MapBlock* MapBlock_Create();
void MapBlock_Init(MapBlock* block, int val);
int MapBlock_GetValue(MapBlock* block);
void MapBlock_Draw(MapBlock* block, SDL_Surface* screen, SDL_Rect* position);
void MapBlock_Destroy(MapBlock* block);
#endif // MAPBLOCK_H_INCLUDED
