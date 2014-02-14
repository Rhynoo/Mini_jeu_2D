#ifndef MAPSECTION_H_INCLUDED
#define MAPSECTION_H_INCLUDED

#include "MapBlock.h"
#include "MapCtxObject.h"

#define SECTION_WIDTH 20
#define SECTION_HEIGHT 15

#define SECTION_CREATION_ERROR "impossible de crée la section"
#define SECTION_BLOCK_ALLOC_ERROR "impossible d'allouer la matrice des blocks de la section"
#define SECTION_CTX_ALLOC_ERROR "impossible d'allouer la matrice des objets contextuels de la section"
#define SECTION_FILE_ERROR "impossible de charger le fichier de la section"
#define SECTION_FILE_READ_ERROR "Erreur lors de la lecture du fichier de la section"

/** the path to the directory of the map blocks files*/
#define MAP_BLOCK_FILES "ressources\\map\\section\\"
/** the path to the directory of the map ctx files*/
#define MAP_CTX_FILES "ressources\\map\\ctx\\"

/** the structure of a map section*/
typedef struct
{
    /** the horizontal coordinate of the section in the map */
    int x;
    /** the vertical coordinate of the section in the map */
    int y;
    /** number of blocks vertically */
    int height;
    /** number of blocks horizontally */
    int width;
    /** matrix of map blocks */
    MapBlock*** blocks;
    /** matrix of map contextuel objects */
    MapCtxObject*** ctx_objects;
} MapSection;

MapSection* MapSection_Create();
void MapSection_Init(MapSection* section, int x, int y);
void MapSection_Draw(MapSection* section, SDL_Surface* screen);
void MapSection_LoadBlocks(MapSection* section);
void MapSection_LoadCTX(MapSection* section);
void MapSection_Destroy(MapSection* section);
int MapSection_NearBlock(MapSection* section,int move_x, int move_y);
MapCtxObject* MapSection_NearCtx(MapSection* section,int move_x, int move_y);
#endif // MAPSECTION_H_INCLUDED
