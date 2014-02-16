#include <SDL\SDL.h>
#include "ItemEffect.h"
#include "Character.h"
#include "Const.h"

void Effect_Heal(void* data, int ammount)
{
    Character* ch = (Character*)data;
    int life = ch->getLife() + ammount;
    if(life > MAX_LIFE)
        life = MAX_LIFE;
    ch->setLife(life);
}
