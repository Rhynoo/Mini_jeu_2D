#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include "Const.h"
#include "Character.h"
#include "Item.h"
#include "ItemEffect.h"

/** Create a character
 * @return a pointer on the character created
 * @warning the character is created using malloc
*/
Character::Character(char* file)
{
    sprite = NULL;
    inventory = NULL;

    coord = Create_Rect(INIT_POSITION_X, INIT_POSITION_Y, 40, 64);

    direction = NO_DIRECTION;
    speed = BASE_SPEED;

    sprite = Sprite_Create();
    Sprite_Init(sprite, file, coord.w, coord.h);

    collisionbox = Create_Rect(INIT_POSITION_X + COLLBOX_xOFFSET, INIT_POSITION_Y + COLLBOX_yOFFSET,
                                   coord.h, coord.w);

    life = MAX_LIFE;

    inventory = new Inventory();

    Item* potion = new Item("potion", 1, USABLE_ITEM, STACKABLE, Effect_Heal, 10);
    inventory->AddItem(potion);

    inventory->setSelectedItem(potion);
}

/** Set the direction of a character
 * @param ch : the character
 * @param direction : the new direction of the character
*/
void Character::setDirection(int direction)
{
    this->direction = direction;
    Sprite_SetOrientation(sprite, direction);
}

/** Set the life of a character
 * @param ch : the character
 * @param life : the new life of the character
*/
void Character::setLife(int life)
{
    this->life = life;
}

/** Set the position of a character
 * @param ch : the character
 * @param x : the horizontal position of the character
 * @param y : the vertical position of the character
*/
void Character::SetPosition(int x, int y)
{
    collisionbox.x = x;
    collisionbox.y = y;
    coord.x = x;
    coord.y = y;
}

/** Does dammage on the character
 * @param ch : the character played
 * @param ammount : the ammount of dammage to deal on the character's life
*/
void Character::TakeDammage(int ammount)
{
    int life = this->getLife() - ammount;
    if(life <= 0)
        life = 0;
    setLife(life);
}

/** Use the selected item
 * @param ch : the character played
*/
void Character::UseSelectedItem()
{
    inventory->UseSelectedItem(this);
}

/** Update the position and the coord of a character
 * @param ch : the character
 * @param map : the map where the character evolves
 * @return the status of the game
*/
int Character::Update(Map* map)
{
    int block_value;
    MapCtxObject* ctx;
    switch(direction)
    {
    case UP:
        block_value = Map_NearBlock(map, collisionbox.x + coord.w/2, collisionbox.y - speed);
        ctx = Map_NearCtx(map, collisionbox.x + coord.w/2, collisionbox.y - speed);
        // we check if we can walk on a block
        if(block_value < WALKABLE)
        {
            if (collisionbox.y < COLLBOX_yOFFSET)
            {//if we are on a bound we change the map
                coord.y = SCREEN_HEIGHT - COLLBOX_yOFFSET - 12;
                collisionbox.y = SCREEN_HEIGHT ;
                Map_SetActiveSection(map, map->active_section->x, map->active_section->y - 1);
            }
            else //else we move the character on the requested direction
            {
                coord.y -= speed;
                collisionbox.y -= speed;
            }
        }
        break;

    case DOWN:
        block_value = Map_NearBlock(map, collisionbox.x + coord.w/2, collisionbox.y + speed + coord.h/3);
        ctx = Map_NearCtx(map, collisionbox.x + coord.w/2, collisionbox.y + speed + coord.h/3);
        if(block_value < WALKABLE)
        {
            if (collisionbox.y + collisionbox.h/2 > SCREEN_HEIGHT)
            {
                coord.y = 0;
                collisionbox.y = COLLBOX_yOFFSET;
                Map_SetActiveSection(map,map->active_section->x, map->active_section->y + 1);
            }
            else
            {
                coord.y += speed;
                collisionbox.y += speed;
            }
        }
        break;

    case LEFT:
        block_value = Map_NearBlock(map, collisionbox.x - speed, collisionbox.y + coord.h/4);
        ctx = Map_NearCtx(map, collisionbox.x - speed, collisionbox.y + coord.h/4);
        if(block_value < WALKABLE)
        {
            if (collisionbox.x < COLLBOX_xOFFSET)
            {
                coord.x = SCREEN_WIDTH - COLLBOX_xOFFSET;
                collisionbox.x = SCREEN_WIDTH;
                Map_SetActiveSection(map, map->active_section->x - 1, map->active_section->y);
            }
            else
            {
                coord.x -= speed;
                collisionbox.x -= speed;
            }
        }
        break;

    case RIGHT:
        block_value = Map_NearBlock(map, collisionbox.x + speed + coord.w, collisionbox.y + coord.h/4) ;
        ctx = Map_NearCtx(map, collisionbox.x + speed + coord.w, collisionbox.y + coord.h/4) ;
        if(block_value < WALKABLE)
        {
            if (collisionbox.x + collisionbox.w > SCREEN_WIDTH)
            {
                coord.x = 0;
                collisionbox.x = COLLBOX_xOFFSET;
                Map_SetActiveSection(map, map->active_section->x + 1, map->active_section->y);
            }
            else
            {
                coord.x += speed;
                collisionbox.x += speed;
            }
        }
        break;

    default:
        block_value = Map_NearBlock(map, collisionbox.x + coord.w/2, collisionbox.y + coord.h/4) ;
        ctx = Map_NearCtx(map, collisionbox.x + coord.w/2, collisionbox.y + coord.h/4) ;
        break;
    }
    if((block_value == WIN)) // if the character exits the labyrinthe, the game is won
        return STATUS_GAMEWIN;

    if((block_value < WALKABLE ) && (block_value >= DANGEROUS))//if the block is a damaging block, we hurt the character
        TakeDammage(1);

    if(life <= 0) // if the character is dead, the game is over
        return STATUS_GAMELOSE;

    if(ctx != NULL)
        WalkOnObject(ctx);

    Sprite_Animate(sprite);

    return STATUS_INGAME;
}

/** Make the good treatment when a character walks on a contextual object
 * @param ch : the character
 * @param ctx : the contextual object
*/
void Character::WalkOnObject(MapCtxObject* ctx)
{
    if(ctx->active == CTX_ACTIVE)
    {
        switch(ctx->id)
        {
            case CTX_GOLD:
                MapCtxObject_Enable(ctx, CTX_NONACTIVE);
                inventory->AddGold(1);
                break;
            case CTX_ITEM:
                /*Item* item = Item_Create();
                Item_Init();
                Inventory_AddItem(inventory, item);*/
                break;
            default:
                break;
        }
    }
}

/** Draw a character on the screen
 * @param ch : the character
 * @param screen : the main window of the application
*/
void Character::Draw(SDL_Surface* screen)
{
    // use the next line to draw the collision box of the character
    //Draw_Rect(screen, collisionbox.x, collisionbox.y, BLOC_WIDTH, BLOC_HEIGHT, 0, 255, 255);

    Sprite_Draw(sprite, screen, &coord);
}

/** Free a character
 * @param ch : the character to free
*/
Character::~Character()
{
	Sprite_Destroy(sprite);
	delete inventory;
}
