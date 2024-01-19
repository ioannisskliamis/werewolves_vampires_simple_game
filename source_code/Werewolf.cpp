#include <iostream>
#include "Being.h"
#include "Creature.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

using namespace std;

// Initializing static data-member
int Werewolf::werewolf_count {0};

// Constructor with default parameters
Werewolf::Werewolf(const int x_v, const int y_v, const int health_v, const int attack_lv_v, const int defense_lv_v, const int id_v)
	: Creature {x_v, y_v, health_v, attack_lv_v, defense_lv_v, id_v} {
	werewolf_count++;
	this->id = werewolf_count;
	return;
}

// Copy constructor
Werewolf::Werewolf(const Werewolf& src)
	: Creature(src) {
	return;
}

// Destructor
Werewolf::~Werewolf() {
	return;
}

// Accessor function for static data-member werewolf_count
int Werewolf::get_werewolf_count() {
	return werewolf_count;
}

// Mutator function for static data-member werewolf_count
void Werewolf::decrease_werewolf_count() {
	werewolf_count--;
	return;
}

// Gives a werewolf the correct possible moves
int** Werewolf::get_moves(int** p) const {

	// Up
	p[0][0] = this->x;
	p[0][1] = this->y - 1;

	// Down
	p[1][0] = this->x;
	p[1][1] = this->y + 1;

	// Left
	p[2][0] = this->x - 1;
	p[2][1] = this->y;

	// Right
	p[3][0] = this->x + 1;
	p[3][1] = this->y;

	return p;
}



