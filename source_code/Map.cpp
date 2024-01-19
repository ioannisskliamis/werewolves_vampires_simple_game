#include <iostream>
#include <typeinfo>
#include "Being.h"
#include "Avatar.h"
#include "Creature.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"

using namespace std;

// Helper function to place obstacles in the map
inline int randomize() {
	double val = (double)rand() / RAND_MAX;
	int random {};

	// Making sure there aren't too many obstacles
	if(val < 0.1) {
		random = 1;
	} else if(val < 0.2) {
		random = 2;
	} else {
		random = 0;
	}
	return random + 1;
}

// Constructor with default parameters
Node::Node(const int x_v, const int y_v, const floor material_v, const bool potion_v, Creature * creature_v, Avatar* avatar_v, const char visual_v)
	: x {x_v}, y {y_v}, material {material_v}, potion {potion_v}, creature {creature_v}, avatar {avatar_v}, visual {visual_v}  {								//Constructor
	
	// Randomly choose wether a position is walkable or has an obstacle
	if (this->material == empty) {
		this->material = (floor) randomize();
	}

	// Put the correct position symbol on the map
	switch (this->material) {
		case (earth):
			this->visual = '*';
			break;
		case (river):
			this->visual = 'R';
			break;
		case (tree):
			this->visual = 'T';
			break;
		default:
			this->visual = '-';
	}

	return;
} 

// Destructor
Node::~Node(){		
	// Take care of creature pointer
	if (this->creature != NULL) {
		this->exit_creature();
	}

	// Take care of avatar pointer
	if (this->avatar != NULL) {
		this->exit_avatar();
	}
	return;
}

// Returns node's x position parameter
int Node::get_x() const {
	return this->x;
}

// Returns node's y position parameter
int Node::get_y() const {
	return this->y;
}

// Returns the floor material of a map position
floor Node::get_floor() const{
	return this->material;
}

// Returns wether this position has a health potion
bool Node::get_potion() const{
	return this->potion;
}

// Returns pointer to the creature occupying this position
Creature* Node::get_creature() const{
	return this->creature;
}

// Returns pointer to the avatar occupying this position
Avatar* Node::get_avatar() const{
	return this->avatar;
}

// Returns this node's visualization symbol
char Node::get_visual() const{
	return this->visual;
}

// Changes the x position parameter of a Node. Used only in constructor.
void Node::set_x(const int x_v) {
	this->x = x_v;
	return;
}

// Changes the y position parameter of a Node. Used only in constructor.
void Node::set_y(const int y_v) {
	this->y = y_v;
	return;
}

// Used when avatar acquires a new potion or when the potion is placed on the map for the first time
void Node::set_potion(bool v){
	if (this->material == earth) {
		this->potion = v;
		if (this->potion) {
			this->visual = 'P';
		} else {
			this->visual = '*';
		}
	}
	return;
}

// Changes the visualization symbol
void Node::set_visual(char c) {
	this->visual = c;
	return;
}

// True if a creature or the avatar is occupying this position
bool Node::is_occupied() const {
	if (this->creature == NULL && this->avatar == NULL) {
		return false;
	} else {
		return true;
	}
}

// Puts avatar in a position on the map
void Node::enter_avatar(Avatar* new_avatar) {
	// Avatar can enter only empty positions
	if (!this->is_occupied()) {
		this->avatar = new_avatar;

		// Update avatar's x and y position parameters
		this->avatar->set_x(this->x);
		this->avatar->set_y(this->y);
		this->visual = 'A';
	}
	return;
}
	
// Puts avatar in a position on the map
void Node::enter_creature(Creature* new_creature) {
	
	// Creatures can enter only empty positions
	if (!this->is_occupied()) {
		this->creature = new_creature;
		this->creature->set_x(this->x);
		this->creature->set_y(this->y);

		// Change the visualization symbol accordingly
		if (typeid(*new_creature) == typeid(Vampire)) {
			this->visual = 'V';
		} else if (typeid(*new_creature) == typeid(Werewolf)) {
			this->visual = 'W';
		}
	}
	return;
}

// Empties position after avatar has moved
void Node::exit_avatar() {
	this->avatar = NULL;
	this->visual = '*';
	return;
}

// Empties position after creature has moved
void Node::exit_creature() {
	this->creature = NULL;
	if (this->get_potion()) {
		this->visual = 'P';
	} else {
		this->visual = '*';
	}
	return;
}

// Prints all data-members
void Node::print_node() const {
	cout << "--------------------------" << endl;
	cout << "n.material: " << this->material << endl;
	cout << boolalpha;
	cout << "n.potion: " << this->potion << endl;
	cout << noboolalpha;
	cout << "n.creature: ";
	if (this->creature == NULL) {
		cout << this->creature << endl;
	} else {
		cout << this->get_creature()->get_id() << endl;
	}
	cout << "n.avatar: ";
	if (this->avatar == NULL) {
		cout << this->avatar << endl;
	} else {
		cout << this->get_avatar()->get_supporting_team() << endl;
	}
	cout << "n.visual: " << this->visual << endl;
	return;
}

