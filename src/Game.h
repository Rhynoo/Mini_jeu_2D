#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Map.h"
#include "Character.h"

/** an error message that apears when the game's allocation fails*/
#define GAME_CREATION_ERROR "Impossible de creer le jeu"

class Game
{
private:
    /** the score of the player */
    int score;
    /** the time spent in game */
    unsigned int time;
    int Update(Character* ch, Map* map, SDL_Surface* screen);
    void Draw(Character* ch, Map* map, SDL_Surface* screen);
public:
    Game();
    int Play(Character* ch, Map* map, SDL_Surface* screen);

	int getScore() const {
		return score;
	}

	void setScore(int score) {
		this->score = score;
	}

	unsigned int getTime() const {
		return time;
	}

	void setTime(unsigned int time) {
		this->time = time;
	}
};

#endif // GAME_H_INCLUDED
