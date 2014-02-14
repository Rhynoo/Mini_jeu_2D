#include <SDL\SDL.h>
#include "Const.h"

#include "Map.h"

/** Create the map of the player
 * @return a pointer on the map created
 * @warning the map is created using malloc
*/
Map* Map_Create()
{
    Map* map = (Map*) malloc(sizeof(Map));
    if(map == NULL)
    {
        printf(MAP_CREATION_ERROR);
        exit(-1);
    }

    map->active_section = NULL;
    map->Section_tab = NULL;

    return map;
}

/** Inits a map
 * @param map : the map to init
 * @note the map must have been created previously
*/
void Map_Init(Map* map)
{
    int i,j;
    map->width = MAP_WIDTH;
    map->height = MAP_HEIGHT;

    map->Section_tab = (MapSection***)malloc(sizeof(MapSection**)*MAP_HEIGHT);
    if(map->Section_tab == NULL)
    {
        printf(MAP_SECTION_ALLOC_ERROR);
        exit(-1);
    }
    for(i = 0 ; i < map->height ; i++)
    {
        map->Section_tab[i] = (MapSection**)malloc(sizeof(MapSection*)*MAP_WIDTH);
        if(map->Section_tab[i] == NULL)
        {
            printf(MAP_SECTION_ALLOC_ERROR);
            exit(-1);
        }
        for(j = 0 ; j < map->width ; j++)
        {
            map->Section_tab[i][j] = MapSection_Create();
            MapSection_Init(map->Section_tab[i][j], i, j);
        }
    }
    // the first section we play is the defined here
    map->active_section = map->Section_tab[0][0];
}

/** Draw the map on the screen
 * @param map : the map to draw on the screen
 * @param screen : the main window of the application
*/
void Map_Draw(Map* map,SDL_Surface* screen)
{
    MapSection_Draw(map->active_section, screen);
}

/** Frees a map
 * @param map : the map to free
*/
void Map_Destroy(Map* map)
{
    int i, j;
    if(map->Section_tab != NULL)
    {
        for(i = 0 ; i < map->height ; i++)
        {
            for(j = 0 ; j < map->width ; j++)
            {
                MapSection_Destroy(map->Section_tab[i][j]);
            }
            free(map->Section_tab[i]);
        }
    }
    free(map->Section_tab);
    free(map);
}

/** Set the active Section of a map
 * @param map : the map
 * @param x : the new horizontal coordinate of the section
 * @param y : the new vertical coordinate of the section
*/
void Map_SetActiveSection(Map* map, int x, int y)
{
    map->active_section = map->Section_tab[x][y];
}

/** Get the value of a MapBlock according to the move of an object
 * @param map : the map where the player is
 * @param move_x : the horizontal move
 * @param move_y : the vertical move
 * @return the value of the nearest block from the player
*/
int Map_NearBlock(Map* map, int move_x, int move_y)
{
    return MapSection_NearBlock(map->active_section, move_x, move_y);
}

/** Get the id of a Contextual object according to the move of an object
 * @param mpa : the map where the player is
 * @param move_x : the horizontal move
 * @param move_y : the vertical move
 * @return a pointer on of the nearest ctx from the player
*/
MapCtxObject* Map_NearCtx(Map* map, int move_x, int move_y)
{
    return MapSection_NearCtx(map->active_section, move_x, move_y);
}
