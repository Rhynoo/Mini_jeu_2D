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
#define COLLBOX_yOFFSET ch->coord.h/2 +5

/** The structure of the character*/
typedef struct
{
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
} Character;

Character* Character_Create();
void Character_SetDirection(Character* ch, int life);
void Character_SetLife(Character* ch, int direction);
void Character_SetPosition(Character* ch, int x, int y);
void Character_TakeDammage(Character* ch, int ammount);
void Character_UseSelectedItem(Character* ch);
void Character_Init(Character* ch, char* file);
int Character_Update(Character* ch, Map* map);
void Character_WalkOnObject(Character* ch, MapCtxObject* ctx);
void Character_Draw(Character* ch, SDL_Surface* screen);
void Character_Destroy(Character* ch);

#endif // CHARACTER_H_INCLUDED
