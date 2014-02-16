#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "Map.h"
#include "MapCtxObject.h"
#include "Sprite.h"
#include "Inventory.h"

/** An error message when alloc on a character fails */
#define CHAR_CREATION_ERROR "impossible de creer le personnage"
/** the path to the player's character file */
#define MAIN_CHAR_FILE "ressources\\char\\shep.bmp"

/** the init position of the character when the game begins*/
#define INIT_POSITION_X 304
/** the init position of the character when the game begins*/
#define INIT_POSITION_Y 260

/** an offset for the collision box to move it correctly */
#define COLLBOX_xOFFSET 5
/** an offset for the collision box to move it correctly */
#define COLLBOX_yOFFSET coord.h/2 +5

class Character
{
private :
    /** the amount of life of the character */
    int life;
    /** the character's direction */
    int direction;
    /** the character's speed */
    int speed;
    /** the sprite that contains all the graphical information about the character */
    Sprite* sprite;
    /** the character's inventory */
    Inventory* inventory;
    /** the box that checks collisions for the character */
    SDL_Rect collisionbox;
    /** the coordinates of the character */
    SDL_Rect coord;
public:
    Character(char* file);
    ~Character();
    void setDirection(int direction);
    void setLife(int life);
    void SetPosition(int x, int y);
    void TakeDammage(int ammount);
    void UseSelectedItem();

    int Update(Map* map);
    void WalkOnObject(MapCtxObject* ctx);
    void Draw(SDL_Surface* screen);
    void Destroy(Character* ch);

	const SDL_Rect& getCollisionbox() const {
		return collisionbox;
	}

	void setCollisionbox(const SDL_Rect& collisionbox) {
		this->collisionbox = collisionbox;
	}

	const SDL_Rect& getCoord() const {
		return coord;
	}

	void setCoord(const SDL_Rect& coord) {
		this->coord = coord;
	}

	Inventory* getInventory() {
		return inventory;
	}

	void setInventory(Inventory* inventory) {
		this->inventory = inventory;
	}

	int getSpeed() const {
		return speed;
	}

	void setSpeed(int speed) {
		this->speed = speed;
	}

	Sprite* getSprite() {
		return sprite;
	}

	void setSprite(Sprite* sprite) {
		this->sprite = sprite;
	}

	int getDirection() const {
		return direction;
	}

	int getLife() const {
		return life;
	}
};

#endif // CHARACTER_H_INCLUDED
