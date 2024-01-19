#ifndef _WEREWOLF_H_
#define	_WEREWOLF_H_

class Werewolf final: public Creature {
	protected:
		// Changes when werewolves are created or killed
		static int werewolf_count;
	public:
		// Constructor with default parameters
		Werewolf(const int = 0, const int = 0, const int = 0, const int = 0, const int = 0, const int = 0);
		Werewolf(const Werewolf&);
		virtual ~Werewolf();	

		// Functions for static data-member werewolf_count
		static int get_werewolf_count();
		static void decrease_werewolf_count();
		
		// Gives a werewolf the correct possible moves
		virtual int** get_moves(int**) const final;
};

#endif

