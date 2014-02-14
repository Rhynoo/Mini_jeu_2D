#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

/** the width of the game screen */
#define SCREEN_WIDTH 640
/** the height of the game screen (does not include the border for the interface)*/
#define SCREEN_HEIGHT 480

/** the width of a MapBlock*/
#define BLOC_WIDTH 32
/** the height of a MapBlock*/
#define BLOC_HEIGHT 32
/** the number of MapBlocks in a MapSection vertically*/
#define MAP_IN_WIDTH 20
/** the number of MapBlocks in a MapSection vertically*/
#define MAP_IN_HEIGHT 15

/** The value that defines if a MapBlock blocs the character*/
#define WALKABLE 50
/** the value that defines if a MapBlock hurts a character*/
#define DANGEROUS 30
/** the value that defines the MapBlock for the Labyrinth's exit*/
#define WIN 42

/** the init speed of a character*/
#define BASE_SPEED 4
/** the highest value a character's life can be */
#define MAX_LIFE 100

/** Defines all the possible directions for a character*/
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NO_DIRECTION
};

/** Defines all the possible option's treatement for a MenuOption */
enum OPTION
{
    OPTION_IN_MENU,
    OPTION_RESUME_GAME,
    OPTION_SAVE_GAME,
    OPTION_LOAD_GAME,
    OPTION_NEW_GAME,
    OPTION_EXIT_TO_MAIN_MENU,
    OPTION_EXIT_TO_DESKTOP,
    NO_OPTION
};

/** Defines all the possible status a Game can be */
enum GAME_STATUS
{
    STATUS_INGAME,
    STATUS_GAMELOSE,
    STATUS_GAMEWIN
};

/** Defines the path for the font used by SDL_TTF to write on the screen */
#define FONT_FILE "ressources\\font\\Tr2n.ttf"

/** Defines the path of the direction were the item's ressources are */
#define ITEM_FILE "ressources\\item\\"

SDL_Surface* LoadImage(const char* fichier);
char* Parse_Time(int time);
void Draw_Rect(SDL_Surface* screen, int x, int y, int w, int h, int r, int g, int b);
SDL_Rect Create_Rect(int x, int y, int w, int h);
void copyStringWithLength(char * dest, const char * src, size_t destSize);
char * duplicateString(const char * str);

#endif // CONST_H_INCLUDED
