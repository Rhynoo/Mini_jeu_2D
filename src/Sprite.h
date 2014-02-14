#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#define SPRITE_CREATION_ERROR "impossible de creer le sprite"
#define ANIM_TIME 9

typedef struct
{
    /** the image used by the sprite */
    SDL_Surface* image;
    /** the surface that copy the proper animation from the sprite */
    SDL_Rect source;
    /** indicate if the sprite is animated or not */
    int anim;
    /** the orientation of the sprite (UP, RIGHT, DOWN, LEFT, NONE) */
    int orientation;
    /** actual state of the sprite */
    int anim_courante;
    /** remaining time of the sprite animation */
    int temps_anim_courante;
    /** number of animations in the sprite */
    int total_anims;
} Sprite;

Sprite* Sprite_Create();
void Sprite_Init(Sprite* sprite, const char* image, int width, int height);
void Sprite_Destroy(Sprite* sprite);
void Sprite_SetOrientation(Sprite* sprite, int orientation);
void Sprite_Draw(Sprite* sprite, SDL_Surface* screen, SDL_Rect* dest);
void Sprite_Animate(Sprite* sprite);

#endif // SPRITE_H_INCLUDED
