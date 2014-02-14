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
Character* Character_Create()
{
    Character* ch = (Character*)malloc(sizeof(Character));
    if(ch == NULL)
    {
        printf(CHAR_CREATION_ERROR);
        exit(-1);
    }

    ch->sprite = NULL;
    ch->inventory = NULL;

    return ch;
}

/** Inits a character
 * @param ch : the character to init
 * @param file : the path to the character's sprite
 * @note the character must have been created previously
*/
void Character_Init(Character* ch, char* file)
{
    ch->coord = Create_Rect(INIT_POSITION_X, INIT_POSITION_Y, 40, 64);

    ch->direction = NO_DIRECTION;
    ch->speed = BASE_SPEED;

    ch->sprite = Sprite_Create();
    Sprite_Init(ch->sprite, file, ch->coord.w, ch->coord.h);

    ch->collisionbox = Create_Rect(INIT_POSITION_X + COLLBOX_xOFFSET, INIT_POSITION_Y + COLLBOX_yOFFSET,
                                   ch->coord.h, ch->coord.w);

    ch->life = MAX_LIFE;

    ch->inventory = Inventory_Create();

    Item* potion = Item_Create();
    Item_Init(potion, "potion", USABLE_ITEM, STACKABLE, Effect_Heal, 10);
    Inventory_AddItem(ch->inventory, potion);

    Inventory_SetSelectedItem(ch->inventory, potion);
}

/** Set the direction of a character
 * @param ch : the character
 * @param direction : the new direction of the character
*/
void Character_SetDirection(Character* ch, int direction)
{
    ch->direction = direction;
    Sprite_SetOrientation(ch->sprite, direction);
}

/** Set the life of a character
 * @param ch : the character
 * @param life : the new life of the character
*/
void Character_SetLife(Character* ch, int life)
{
    ch->life = life;
}

/** Set the position of a character
 * @param ch : the character
 * @param x : the horizontal position of the character
 * @param y : the vertical position of the character
*/
void Character_SetPosition(Character* ch, int x, int y)
{
    ch->collisionbox.x = x;
    ch->collisionbox.y = y;
    ch->coord.x = x;
    ch->coord.y = y;
}

/** Does dammage on the character
 * @param ch : the character played
 * @param ammount : the ammount of dammage to deal on the character's life
*/
void Character_TakeDammage(Character* ch, int ammount)
{
    int life = ch->life - ammount;
    if(life <= 0)
        life = 0;
    Character_SetLife(ch, life);
}

/** Use the selected item
 * @param ch : the character played
*/
void Character_UseSelectedItem(Character* ch)
{
    Inventory_UseSelectedItem(ch->inventory, ch);
}

