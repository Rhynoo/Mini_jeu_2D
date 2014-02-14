#ifndef ITEMEFFECT_H_INCLUDED
#define ITEMEFFECT_H_INCLUDED

/** defines a function pointer for the item's effects*/
typedef void (Effect)(void* data, int ammount);

void Effect_Heal(void* data, int ammount);

#endif // ITEMEFFECT_H_INCLUDED
