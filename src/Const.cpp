#include <SDL\SDL.h>
#include "Const.h"

/** Load an image on a surface
 * @param fichier : the file path of the image on the computer
 * @return a SDL_Surface that contains the image
 * @warning the surface have been inited with malloc
*/
SDL_Surface* LoadImage(const char* fichier)
{
    SDL_Surface* image;
    image = SDL_LoadBMP(fichier);
    if (image == NULL)
    {
        fprintf(stderr, "Echec de chargement du fichier %s : %s.\n", fichier, SDL_GetError());
        exit(-1);
    }
    // fix the transparance key
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 0));
    return image;
}

/** Parse the time specified in parameter
 * @param time : time
 * @warning the time is in milliseconds
 * @return the time formated on a string
*/
char* Parse_Time(int time)
{
    int s = 0;
    int m = 0;
    int h = 0;
    char* str = (char*)malloc(sizeof(char)*9);
    if(str == NULL)
    {
        printf("...");
        exit(-1);
    }

    s = time/1000;

    while(s >= 60)
    {
        s -= 60;
        m += 1;
    }

    while(m >= 60)
    {
        m -= 60;
        h += 1;
    }

    sprintf(str, "%.2d:%.2d:%.2d", h, m, s);

    return str;
}

/** Generic function that draws a rectangle on the screen
 * @param screen : the surface where the rect is drawn
 * @param x : the horizontal origin of the rect
 * @param y : the vertical origin of the rect
 * @param w : the width of the rect
 * @param h : the height of the rect
 * @param r : the ammount of red in the rect's color
 * @param g : the ammount of green in the rect's color
 * @param b : the ammount of blue in the rect's color
*/
void Draw_Rect(SDL_Surface* screen, int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect position = Create_Rect(x, y, w, h);

    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 16, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(screen->format, r, g, b));

    SDL_BlitSurface(surface, NULL, screen, &position);

    SDL_FreeSurface(surface);
}

/** Generic function that init a rectangle
 * @param x : the horizontal origin of the rect
 * @param y : the vertical origin of the rect
 * @param w : the width of the rect
 * @param h : the height of the rect
 * @return a SDL_Rect with the size specified
 * @warning the SDL_Rect is NOT allocated dynamicly
*/
SDL_Rect Create_Rect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void copyStringWithLength(char * dest, const char * src, size_t destSize)
{
    unsigned int i=0;
    while((i<destSize-1)&&(src[i]!='\0'))
    {
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * duplicateString(const char * str)
{
    char * mem =(char *)malloc(sizeof(char)*(strlen(str)+1));
    if (mem == NULL)
    {
        printf("erreur dans l'allocation de duplicateString");
        exit(-1);
    }
    copyStringWithLength(mem,str,strlen(str)+1);
    return mem;
}

