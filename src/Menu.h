#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL\SDL_ttf.h>
#include "MenuOption.h"

#define MENU_CREATION_ERROR "Impossible de creer le menu"
#define MENU_OPTION_ALLOC_ERROR "impossible d'allouer le tableau d'option du menu"

#define FONT_FILE "ressources\\font\\Tr2n.ttf"

#define MAIN_MENU 0
#define GAME_MENU 1

#define MENU_INIT_POSITION 100
#define MENU_OPTION_OFFSET 50
#define MENU_WIDTH 250
#define MENU_HEIGHT 20

class Menu
{
private:
    /** the number of options */
    int option_count;
    /** the selected option */
    int active_option;
    /** the array of options */
    MenuOption** options;
    /** the police used in the menu */
    TTF_Font* police;
    void InitGame();
    void InitApp();
public:
    Menu(int type);
    ~Menu();
    int Play(SDL_Surface* screen);
    void SetActiveOption(int option);
    void Draw(SDL_Surface* screen);
    int TreatOption(int x, int y);

	int getActiveOption() const {
		return active_option;
	}

	void setActiveOption(int activeOption) {
		active_option = activeOption;
	}

	int getOptionCount() const {
		return option_count;
	}

	void setOptionCount(int optionCount) {
		option_count = optionCount;
	}

	MenuOption** getOptions() {
		return options;
	}

	void setOptions(MenuOption** options) {
		this->options = options;
	}

	TTF_Font*& getPolice(){
		return police;
	}

	void setPolice(TTF_Font* police) {
		this->police = police;
	}
};

#endif // MENU_H_INCLUDED