// Prints visuals in color
void Node::print_color_visual() const {
	switch (this->visual) {
		case '*':
			cout << '*';
			break;
		case 'A':
			// Avatar visual has the same color as the team it supports
			if (this->avatar->get_supporting_team() == vampires) {
				cout << "\033[0;95;49mA\033[0m";
			} else if (this->avatar->get_supporting_team() == werewolves) {
				cout << "\033[0;93;49mA\033[0m";
			}
			break;
		case 'P':
			// Potion is red
			cout << "\033[0;91;49mP\033[0m";
			break;
		case 'T':
			// Trees are green
			cout << "\033[0;92;49mT\033[0m";
			break;
		case 'R':
			// Rivers are blue
			cout << "\033[0;94;49mR\033[0m";
			break;
		case 'W':
			// Print in yellow for werewolves
			cout << "\033[0;93;49mW" << this->get_creature()->get_id() << "\033[0m";
			break;
		case 'V':
			// Print in magenta for vampires
			cout << "\033[0;95;49mV" << this->get_creature()->get_id() << "\033[0m";
			break;
		default:
			cout << '-';
	}
	return;
}

// Initializing static data-member. Used for change between night and day.
time_of_day Map::time {no_time};

// Constructor with default parameters
Map::Map(const int width_v, const int height_v, Node** tiles_v)
	: width {width_v}, height {height_v}, tiles {tiles_v} {			

	// Day or night is chosen randomly
	if (this->time == no_time) {
		this->time = (time_of_day) (rand() % 2 + 1);
	}

	// Creating 2D array
	tiles = new Node*[this->width] {};
	for (int i {0}; i < this->width; i++) {
		tiles[i] = new Node[this->height] {};
	}

	// Giving correct coordinates to nodes
	int i {0}, j {0};
	for (i = 0; i < this->width; i++) {
		for (j = 0; j < this->height; j++) {
			this->tiles[i][j].set_x(i);
			this->tiles[i][j].set_y(j);
		}
	}

	// Placing potion on an empty walkable space
	int potionx {}, potiony {};
	do {
		potionx = rand() % width;
		potiony = rand() % height;
	} while (tiles[potionx][potiony].get_floor() != earth);
	tiles[potionx][potiony].set_potion(true);

	return;
}

// Destructor
Map::~Map() {										
	for (int i {0}; i < this->width; i++) {
		delete[] tiles[i];
	}
	delete[] tiles;
	return;
}

// Returns map width
int Map::get_width() const {
	return this->width;
}

// Returns map height
int Map::get_height() const {
	return this->height;
}

// Returns day or night
time_of_day Map::get_time_of_day() {
	return time;
}

// Returns a node given its coordinates
Node* Map::get_node(const int wanted_x, const int wanted_y) const{
	return &this->tiles[wanted_x][wanted_y];
}

// Changes day to night and vice-versa	
void Map::flow_time() {
	if (time == day) {
		time = night;
	} else if (time == night) {
		time = day;
	}
	return;
}

// Prints map
void Map::print() const{
	system("clear");
	// Print night or day
	if (this->time == day) {
		cout << "It's daytime" << endl;
	} else if (this->time == night) {
		cout << "It's nighttime" << endl;
	}

	// Print squares
	for (int j {0}; j < this->height; j++){
		cout << "_";
		for(int i {0}; i < this->width; i++){
			cout << "____";
		}
		cout << endl;
		for (int k {0}; k < this->width; k++){
			cout <<  "| ";

			// Print the correct visual and/or creature id in color
			this->get_node(k, j)->print_color_visual();
			if (this->get_node(k, j)->get_creature() == NULL) {
				cout << " ";
			}
		}
		cout << "|\n";
	}
	cout << "_";
	for(int h {0}; h < this->width; h++){
		cout << "____";
	}
	cout << endl;
	cout << "x";
	for (int l {0}; l < this->width; l++){
		cout << "xxxx";
	}
	cout << "x" << endl;
	return;
}

// Placing a team of creatures randomly on the map
void Map::place_creatures(Creature** creatures, const int size) {
	for (int k {0}; k < size; k++) {
		// Making sure the position is empty, walkable and doesn't have the potion before placing creature in it
		int i {0}, j {0};
		do {
			i = rand() % width;
			j = rand() % height;
		} while (this->tiles[i][j].is_occupied() || this->tiles[i][j].get_floor() != earth || this->tiles[i][j].get_potion());
		this->tiles[i][j].enter_creature(creatures[k]);
	}
	return;
}

// Placing avatar randomly on the map
void Map::place_avatar(Avatar* entity) {
	// Making sure the position is empty, walkable and doesn't have the potion before placing avatar in it
	int i {0}, j {0};
	do {
		i = rand() % width;
		j = rand() % height;
	} while (this->tiles[i][j].is_occupied() || this->tiles[i][j].get_floor() != earth);
	this->tiles[i][j].enter_avatar(entity);
	return;
}



