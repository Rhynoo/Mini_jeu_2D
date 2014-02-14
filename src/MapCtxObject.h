#ifndef MAPCTXOBJECT_H_INCLUDED
#define MAPCTXOBJECT_H_INCLUDED

#define CTX_GOLD 1
#define CTX_ITEM 2

#define ID_GOLD 1
#define ID_POTION 2

#define CTX_ACTIVE 1
#define CTX_NONACTIVE 0

#define CTX_ALLOC_ERROR "impossible d'allouer l'objet contextuel"

typedef struct
{
    /** the type of the CtxObject : gold, item or other */
    int type;
    /** defines if the CtxObject has been took/actionned or not */
    int active;
    /** the value of the CtxObject (defines the object)*/
    int id;
    /** the name of the object */
    char* name;
} MapCtxObject;

MapCtxObject* MapCtxObject_Create();
void MapCtxObject_Init(MapCtxObject* ctx, int type, int id, char* name);
int MapCtxObject_GetId(MapCtxObject* ctx);
void MapCtxObject_Enable(MapCtxObject* ctx, int value);
void MapCtxObject_Destroy(MapCtxObject* ctx);
void MapCtxObject_Generate(MapCtxObject* ctx, int value);
void MapCtxObject_Draw(MapCtxObject* ctx, SDL_Surface* screen, SDL_Rect* position);

#endif // MAPCTXOBJECT_H_INCLUDED
