#include <SDL\SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ItemEffect.h"
#include "Const.h"
#include <iostream>

/** Creates a new item
 * @return a pointer on the item created
 * @warning the item is created using malloc
*/
Item::Item(char* name, int count, int use, int stack, Effect* effect, int ammount)
{
    this->name = strdup(name);

    usable = use;
    this->effect = effect;
    this->ammount = ammount;
    stackable = stack;
    this->count = count;
}

/** Use an item
 * @param item : the item
 * @param data : the object on what is item is used (generally a character)
 * @return the count of the item
*/
int Item::Use(void* data)
{
    effect(data, ammount);
    if(stackable == STACKABLE)
        count--;
    return count;
}

void Item::Draw(SDL_Surface* screen, SDL_Rect* position)
{
    char* filename = (char*) malloc(sizeof(char)*30);
    if(filename == NULL)
    {
        printf("Item draw error");
        exit(-1);
    }

    sprintf(filename, "%s%s.bmp", ITEM_FILE, name);

    SDL_Surface* img = LoadImage(filename);

    SDL_BlitSurface(img, NULL, screen, position);

    free(filename);
    SDL_FreeSurface(img);
}

Item::~Item() {
	free(name);
}
