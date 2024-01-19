#include <iostream>
#include <cstdlib>
#include "Being.h"
#include "Creature.h"
#include "Avatar.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

// Initializing static data-member. Used for change between day and night.
int Game::count_time {0};

// Constructor with default parameters
Game::Game(const int width_v, const int height_v, const int num_v, Map* map_v, Creature** v_v, Creature** w_v, Avatar* a_v)
	: num {num_v}, map {map_v}, v {v_v}, w {w_v}, a {a_v} {

	// Creating the map
	if (this->map == NULL) {
		this->map = new Map {width_v, height_v};
	}

	// Creating the Avatar and placing it on the map
	if (this->a == NULL) {	
		this->a = new Avatar {};
		this->map->place_avatar(this->a);
	}

	// Calculating number of creatures
	if (this->num == 0) {
		int max_num {(width_v * height_v) / 15};
		this->num =	rand() % max_num + 5;	
	}

	// Creating creatures and placing them on the map
	this->v = new Creature*[this->num];	
	this->w = new Creature*[this->num];
	for (int i {0}; i < this->num; i++) {
		v[i] = new Vampire {};
		w[i] = new Werewolf {};
	}
	this->map->place_creatures(this->v, this->num);
	this->map->place_creatures(this->w, this->num);

	// Outputing map
	this->map->print();		

	return;
}

// Destructor
Game::~Game() {
	for (int i {0}; i < this->num; i++) {
		delete this->v[i];
		delete this->w[i];
	}
	delete [] v;
	delete [] w;
	delete this->a;
	delete this->map;
	return;
}

// Check if a pair of coordinates is within the limits of the map
bool Game::is_out_of_bounds(const int p[2]) const {
	if ((p[0] < 0) || (p[1] < 0) || (p[0] > (this->map->get_width() - 1)) || (p[1] > (this->map->get_height() - 1))) {
		return true;
	} else {
		return false;
	}
}

// Moves a creature correctly on the map
void Game::move_creature(Creature* c) {

	// Getting the correct number of possible movements for a creature
	int limit {};											
	if (typeid(*c) == typeid(Vampire)) {
		limit = 8;
	} else if (typeid(*c) == typeid(Werewolf)) {
		limit = 4;
	}

	// Getting movements for all directions depending on type of creature
	int** all_moves {};																				
	all_moves = new int*[limit] {};
	for (int k {0}; k < limit; k++) {
		all_moves[k] = new int[2] {};
	}
	all_moves = c->get_moves(all_moves);

	// Decision to move is random
	if (rand() % 2) {		
		// Used to decide which subset of all_moves are valid
		int** possible_moves {};														
		possible_moves = new int*[limit] {};
		for (int k {0}; k < limit; k++) {
			possible_moves[k] = new int[2] {};
		}

		int size {0};
		for (int k {0}; k < limit; k++) {
			// Don't move out of the map
			if (this->is_out_of_bounds(all_moves[k])) {						
				continue;
			} else {
				Node* n {};
				n = this->map->get_node(all_moves[k][0], all_moves[k][1]);

				// Can't pass through obstacles or occupied positions
				if (n->get_floor() != earth || n->is_occupied()) {		
					continue;
				} else {
					// If movement is valid, put it in the subset
					possible_moves[size][0] = all_moves[k][0];
					possible_moves[size][1] = all_moves[k][1];
					size++;
				}
			}			
		}
		if (size > 0) {
			// Pick a position randomly
			int i = rand() % size;			
			Node* next = this->map->get_node(possible_moves[i][0], possible_moves[i][1]);
			Node* prev = this->map->get_node(c->get_x(), c->get_y());

			// Enter the new position and leave the previous one
			next->enter_creature(c);					
			prev->exit_creature();
		}
		// Print message
		this->map->get_node(c->get_x(), c->get_y())->print_color_visual();
		cout << " moved." << endl;

		// Freeing all allocated memory
		for (int k {0}; k < limit; k++) {	
			delete all_moves[k];
			delete possible_moves[k];
		}
		delete [] all_moves;
		delete [] possible_moves;
	} else {
		// Print message of creature stood still
		this->map->get_node(c->get_x(), c->get_y())->print_color_visual();
		cout << " stood still." << endl;
	}
	system("sleep 2s");
	this->map->print();
	return;
}

// Moves the avatar correctly on the map
void Game::move_avatar() {

	cout << "It's the avatar's turn to move. " << endl;
	cout << "Use the ARROW keys or press SPACE: " << endl;
	int* p {};
	// p is a pair of coordinates x and y
	p = new int[2] {};
	bool flag {true};
	do {
		// Get the correct move from the keyboard
		p = this->a->get_move(p);	
		// Make sure it doesn't go off the map
		if (this->is_out_of_bounds(p)) {		
			flag = true;
			cout << "Ivalid movement! Try again!" << endl;
		} else {
			Node* next {};
			Node* prev {};
			next = this->map->get_node(p[0], p[1]);
			prev = this->map->get_node(this->a->get_x(), this->a->get_y());
			// Check if position is occupied by a creature
			if (next->get_creature() != NULL) {				
				flag = true;
				cout << "Position is occupied!" << endl;
			} else if (next->get_floor() != earth) {
				// Check if position is walkable	
				flag = true;
				cout << "You run into an obstacle!" << endl;
			} else {
				flag = false;
				if (next->get_potion()) {
					// Get the potion if you found it					
					this->a->take_new_potion();
					next->set_potion(false);
				}
				// Make the move
				prev->exit_avatar();					
				next->enter_avatar(this->a);
			}
		}
	} while (flag);
	delete p;
	return;
}

