#include <SDL\SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ItemEffect.h"
#include "Const.h"

/** Creates a new item
 * @return a pointer on the item created
 * @warning the item is created using malloc
*/
Item* Item_Create()
{
    Item* item = (Item*)malloc(sizeof(Item));
    if(item == NULL)
    {
        printf(ITEM_CREATION_ERROR);
        exit(-1);
    }

    item->name = NULL;
    item->effect = NULL;

    return item;
}

/** Inits an item
 * @param item : the item
 * @param name : the name of the item
 * @param use : an int that defines if the item is usable or not
 * @param effect : a pointer on the effect that makes this item
*/
void Item_Init(Item* item, char* name, int use, int stack, Effect effect, int ammount)
{
    item->name = strdup(name);
    item->usable = use;
    item->effect = effect;
    item->ammount = ammount;
    item->stackable = stack;
    item->count = 1;
}

/** Use an item
 * @param item : the item
 * @param data : the object on what is item is used (generally a character)
 * @return the count of the item
*/
int Item_Use(Item* item, void* data)
{
    item->effect(data, item->ammount);
    if(item->stackable == STACKABLE)
        item->count--;
    return item->count;
}

/** Set the count of an item
 * @param item : the item
 * @param count : the new count of the item
*/
void Item_SetCount(Item* item, int count)
{
    item->count = count;
}

void Item_Draw(Item* item, SDL_Surface* screen, SDL_Rect* position)
{
    char* filename = (char*) malloc(sizeof(char)*30);
    if(filename == NULL)
    {
        printf("Item draw error");
        exit(-1);
    }

    sprintf(filename, "%s%s.bmp", ITEM_FILE, item->name);

    SDL_Surface* img = LoadImage(filename);

    SDL_BlitSurface(img, NULL, screen, position);

    free(filename);
    SDL_FreeSurface(img);
}

/** Frees an item
 * @param item : the item
*/
void Item_Destroy(Item* item)
{
    free(item);
}
