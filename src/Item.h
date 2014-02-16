#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "ItemEffect.h"

#define ITEM_CREATION_ERROR "impossible de créer l'item"

#define USABLE_ITEM 1
#define UNUSABLE_ITEM 0

#define STACKABLE 1
#define UNSTACKABLE 0

class Item
{
private:
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
public:
    Item(char* name, int count, int use, int stack, Effect* effect, int ammount);
    ~Item();
    int Use(void* data);
    void Draw(SDL_Surface* screen, SDL_Rect* position);

	int getAmmount() const {
		return ammount;
	}

	void setAmmount(int ammount) {
		this->ammount = ammount;
	}

	int getCount() const {
		return count;
	}

	void setCount(int count) {
		this->count = count;
	}

	Effect* getEffect() const {
		return effect;
	}

	void setEffect(Effect* effect) {
		this->effect = effect;
	}

	char* getName() const {
		return name;
	}

	void setName(char* name) {
		this->name = name;
	}

	int getStackable() const {
		return stackable;
	}

	int getUsable() const {
		return usable;
	}
};

#endif // ITEM_H_INCLUDED