// Check if creatures died after a creature's turn
void Game::dead_creatures() {
	for (int k {0}; k < this->num; k++) {
		// If a werewolf is not already dead
		if (w[k] != NULL) {				
			if (w[k]->get_health() == 0) {			
				// Kill it if it's health reached 0
				this->kill(w[k]);					
				this->map->print();
			}
		}
		// If a vampire is not already dead
		if (v[k] != NULL) {
			// Kill it if it's health reached 0							
			if (v[k]->get_health() == 0) {
				this->kill(v[k]);					
				this->map->print();
			}
		}
	}
	return;
}

// Function that kills a creature
void Game::kill(Creature* c) {

	// Print message
	c->print_id();													
	cout << " is dead." << endl;
	system("sleep 2s");
	this->map->print();

	// Taking creature out of the map
	Node* n {};														
	n = this->map->get_node(c->get_x(), c->get_y());
	n->exit_creature();

	// Decrease the correct count variable
	if (typeid(*c) == typeid(Vampire)) {							
		Vampire::decrease_vampire_count();

		// Change creature array element to NULL to show that the creature is dead
		this->v[c->get_id() - 1] = NULL;	

	} else if (typeid(*c) == typeid(Werewolf)) {
		Werewolf::decrease_werewolf_count();
		this->w[c->get_id() - 1] = NULL;
	}
	return;
}

// Finds the creatures adjacent to the one calling the function. Precursor to play_turn().
void Game::prepare_turn(Creature* c) {

	// Getting the correct number for all possible movements of a creature
	int limit {};																							
	if (typeid(*c) == typeid(Vampire)) {
		limit = 8;
	} else if (typeid(*c) == typeid(Werewolf)) {
		limit = 4;
	}

	// "neighbours" contains all the adjacent creatures
	Creature** neighbours {};										

	// Getting movements for all directions depending on type of creature
	int** all_moves {};												
	all_moves = new int*[limit] {};
	neighbours = new Creature*[limit] {};
	for (int k {0}; k < limit; k++) {
		all_moves[k] = new int[2] {};
	}
	all_moves = c->get_moves(all_moves);

	int size {0};
	for (int k {0}; k < limit; k++) {
		// Make sure creature is looking within the limits of the map
		if (this->is_out_of_bounds(all_moves[k])) {					
			continue;
		} else {
			Node* n {};
			n = this->map->get_node(all_moves[k][0], all_moves[k][1]);

			if (n->is_occupied() && n->get_creature() != NULL) {	
				// Check is position is occupied by another creature and not the avatar
				neighbours[size] = n->get_creature();
				size++;
			}
		}
	}

	// Creature interacts with all its neighbours (attack/heal)
	c->play_turn(neighbours, size);									

	// Freeing all allocated memory
	for (int k {0}; k < limit; k++) {								
		delete all_moves[k];
	}
	delete [] all_moves;
	return;
}

// Starts with the avatar's turn and then every creature has their turn
void Game::play_round() {

	// Avatar moves first
	this->move_avatar();										
	this->map->print();

	// Make sure the avatar interracts only with the team they support
	if (this->a->get_supporting_team() == vampires) {			
		this->a->play_turn(this->v, Vampire::get_vampire_count());
	} else if (this->a->get_supporting_team() == werewolves) {
		this->a->play_turn(this->w, Werewolf::get_werewolf_count());
	}
	this->map->print();

	// Repeat for every creature
	for (int i {0}; i < this->num; i++) {										

		// Start with the first vampire
		if (this->v[i] != NULL) {												
			int health_before = 0, health_after = 0;
			health_before = v[i]->get_health();

			// Give them a chance to move
			this->move_creature(this->v[i]);

			// Give them a chance to play after the move									
			this->prepare_turn(v[i]);											
			this->map->print();

			// Trying to flee if any damage was received by a counter attack
			health_after = v[i]->get_health();									
			if (health_after < health_before && health_after != 0) {
				this->move_creature(this->v[i]);
				this->map->print();
			}
		}
		
		// Check for dead creatures
		this->dead_creatures();													

		// Check if anybody won
		if (Werewolf::get_werewolf_count() == 0 || Vampire::get_vampire_count() == 0) {	
			return;
		}

		// Same thing for werewolves
		if (this->w[i] != NULL) {												
			int health_before = 0, health_after = 0;
			health_before = w[i]->get_health();
			this->move_creature(this->w[i]);
			this->prepare_turn(w[i]);
			this->map->print();

			health_after = w[i]->get_health();									
			if (health_after < health_before && health_after != 0) {
				this->move_creature(this->w[i]);
				this->map->print();
			}
		}

		this->dead_creatures();										

		// Check if anybody won
		if (Werewolf::get_werewolf_count() == 0 || Vampire::get_vampire_count() == 0) {
			return;
		}
	}
	return;
}

// Starts game and loops until one team wins
void Game::start() {
	int vc {0}, wc {0};
	vc = Vampire::get_vampire_count();
	wc = Werewolf::get_werewolf_count();

	// Loop while there are creatures alive from both teams
	while (vc != 0 && wc != 0) {

		// Day and night alternate every 5 rounds
		if (count_time == 5) {						
			this->map->flow_time();
			count_time = 0;
		}	

		// Everyone makes a move
		this->play_round();							
		vc = Vampire::get_vampire_count();
		wc = Werewolf::get_werewolf_count();
		count_time++;
	}

	// Print the correct message for the winner in color
	if (vc == 0) {
		cout << "\033[0;93;49mWerewolves are the winners!\033[0m" << endl;
	} else if (wc == 0) {
		cout << "\033[0;95;49mVampires are the winners!\033[0m" << endl;
	}

	return;
}


