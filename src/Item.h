#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "ItemEffect.h"

#define ITEM_CREATION_ERROR "impossible de créer l'item"

#define USABLE_ITEM 1
#define UNUSABLE_ITEM 0

#define STACKABLE 1
#define UNSTACKABLE 0

typedef struct
{
    /** the name of the item */
    char* name;
    /** the type of the item */
    int usable;
    /** defines if the item is stackable */
    int stackable;
    /** the number of stack of this item if stackable */
    int count;
    /** the effect of the item on the character */
    Effect* effect;
    /** the ammount of the effect of the item */
    int ammount;
} Item;

Item* Item_Create();
void Item_Init(Item* item, char* name, int use, int stack, Effect* effect, int ammount);
void Item_Destroy(Item* item);
int Item_Use(Item* item, void* data);
void Item_SetCount(Item* item, int count);
void Item_Draw(Item* item, SDL_Surface* screen, SDL_Rect* position);

#endif // ITEM_H_INCLUDED
