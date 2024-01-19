#ifndef _MAP_H_
#define _MAP_H_

#include "Avatar.h"
#include "Creature.h"

using namespace std;

enum floor {empty = 0, earth = 1, tree = 2, river = 3};
enum time_of_day {no_time = 0, day = 1, night = 2};

class Node {
protected:
	// x and y denote the position of a node in the map
	int x;
	int y;
	floor material;
	bool potion;
	Creature* creature;
	Avatar* avatar;
	char visual;
public:
	// Constructor with default parameters
	Node(const int = 0, const int = 0, const floor = empty, const bool = false, Creature* = NULL, Avatar* = NULL, const char = '-');
	~Node();												

	// Getter functions
	int get_x() const;										
	int get_y() const;
	floor get_floor() const;
	bool get_potion() const;
	Creature* get_creature() const;
	Avatar* get_avatar() const;
	char get_visual() const;

	// Setter functions
	void set_x(const int);
	void set_y(const int);
	void set_potion(const bool);
	void set_visual(const char);

	// Checks if the avatar or a creature have entered this node
	bool is_occupied() const;

	// Functions to put players in a position (node)
	void enter_avatar(Avatar*);
	void enter_creature(Creature*);

	// Functions to remove players from a position (node)
	void exit_avatar();
	void exit_creature();

	// Printing functions
	void print_node() const;
	void print_color_visual() const;
};


class Map {
protected:
	int width;
	int height;

	// Day or night
	static time_of_day time;

	// Map is a 2D array of Nodes
	Node** tiles;						
public:
	// Constructor with default parameters
	Map(const int = 0, const int = 0, Node** = NULL);
	~Map();	

	// Getter functions
	int get_width() const;
	int get_height() const;
	static time_of_day get_time_of_day();

	// Returns a node given its position in the map
	Node* get_node(const int, const int) const;

	// Changes day to night and vice-versa
	void flow_time();			

	void print() const;										
	void place_creatures(Creature**, const int);			
	void place_avatar(Avatar*);		
};

#endif

