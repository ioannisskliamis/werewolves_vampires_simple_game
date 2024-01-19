#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "Being.h"
#include "Creature.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

using namespace std;

// Constructor with default parameters
Creature::Creature(const int x_v, const int y_v, const int health_v, const int attack_lv_v, const int defense_lv_v, const int id_v)
	: health {health_v}, attack_lv {attack_lv_v}, defense_lv {defense_lv_v}, id {id_v}, Being {x_v, y_v} {

	// All creatures start with maximum health
	if (this->health == 0) {
		this->health = this->max_health;
	}

	// Attack level is determined randomly for everyone
	if (this->attack_lv == 0) {
		this->attack_lv = rand() % 3 + 1;
	}

	// Defense level is determined randomly for everyone
	if (this->defense_lv == 0) {
		this->defense_lv = rand() % 2 + 1;
	}
	return;
}


// Copy constructor
Creature::Creature(const Creature& src)
	: Being (src) {
	this->health = src.health;
	this->attack_lv = src.attack_lv;
	this->defense_lv = src.defense_lv;
	this->id = src.id;
	return;
}

// Destructor
Creature::~Creature() {
	return;
}

// Returns creature's health
int Creature::get_health() const {
	return this->health;
}

// Returns creature's attack level
int Creature::get_attack_lv() const {
	return this->attack_lv;
}

// Returns creature's defense level
int Creature::get_defense_lv() const {
	return this->defense_lv;
}

// Returns creature's numeric id
int Creature::get_id() const {
	return this->id;
}

// Returns creature's maximum possible health
int Creature::get_max_health() const {
	return this->max_health;
}

// Prints creature's data-members
void Creature::print() const {
	cout << "-------------------------" << endl;
	cout << ".id: ";
	if (typeid(*this) == typeid(Vampire)) {
		cout << "V";
	} else if (typeid(*this) == typeid(Werewolf)) {
		cout << "W";
	}
	cout << this->id << endl;
	cout << ".health: " << this->health << endl;
	cout << ".max_health: " << this->max_health << endl;
	cout << ".attack: " << this->attack_lv << endl;
	cout << ".defense: " << this->defense_lv << endl;
	cout << ".health_potions: " << this->health_potions << endl;
	cout << ".x: " << this->x << endl;
	cout << ".y: " << this->y << endl;
	return;
}

// Prints creature's type and numeric id in color
void Creature::print_id() const {
	if (typeid(*this) == typeid(Vampire)) {
		cout << "\033[0;95;49mV" << this->id << "\033[0m";
	} else if (typeid(*this) == typeid(Werewolf)) {
		cout << "\033[0;93;49mW" << this->id << "\033[0m";
	}
	return;
}

// Checks if the given creature is on the same team as the one calling the function
bool Creature::is_ally(Creature* other) {
	if (typeid(*this) == typeid(*other)) {
		return true;
	} else {
		return false;
	}
}

// Increases creature's health by 1 when healed by an ally or the avatar
void Creature::increase_health() {
	this->health++;
	return;
}

// Decreases creature's health by the damage taken from an attack
void Creature::decrease_health(const int damage) {
	this->health -= damage;

	// No need to go below zero
	if (this->health < 0) {
		this->health = 0;					
	}
	return;
}

// Attacks an opponent
void Creature::attack(Creature* other) {
	// Only attack enemies
	if (!this->is_ally(other)) {
		// Only the strongest attacks or both if they have equal strength
		if (this->attack_lv >= other->get_attack_lv() && this->health > 0) {
			int damage {0};
			damage = this->attack_lv - other->get_defense_lv();

			// Opponent takes damage only if their defense is lower than the attack they received
			if (damage > 0) {
				other->decrease_health(damage);
			}

			// Print message
			this->print_id();
			cout << " attacked ";
			other->print_id();
			cout << endl;
			other->print_id();
			cout << " health: " << other->get_health() << endl;
			system("sleep 2s");
		}
	}
	return;
}

// Heals a teammate
void Creature::heal(Creature* other) {
	// Only heal allies
	if (this->is_ally(other) && this->health > 0) {

		// Heal only those who don't have maximum health
		if (other->get_health() < other->get_max_health()) {

			// Decision to heal is random
			if (rand() % 2) {								
				if (this->health_potions > 0) {
					this->health_potions--;
					other->increase_health();

					// Print message
					this->print_id();
					cout << " healed ";
					other->print_id();
					cout << endl;
					other->print_id();
					cout << " health: " << other->get_health() << endl;
					system("sleep 2s");
				}
			}
		}
	}
	return;
}

// Receives attack from a stronger opponent
void Creature::counter_attack(Creature* other) {
	other->attack(this);
	return;
}

// "neighboors" contains all creatures adjacent to the one calling the function
void Creature::play_turn(Creature** neighboors, const int size) {

	for (int i {0}; i < size; i++) {

		// First heal teammates
		if (this->is_ally(neighboors[i])) {			
			this->heal(neighboors[i]);
		} else if ( (!this->is_ally(neighboors[i])) && this->attack_lv >= neighboors[i]->get_attack_lv()) { 

			// Then attack weaker enemies 
			this->attack(neighboors[i]);
		}
	}

	// Receive damage if you run into a stronger opponent. Happens only once.
	for (int i {0}; i < size; i++) {
		if ( (!this->is_ally(neighboors[i])) && this->attack_lv < neighboors[i]->get_attack_lv()) {
			this->counter_attack(neighboors[i]);
			break;
		}
	}

	return;
}



