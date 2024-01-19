#ifndef _VAMPIRE_H_
#define	_VAMPIRE_H_

class Vampire final: public Creature {
	protected:
		// Changes when vampires are created or killed
		static int vampire_count;
	public:
		// Constructor with default parameters
		Vampire(const int = 0, const int = 0, const int = 0, const int = 0, const int = 0, const int = 0); 
		Vampire(const Vampire&);			
		virtual ~Vampire();				

		// Functions for static data-member vampire_count
		static int get_vampire_count();
		static void decrease_vampire_count();
		
		// Gives a vampire the correct possible moves
		virtual int** get_moves(int**) const final;
};

#endif



