#include "Character.h"
#include "Inventory.h"
#include "Item.h"

/** Create a new inventory
 * @return a pointer on the inventory created
 * @warning the inventory is created using malloc
*/
Inventory::Inventory()
{
    items = NULL;
    selected_item = NULL;
    item_count = 0;
    gold = 0;
}

/** Add a new item in the inventory
 * @param inv : the inventory
 * @param item : the item to add
 * @note if the item is stackable and already exists we had new count for this item, else we add it
*/
void Inventory::AddItem(Item* item)
{
    if(items == NULL) //if there is no item in the inventory, we had the first
    {
        item_count++;
        items = (Item**)malloc(sizeof(Item*));
        if(items == NULL)
        {
            printf(INVENTORY_ADD_ERROR);
            exit(-1);
        }

        items[0] = item;
    }
    else
    {
        int i = 0;
        // we search the new position for the item
        while(items[i] != NULL)
        {
            printf(items[i]->getName());
            if((items[i]->getName() == item->getName()) && (items[i]->getStackable() == STACKABLE))
                break;
            i++;
        }
        //and we had it
        if(items[i] == NULL)
        {
            item_count++;
            realloc((Item**)items, sizeof(Item*)*item_count);
            if(items == NULL)
            {
                printf(INVENTORY_ADD_ERROR);
                exit(-1);
            }
            items[i] = item;
        }
        else
            items[i]->setCount(items[i]->getCount() + 1);
    }
}

/** Remove a item from the inventory
 * @param inv : the inventory
 * @param item : the item to remove
*/
void Inventory::RemoveItem(Item* item)
{
    int i;
    int count = 0;
    Item* temp = items[0];

    while((temp != NULL) && (item->getName() != temp->getName()))
    {
        count++;
        temp = items[count];
    }

    delete items[count];
    item_count--;
    if(item_count > 1)
    {
        for(i = count ; i < item_count ; i++)
            items[i] = items[i+1];
    }
}

/** Add Gold to the inventory
 * @param inv : the inventory
 * @param ammount : the ammount of gold to add
*/
void Inventory::AddGold(int ammount)
{
    gold += ammount;
}

/** Remove Gold from the inventory
 * @param inv : the inventory
 * @param ammount : the ammount of gold to remove
*/
void Inventory::RemoveGold(int ammount)
{
    gold -= ammount;
}

/** Use the selected item on the inventory
 * @param item : the inventory
 * @param data : the object on what is item is used (generally a character)
*/
void Inventory::UseSelectedItem(void* data)
{
    if(selected_item != NULL)
    {
        int count = selected_item->Use(data);
        if(count == 0)
        {
            RemoveItem(selected_item);
            selected_item = NULL;
        }
    }
}

/** Frees an inventory
 * @param inv : the inventory
*/
Inventory::~Inventory()
{
	int i;
	for(i = 0 ; i < item_count ; i++)
		delete items[i];

	free(items);
}
