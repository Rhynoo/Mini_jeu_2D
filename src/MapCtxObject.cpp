#include <SDL\SDL.h>
#include "MapCtxObject.h"
#include "Const.h"

/** Create a new Contextual object
 * @return the Contextual object created
 * @warning the object is created using malloc
*/
MapCtxObject* MapCtxObject_Create()
{
    MapCtxObject* ctx = (MapCtxObject*)malloc(sizeof(MapCtxObject));
    if(ctx == NULL)
    {
        printf(CTX_ALLOC_ERROR);
        exit(-1);
    }

    ctx->name = NULL;
    ctx->id = 0;
    ctx->active = CTX_NONACTIVE;

    return ctx;
}

/** Inits a Contextual object
 * @param ctx : the contextual object
 * @param type : the type of the Contextual object
 * @param name : the name of the object
*/
void MapCtxObject_Init(MapCtxObject* ctx, int type, int id, char* name)
{
    ctx->type = type;
    ctx->id = id;
    ctx->active = CTX_ACTIVE;
    ctx->name = duplicateString(name);
}

/** Enable or disable a contextual object
 * @param ctx : the contextual object
 * @param value : ENABLE or DISABLE
*/
void MapCtxObject_Enable(MapCtxObject* ctx, int value)
{
    ctx->active = value;
}

/** Return the id of a contextual object
 * @param ctx : the contextual object
 * @return the id of the object
*/
int MapCtxObject_GetId(MapCtxObject* ctx)
{
    if((ctx != NULL) && (ctx->active == CTX_ACTIVE))
        return ctx->id;
    else return 0;
}

/** Draw a map ctx object on a screen at his position
 * @param ctx : the map ctx object to draw on the screen
 * @param screen : the main window of the application
 * @param position : the position of the block on the screen
*/
void MapCtxObject_Draw(MapCtxObject* ctx, SDL_Surface* screen, SDL_Rect* position)
{
    if((ctx != NULL) && (ctx->name != NULL))
    {
        if(ctx->active == CTX_ACTIVE)
        {
            char* filename =(char*) malloc(sizeof(char)*30);
            if(filename == NULL)
            {
                printf("error in mapctx draw");
                exit(-1);
            }
            sprintf(filename, "%s%s.bmp", ITEM_FILE, ctx->name);

            SDL_Surface* surface = LoadImage(filename);

            position->x += surface->w/2;
            position->y += surface->h/2;

            SDL_BlitSurface(surface,NULL,screen,position);
            SDL_FreeSurface(surface);
            free(filename);
        }
    }
}

/** Generate a Contextual object from its id on the map file
 * @param ctx : the contextual object
 * @param id : the id of the the contextual object
 * @note the contextual object must have been created before using this function
*/
void MapCtxObject_Generate(MapCtxObject* ctx, int id)
{
    switch(id)
    {
    case ID_GOLD:
        MapCtxObject_Init(ctx, CTX_GOLD, id, "gold");
        break;
    case ID_POTION:
        MapCtxObject_Init(ctx, CTX_ITEM, id, "potion");
        break;
    default:
        break;
    }
}

/** Fress a contextual object
 * @param ctx : the contextual object
*/
void MapCtxObject_Destroy(MapCtxObject* ctx)
{
    free(ctx->name);
    free(ctx);
}