/** Update the position and the coord of a character
 * @param ch : the character
 * @param map : the map where the character evolves
 * @return the status of the game
*/
int Character_Update(Character* ch, Map* map)
{
    int block_value;
    MapCtxObject* ctx;
    switch(ch->direction)
    {
    case UP:
        block_value = Map_NearBlock(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y - ch->speed);
        ctx = Map_NearCtx(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y - ch->speed);
        // we check if we can walk on a block
        if(block_value < WALKABLE)
        {
            if (ch->collisionbox.y < COLLBOX_yOFFSET)
            {//if we are on a bound we change the map
                ch->coord.y = SCREEN_HEIGHT - COLLBOX_yOFFSET - 12;
                ch->collisionbox.y = SCREEN_HEIGHT ;
                Map_SetActiveSection(map, map->active_section->x, map->active_section->y - 1);
            }
            else //else we move the character on the requested direction
            {
                ch->coord.y -= ch->speed;
                ch->collisionbox.y -= ch->speed;
            }
        }
        break;

    case DOWN:
        block_value = Map_NearBlock(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y + ch->speed + ch->coord.h/3);
        ctx = Map_NearCtx(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y + ch->speed + ch->coord.h/3);
        if(block_value < WALKABLE)
        {
            if (ch->collisionbox.y + ch->collisionbox.h/2 > SCREEN_HEIGHT)
            {
                ch->coord.y = 0;
                ch->collisionbox.y = COLLBOX_yOFFSET;
                Map_SetActiveSection(map,map->active_section->x, map->active_section->y + 1);
            }
            else
            {
                ch->coord.y += ch->speed;
                ch->collisionbox.y += ch->speed;
            }
        }
        break;

    case LEFT:
        block_value = Map_NearBlock(map, ch->collisionbox.x - ch->speed, ch->collisionbox.y + ch->coord.h/4);
        ctx = Map_NearCtx(map, ch->collisionbox.x - ch->speed, ch->collisionbox.y + ch->coord.h/4);
        if(block_value < WALKABLE)
        {
            if (ch->collisionbox.x < COLLBOX_xOFFSET)
            {
                ch->coord.x = SCREEN_WIDTH - COLLBOX_xOFFSET;
                ch->collisionbox.x = SCREEN_WIDTH;
                Map_SetActiveSection(map, map->active_section->x - 1, map->active_section->y);
            }
            else
            {
                ch->coord.x -= ch->speed;
                ch->collisionbox.x -= ch->speed;
            }
        }
        break;

    case RIGHT:
        block_value = Map_NearBlock(map, ch->collisionbox.x + ch->speed + ch->coord.w, ch->collisionbox.y + ch->coord.h/4) ;
        ctx = Map_NearCtx(map, ch->collisionbox.x + ch->speed + ch->coord.w, ch->collisionbox.y + ch->coord.h/4) ;
        if(block_value < WALKABLE)
        {
            if (ch->collisionbox.x + ch->collisionbox.w > SCREEN_WIDTH)
            {
                ch->coord.x = 0;
                ch->collisionbox.x = COLLBOX_xOFFSET;
                Map_SetActiveSection(map, map->active_section->x + 1, map->active_section->y);
            }
            else
            {
                ch->coord.x += ch->speed;
                ch->collisionbox.x += ch->speed;
            }
        }
        break;

    default:
        block_value = Map_NearBlock(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y + ch->coord.h/4) ;
        ctx = Map_NearCtx(map, ch->collisionbox.x + ch->coord.w/2, ch->collisionbox.y + ch->coord.h/4) ;
        break;
    }
    if((block_value == WIN)) // if the character exits the labyrinthe, the game is won
        return STATUS_GAMEWIN;

    if((block_value < WALKABLE ) && (block_value >= DANGEROUS))//if the block is a damaging block, we hurt the character
        Character_TakeDammage(ch, 1);

    if(ch->life <= 0) // if the character is dead, the game is over
        return STATUS_GAMELOSE;

    if(ctx != NULL)
        Character_WalkOnObject(ch, ctx);

    Sprite_Animate(ch->sprite);

    return STATUS_INGAME;
}

/** Make the good treatment when a character walks on a contextual object
 * @param ch : the character
 * @param ctx : the contextual object
*/
void Character_WalkOnObject(Character* ch, MapCtxObject* ctx)
{
    if(ctx->active == CTX_ACTIVE)
    {
        switch(ctx->id)
        {
            case CTX_GOLD:
                MapCtxObject_Enable(ctx, CTX_NONACTIVE);
                Inventory_AddGold(ch->inventory, 1);
                break;
            case CTX_ITEM:
                /*Item* item = Item_Create();
                Item_Init();
                Inventory_AddItem(ch->inventory, item);*/
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
void Character_Draw(Character* ch, SDL_Surface* screen)
{
    // use the next line to draw the collision box of the character
    //Draw_Rect(screen, ch->collisionbox.x, ch->collisionbox.y, BLOC_WIDTH, BLOC_HEIGHT, 0, 255, 255);

    Sprite_Draw(ch->sprite, screen, &ch->coord);
}

/** Free a character
 * @param ch : the character to free
*/
void Character_Destroy(Character* ch)
{
    if(ch != NULL)
    {
        Sprite_Destroy(ch->sprite);
        Inventory_Destroy(ch->inventory);
    }
    free(ch);
}
