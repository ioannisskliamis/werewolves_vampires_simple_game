#ifndef _CREATURE_H_
#define	_CREATURE_H_

using namespace std;

class Creature: public Being {
	protected:
		int health;
		int attack_lv;
		int defense_lv;
		int id;
		const int max_health {4};
	public:
		// Constructor with default parameters
		Creature(const int = 0, const int = 0, const int = 0, const int = 0, const int = 0, const int = 0);
		Creature(const Creature&);																					
		virtual ~Creature();																						

		// Getter functions for protected data-members
		int get_health() const;
		int get_attack_lv() const;
		int get_defense_lv() const;
		int get_id() const;
		int get_max_health() const;

		virtual void print() const final;

		// Prints creature's type and numeric id in color							
		void print_id() const;										

		// Checks if the given creature is on the same team
		bool is_ally(Creature*);									

		// Mutator functions for health
		void increase_health();										
		void decrease_health(const int);
		
		void attack(Creature*);										
		void heal(Creature*);										
		void counter_attack(Creature*);	

		// Controls when the creature attacks, heals or receives a counter attack		
		virtual void play_turn(Creature**, const int) final;
		virtual int** get_moves(int**) const = 0;
};

#endif


