#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

/** an error message that apears when the inventory's allocation fails*/
#define INVENTORY_CREATION_ERROR "impossible de crée l'inventaire"
/** an error message that apears when the reallocation of the size of the inventory fails*/
#define INVENTORY_ADD_ERROR "impossible d'ajouter un item à l'inventaire"

#include "Item.h"

/** the structure of the inventory */
typedef struct
{
    /** number of items in the inventory */
    int item_count;
    /** List of items of the inventory */
    Item** items;
    /** Selected item, to use it quickly in game */
    Item* selected_item;
    /** the money(gold) the player have */
    int gold;
} Inventory;

Inventory* Inventory_Create();
void Inventory_SetSelectedItem(Inventory* inv, Item* item);
void Inventory_AddItem(Inventory* inv, Item* item);
void Inventory_RemoveItem(Inventory* inv, Item* item);
void Inventory_UseSelectedItem(Inventory* inv, void* data);
void Inventory_SetGold(Inventory* inv, int gold);
void Inventory_AddGold(Inventory* inv, int ammount);
void Inventory_RemoveGold(Inventory* inv, int ammount);
void Inventory_Destroy(Inventory* inv);

#endif // INVENTORY_H_INCLUDED
