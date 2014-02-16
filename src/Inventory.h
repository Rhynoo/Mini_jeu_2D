#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

/** an error message that apears when the inventory's allocation fails*/
#define INVENTORY_CREATION_ERROR "impossible de crée l'inventaire"
/** an error message that apears when the reallocation of the size of the inventory fails*/
#define INVENTORY_ADD_ERROR "impossible d'ajouter un item à l'inventaire"

#include "Item.h"

class Inventory
{
private:
    /** number of items in the inventory */
    int item_count;
    /** List of items of the inventory */
    Item** items;
    /** Selected item, to use it quickly in game */
    Item* selected_item;
    /** the money(gold) the player have */
    int gold;
public:
    Inventory();
    ~Inventory();
    void AddItem(Item* item);
    void RemoveItem(Item* item);
    void UseSelectedItem(void* data);
    void AddGold(int ammount);
    void RemoveGold(int ammount);

	int getGold() const {
		return gold;
	}

	int getItemCount() const {
		return item_count;
	}

	void setItemCount(int itemCount) {
		item_count = itemCount;
	}

	Item** getItems() {
		return items;
	}

	void setItems(Item** items) {
		this->items = items;
	}

	Item* getSelectedItem() {
		return selected_item;
	}

	void setGold(int gold)
	{
	    this->gold = gold;
	}

	void setSelectedItem(Item* item)
	{
	    this->selected_item = item;
	}
};

#endif // INVENTORY_H_INCLUDED
