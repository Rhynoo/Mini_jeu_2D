#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "MapSection.h"

#define MAP_CREATION_ERROR "impossible de creer la carte"
#define MAP_SECTION_ALLOC_ERROR "impossible d'allouer les tronçons de carte"
/** the number of map sections in a map horizontally */
#define MAP_WIDTH 3
/** the number of map sections in a map verticaly*/
#define MAP_HEIGHT 3

/** the structure of a map*/
typedef struct
{
    /** the map height : the number of map section vertically */
    int height;
    /** the map width : the number of map section horizontally */
    int width;
    /** the section where the player is currently */
    MapSection* active_section;
    /** the matrix of section tabs */
    MapSection*** Section_tab;
} Map;

Map* Map_Create();
void Map_Init(Map* map);
void Map_Draw(Map* map,SDL_Surface* screen);
void Map_Destroy(Map* map);
void Map_SetActiveSection(Map* map, int x, int y);
MapCtxObject* Map_NearCtx(Map* map, int move_x, int move_y);
int Map_NearBlock(Map* map, int move_x, int move_y);

#endif // MAP_H_INCLUDED
