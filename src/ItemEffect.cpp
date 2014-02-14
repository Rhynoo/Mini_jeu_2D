#include <SDL\SDL.h>
#include "ItemEffect.h"
#include "Character.h"
#include "Const.h"

void Effect_Heal(void* data, int ammount)
{
    Character* ch = (Character*)data;
    int life = ch->life + ammount;
    if(life > MAX_LIFE)
        life = MAX_LIFE;
    Character_SetLife(ch, life);
}
