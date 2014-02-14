#include <SDL\SDL.h>
#include "Sprite.h"
#include "Const.h"

/** Create a sprite
 * @return a pointer on the sprite created
 * @warning the sprite is created using malloc
*/
Sprite* Sprite_Create()
{
    Sprite* s = (Sprite*)malloc(sizeof(Sprite));
    if(s == NULL)
    {
        printf(SPRITE_CREATION_ERROR);
        exit(-1);
    }

    s->image = NULL;

    return s;
}

/** Inits a sprite
 * @param sprite : the sprite
 * @param image : the path of the image used
 * @param width : the width of the sprite
 * @param height : the height of the sprite
*/
void Sprite_Init(Sprite* sprite, const char* image, int width, int height)
{
    sprite->image = LoadImage(image);

    // le sprite n'est pas animé par defaut
    sprite->anim = 0;
    // on commence par la première animation
    sprite->anim_courante = 0;
    // le sprite dispose de trois animations
    sprite->total_anims = 4;

    //we fix the direction to down first to fix the character's view to down
    Sprite_SetOrientation(sprite, DOWN);
    Sprite_SetOrientation(sprite, NO_DIRECTION);

    sprite->temps_anim_courante = 0;
    // On definit ensuite les dimentions du sprite.

    sprite->source = Create_Rect(sprite->anim_courante * width, sprite->orientation * height,
                                 width, height);
}

/** Frees a sprite
 * @param sprite : the sprite
*/
void Sprite_Destroy(Sprite* sprite)
{
    if(sprite != NULL)
    {
        SDL_FreeSurface(sprite->image);
        free(sprite);
    }
}

/** Set the orientation of a sprite
 * @param sprite : the sprite
 * @param orientation : the new orientation for the sprite
*/
void Sprite_SetOrientation(Sprite* sprite, int orientation)
{
    // on affecte l'animation correcpondant à la direction au sprite
    if (orientation != NO_DIRECTION)
    {
        sprite->anim = 1;
        sprite->orientation = orientation;
    }
    else
    {
        // si le sprite est areté, on ne l'anime pas
        sprite->anim = 0;
        // on met la première animation
        sprite->anim_courante = 0;
        sprite->temps_anim_courante = 0;
    }
    // on regle la source de l'image à copier
    sprite->source.y = sprite->orientation * sprite->source.h;
    sprite->source.x = sprite->anim_courante * sprite->source.w;
}

/** Draws a sprite on the screen
 * @param sprite : the sprite
 * @param screen : the main screen of the application
 * @param dest : where the sprite is drown
*/
void Sprite_Draw(Sprite* sprite, SDL_Surface* screen, SDL_Rect* dest)
{
    // enfin, on dessine le sprite à l'ecran
    SDL_BlitSurface(sprite->image, &sprite->source, screen, dest);
}

void Sprite_Animate(Sprite* sprite)
{
        /* si le sprite est animé, on gere l'animation */
    if (sprite->anim)
    {
        // on decremente le temps restant à l'animation courante
        sprite->temps_anim_courante--;
        // et on regarde s'il est temps de changer d'animation
        if ( sprite->temps_anim_courante <= 0 )
        {
            // s'il faut changer, on passe à l'animation suivante
            sprite->anim_courante++;
            // si on était à la dernière animation, on repasse à la première
            if (sprite->anim_courante >= sprite->total_anims)
                sprite->anim_courante = 0;

            // on regle la source à copier
            sprite->source.x = sprite->source.w * sprite->anim_courante;
            sprite->temps_anim_courante = ANIM_TIME;
        }
    }
}
