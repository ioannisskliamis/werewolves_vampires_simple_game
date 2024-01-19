#include <iostream>
#include <cstdlib>
#include "Being.h"
#include "Creature.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

using namespace std;

// Initializing static data-member
int Vampire::vampire_count {0};

// Constructor with default parameters
Vampire::Vampire(const int x_v, const int y_v, const int health_v, const int attack_lv_v, const int defense_lv_v, const int id_v)
	: Creature {x_v, y_v, health_v, attack_lv_v, defense_lv_v, id_v} {
	vampire_count++;
	this->id = vampire_count;
	return;
}

// Copy constructor
Vampire::Vampire(const Vampire& src)
	: Creature(src) {
	return;
}

// Destructor
Vampire::~Vampire() {
	return;
}

// Accessor function for static data-member vampire_count
int Vampire::get_vampire_count() {
	return vampire_count;
}

// Mutator function for static data-member vampire_count
void Vampire::decrease_vampire_count() {
	vampire_count--;
	return;
}

// Gives a vampire the correct possible moves
int** Vampire::get_moves(int** p) const {

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

	// Up - Left
	p[4][0] = this->x - 1;
	p[4][1] = this->y - 1;

	// Up - Right
	p[5][0] = this->x + 1;
	p[5][1] = this->y - 1;

	// Down - Left
	p[6][0] = this->x - 1;
	p[6][1] = this->y + 1;

	// Down - Right
	p[7][0] = this->x + 1;
	p[7][1] = this->y + 1;

	return p;
}


