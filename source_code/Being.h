#ifndef _BEING_H_
#define	_BEING_H_

class Creature;

using namespace std;

// Abstract class, ancestor to everyone else
class Being {
	protected:
		int health_potions;

		// x, y denote being's position
		int x;							
		int y;
	public:
		// Constructor with default parameters
		Being(const int = 0, const int = 0, const int = 0);
		Being(const Being&);										
		virtual ~Being();												

		// Getter functions for protected data-members
		int get_x() const;
		int get_y() const;

		// Setter functions for position parameters
		void set_x(const int);
		void set_y(const int);

		// Pure virtual functions inherited to everyone
		virtual void play_turn(Creature**, const int) = 0;
		virtual void print() const = 0;
};

#endif



