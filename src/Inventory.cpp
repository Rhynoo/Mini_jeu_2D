#include "Character.h"
#include "Inventory.h"
#include "Item.h"

/** Create a new inventory
 * @return a pointer on the inventory created
 * @warning the inventory is created using malloc
*/
Inventory* Inventory_Create()
{
    Inventory* inv = (Inventory*)malloc(sizeof(Inventory));
    if(inv == NULL)
    {
        printf(INVENTORY_CREATION_ERROR);
        exit(-1);
    }

    inv->items = NULL;
    inv->selected_item = NULL;
    inv->item_count = 0;
    inv->gold = 0;

    return inv;
}

/** Set the new ammount of gold in the inventory
 * @param inv : the inventory
 * @param gold : the new quantity of gold
*/
void Inventory_SetGold(Inventory* inv, int gold)
{
    inv->gold = gold;
}

/** Set the new selected Item on the inventory
 * @param inv : the inventory
 * @param item : the item
*/
void Inventory_SetSelectedItem(Inventory* inv, Item* item)
{
    inv->selected_item = item;
}

/** Add a new item in the inventory
 * @param inv : the inventory
 * @param item : the item to add
 * @note if the item is stackable and already exists we had new count for this item, else we add it
*/
void Inventory_AddItem(Inventory* inv, Item* item)
{
    if(inv->items == NULL) //if there is no item in the inventory, we had the first
    {
        inv->item_count++;
        inv->items = (Item**)malloc(sizeof(Item*));
        if(inv->items == NULL)
        {
            printf(INVENTORY_ADD_ERROR);
            exit(-1);
        }

        inv->items[0] = item;
    }
    else
    {
        int i = 0;
        // we search the new position for the item
        while(inv->items[i] != NULL)
        {
            printf(inv->items[i]->name);
            if((inv->items[i]->name == item->name) && (inv->items[i]->stackable == STACKABLE))
                break;
            i++;
        }
        //and we had it
        if(inv->items[i] == NULL)
        {
            inv->item_count++;
            realloc((Item**)inv->items, sizeof(Item*)*inv->item_count);
            if(inv->items == NULL)
            {
                printf(INVENTORY_ADD_ERROR);
                exit(-1);
            }
            inv->items[i] = item;
        }
        else
            Item_SetCount(inv->items[i], inv->items[i]->count + 1);
    }
}

/** Remove a item from the inventory
 * @param inv : the inventory
 * @param item : the item to remove
*/
void Inventory_RemoveItem(Inventory* inv, Item* item)
{
    int i;
    int count = 0;
    Item* temp = inv->items[0];

    while((temp != NULL) && (item->name != temp->name))
    {
        count++;
        temp = inv->items[count];
    }

    Item_Destroy(inv->items[count]);
    inv->item_count--;
    if(inv->item_count > 1)
    {
        for(i = count ; i < inv->item_count ; i++)
            inv->items[i] = inv->items[i+1];
    }
}

/** Add Gold to the inventory
 * @param inv : the inventory
 * @param ammount : the ammount of gold to add
*/
void Inventory_AddGold(Inventory* inv, int ammount)
{
    Inventory_SetGold(inv, inv->gold + ammount);
}

/** Remove Gold from the inventory
 * @param inv : the inventory
 * @param ammount : the ammount of gold to remove
*/
void Inventory_RemoveGold(Inventory* inv, int ammount)
{
    Inventory_SetGold(inv, inv->gold - ammount);
}

/** Use the selected item on the inventory
 * @param item : the inventory
 * @param data : the object on what is item is used (generally a character)
*/
void Inventory_UseSelectedItem(Inventory* inv, void* data)
{
    if(inv->selected_item != NULL)
    {
        int count = Item_Use(inv->selected_item, data);
        if(count == 0)
        {
            Inventory_RemoveItem(inv, inv->selected_item);
            inv->selected_item = NULL;
        }
    }
}

/** Frees an inventory
 * @param inv : the inventory
*/
void Inventory_Destroy(Inventory* inv)
{
    if(inv != NULL)
    {
        int i;
        for(i = 0 ; i < inv->item_count ; i++)
            Item_Destroy(inv->items[i]);

        free(inv->items);

        free(inv);
    }
}
