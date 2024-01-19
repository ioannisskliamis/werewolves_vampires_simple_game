#ifndef _GAME_H_
#define _GAME_H_

#include "Creature.h"
#include "Map.h"
#include "Avatar.h"

class Game {
	private:
		// Used for change between day and night.
		static int count_time;

		// Number of creatures	
		int num;					

	public:
		Map* map;
		// Array of vampires
		Creature** v;
		// Array of werewolves
		Creature** w;
		Avatar* a;

		// Constructor with default parameters
		Game(const int = 0, const int = 0, const int = 0, Map* = NULL, Creature** = NULL, Creature** = NULL, Avatar* = NULL);
		~Game();												

		// Checks if a position [x][y] is out of the map
		bool is_out_of_bounds(const int [2]) const;

		// Functions for movement on the map
		void move_creature(Creature*);				
		void move_avatar();

		void kill(Creature*);

		// Updates arrays and static count variables after creatures die
		void dead_creatures();		

		void prepare_turn(Creature*);
		void play_round();									
		void start();		
};

#endif



