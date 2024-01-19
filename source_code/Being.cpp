#include <iostream>
#include <cstdlib>
#include "Being.h"

using namespace std;

// Constructor with default parameters
Being::Being(const int x_v, const int y_v, const int health_postions_v)
	: x {x_v}, y {y_v}, health_potions {health_postions_v} {

	// Number of health potions is determined randomly
	if (this->health_potions == 0) {
		this->health_potions = rand() % 2 + 1;		
	}
	return;
}

// Copy constructor
Being::Being(const Being& src) {
	this->health_potions = src.health_potions;
	this->x = src.x;
	this->y = src.y;
	return;
}

// Destructor
Being::~Being() {
	return;
}

// Returns a being's x position parameter
int Being::get_x() const {
	return this->x;
}

// Returns a being's y position parameter
int Being::get_y() const {
	return this->y;
}

// Changes a being's x position parameter. Used when moving or fleeing
void Being::set_x(const int x_v) {
	this->x = x_v;
	return;
}

// Changes a being's y position parameter. Used when moving or fleeing
void Being::set_y(const int y_v) {
	this->y = y_v;
	return;
}



