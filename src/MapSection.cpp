#include <stdio.h>
#include <stdlib.h>
#include <SDL\SDL.h>
#include "Const.h"
#include "MapSection.h"

static char* generate_filename(int x, int y, char* path);

/** Creates a map section
 * @return a pointer on the map section created
 * @warning the map section is created using malloc
*/
MapSection* MapSection_Create()
{
    MapSection* section = (MapSection*) malloc(sizeof(MapSection));
    if(section == NULL)
    {
        printf(SECTION_CREATION_ERROR);
        exit(-1);
    }

    int i;

    section->blocks = (MapBlock***)malloc(sizeof(MapBlock**)*SECTION_HEIGHT);
    if(section->blocks == NULL)
    {
        printf(SECTION_BLOCK_ALLOC_ERROR);
        exit(-1);
    }
    for(i=0 ; i < SECTION_HEIGHT ; i++)
    {
        section->blocks[i] = (MapBlock**)malloc(sizeof(MapBlock*)*SECTION_WIDTH);
        if(section->blocks[i] == NULL)
        {
            printf(SECTION_BLOCK_ALLOC_ERROR);
            exit(-1);
        }
    }

    section->ctx_objects = (MapCtxObject***)malloc(sizeof(MapCtxObject**)*SECTION_HEIGHT);
    if(section->ctx_objects == NULL)
    {
        printf(SECTION_CTX_ALLOC_ERROR);
        exit(-1);
    }
    for(i=0 ; i < SECTION_HEIGHT ; i++)
    {
        section->ctx_objects[i] = (MapCtxObject**)malloc(sizeof(MapCtxObject*)*SECTION_WIDTH);
        if(section->ctx_objects[i] == NULL)
        {
            printf(SECTION_CTX_ALLOC_ERROR);
            exit(-1);
        }
    }

    return section;
}

/** Inits a map section
 * @param section : the map section to init
 * @param x : the number of the section horizontally
 * @param y : the number of the section vertically
 * @note the the map must have been created before
*/
void MapSection_Init(MapSection* section, int x, int y)
{
    section->height = SECTION_HEIGHT;
    section->width = SECTION_WIDTH;

    section->x = x;
    section->y = y;

    MapSection_LoadBlocks(section);

    MapSection_LoadCTX(section);
}

/** Draw a map section on the screen
 * @param section : the map section to draw on the screen
 * @param screen : the main window of the application
*/
void MapSection_Draw(MapSection* section, SDL_Surface* screen)
{
    int i,j;
    SDL_Rect position;

    for(i = 0 ; i<section->height ; i++)
    {
        for(j = 0 ; j<section->width ; j++)
        {
            position.x = j * BLOC_HEIGHT;
            position.y = i * BLOC_WIDTH;
            MapBlock_Draw(section->blocks[i][j], screen, &position);
            MapCtxObject_Draw(section->ctx_objects[i][j], screen, &position);
        }
    }
}

/** Frees a map section
 * @param section : the map section to free
*/
void MapSection_Destroy(MapSection* section)
{
    int i, j;
    for(i = 0 ; i < section->height ; i++)
    {
        for(j = 0 ; j < section->width ; j++)
        {
            MapBlock_Destroy(section->blocks[i][j]);
        }
        free(section->blocks[i]);
    }
    free(section->blocks);

    for(i = 0 ; i < section->height ; i++)
    {
        for(j = 0 ; j < section->width ; j++)
        {
            MapCtxObject_Destroy(section->ctx_objects[i][j]);
        }
        free(section->ctx_objects[i]);
    }
    free(section->ctx_objects);

    free(section);
}

