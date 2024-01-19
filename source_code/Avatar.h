#ifndef _AVATAR_H_
#define	_AVATAR_H_

#include "Creature.h"
#include "Being.h"

using namespace std;

enum team {neutral = 0, vampires = 1, werewolves = 2};

class Avatar: public Being {
	protected:
		team supporting_team;
	public:
		// Constructor with default parameters
		Avatar(const team = neutral, const int = 0, const int = 0);
		Avatar(const Avatar&); 													
		virtual ~Avatar();														

		team get_supporting_team() const;       								
		virtual void print() const final;										

		void heal_team(Creature**, const int);									
		void take_new_potion();													
		void pause_game() const;
		void exit_game() const;

		// Handles keyboard input for movement
		int* get_move(int*);

		// Gives avatar all available choices												
		virtual void play_turn(Creature**, const int) final;												

};

#endif