/** Load the blocks of a map section from files
 * @param section : the map section where we load the blocks
*/
void MapSection_LoadBlocks(MapSection* section)
{
    int i;
    // +1 car les tableaux commencent à 0 et les fichiers à 1
    char* filename = generate_filename(section->x+1, section->y+1, MAP_BLOCK_FILES);
    FILE* f = fopen(filename,"rt");
    if(f == NULL)
    {
        printf(SECTION_FILE_ERROR);
        exit(-1);
    }

    for(i = 0; i < MAP_IN_HEIGHT; i++)
    {
        char* s = (char*)malloc(sizeof(char)*64);
        if(s == NULL)
        {
            printf("Error in char* alloc in MapSection_LoadBlocks");
            exit(-1);
        }
        int value = 0;
        int j;
        int k = 0;
        if(fgets(s, 64, f) == NULL) //we read the file line per line
        {
            printf(SECTION_FILE_READ_ERROR);
            exit(-1);
        }
        for(j = 0 ; j < strlen(s) ; j++) //we generate the blocks with the good value read
        {
            if((s[j] == '\n') || (s[j] == ' '))
            {
                section->blocks[i][k] = MapBlock_Create();
                MapBlock_Init(section->blocks[i][k], value);
                value = 0;
                k++;
            }
            else value = value*10 + s[j] - '0';
        }
        free(s);
    }
    fclose(f);
    free(filename);
}

/** Load the Ctx Objects of a map section from files
 * @param section : the map section where we load the ctx files
*/
void MapSection_LoadCTX(MapSection* section)
{
    // +1 car les tableaux commencent à 0 et les fichiers à 1
    char* filename = generate_filename(section->x+1, section->y+1, MAP_CTX_FILES);
    FILE* f = fopen(filename,"rt");
    if(f == NULL)
    {
        printf(SECTION_FILE_ERROR);
        exit(-1);
    }
    int i;
    for(i = 0 ; i < MAP_IN_HEIGHT ; i++)
    {
        int j = 0;
        int k = 0;
        int value = 0;
        char* s = (char*)malloc(sizeof(char)*64);
        if(s == NULL)
        {
            printf("Error in char* alloc in MapSection_LoadCTX");
            exit(-1);
        }
        if(fgets(s, 64, f) == NULL) //we read the file line per line
        {
            printf(SECTION_FILE_READ_ERROR);
            exit(-1);
        }
        for(j = 0 ; j < strlen(s) ; j++) //we generates the good contextual object with their value
        {
            if((s[j] == '\n') || (s[j] == ' '))
            {
                section->ctx_objects[i][k] = MapCtxObject_Create();
                MapCtxObject_Generate(section->ctx_objects[i][k], value);
                value = 0;
                k++;
            }
            else value = value*10 + s[j] - '0';
        }
        free(s);
    }
    fclose(f);
    free(filename);
}

/** Get the value of a MapBlock according to the move of an object
 * @param section : the map section where the player is
 * @param move_x : the horizontal move
 * @param move_y : the vertical move
 * @return the value of the nearest block from the player
*/
int MapSection_NearBlock(MapSection* section,int move_x, int move_y)
{
    int x,y;
    x = move_x/(BLOC_HEIGHT);
    y = move_y/(BLOC_WIDTH);
    if ((x >= SECTION_WIDTH) || (y >= SECTION_HEIGHT))
        return 0;
    else
        return MapBlock_GetValue( section->blocks[y][x]);
}

/** Get the id of a Contextual object according to the move of an object
 * @param section : the map section where the player is
 * @param move_x : the horizontal move
 * @param move_y : the vertical move
 * @return a pointer on of the nearest ctx from the player
*/
MapCtxObject* MapSection_NearCtx(MapSection* section,int move_x, int move_y)
{
    int x,y;
    x = move_x/(BLOC_HEIGHT);
    y = move_y/(BLOC_WIDTH);
    if ((x >= SECTION_WIDTH) || (y >= SECTION_HEIGHT))
        return NULL;
    else
        return section->ctx_objects[y][x];
}

/** Generates a filename for a map section file
 * @param x : the number of the map section horizontally
 * @param y : the number of the map section vertically
 * @return the path of the map section file needed
 * @warning the filename is allocated using malloc
*/
static char* generate_filename(int x, int y, char* path)
{
    char* filename = (char*) malloc(sizeof(char)*35);
    if(filename == NULL)
    {
        printf("filename generation error");
        exit(-1);
    }
    sprintf(filename,"%s%d-%d.txt", path, y, x);
    return filename;
}
