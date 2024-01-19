#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "Being.h"
#include "Creature.h"
#include "Avatar.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

using namespace std;

// Constructor with default parameters
Avatar::Avatar(const team supporting_team_v, const int x_v, const int y_v)
	: supporting_team {supporting_team_v}, Being {x_v, y_v} {

	if (this->supporting_team == neutral) {
		cout << "Which team do you support?" << endl;
		cout << "Press W for Werewolves of V for Vampires: ";

		// Exception handling for user input
		char input {};
		cin >> input;
		if (input == 'W' || input == 'w') {
			this->supporting_team = werewolves;
		} else if (input == 'V' || input == 'v') {
			this->supporting_team = vampires;
		} else {
			this->supporting_team = (team) (rand() % 2 + 1);
			cout << "Your team was chosen randomly." << endl;
			system("sleep 2s");
		}	
	}
	return;
}

// Copy constructor
Avatar::Avatar(const Avatar& src)
	: Being {src} {
	this->supporting_team = src.supporting_team;
	return;
}

// Destructor
Avatar::~Avatar() {
	return;
}

// Returns the avatar's supporting team
team Avatar::get_supporting_team() const {
	return this->supporting_team;
}

// Prints all data-members
void Avatar::print() const {
	cout << "---------------------------" << endl;
	cout << "Avatar.supporting_team: ";

	switch (this->supporting_team) {
		case (0):
			cout << "neutral" << endl;
			break;
		case(1):
			cout << "vampires" << endl;
			break;
		case(2):
			cout << "werewolves" << endl;
			break;
		default:
			cout << "invalid" << endl;
	};

	cout << "Avatar.health_potions: " << this->health_potions << endl;
	cout << "Avatar.x: " << this->x << endl;
	cout << "Avatar.y: " << this->y << endl;
	return;
}

// Heals all members of the avatar's supporting team
void Avatar::heal_team(Creature** allies, const int size) {

	// Checking if it's the correct time to heal team
	time_of_day cur_time {};
	cur_time = Map::get_time_of_day();
	if ((cur_time == day && this->supporting_team == vampires) ||
		(cur_time == night && this->supporting_team == werewolves)) {

		// Error checking for typeid used on dead creature
		int i {0}, j {-1};
		do {
			// Looking for the first alive ally to prevent typeid(NULL) from causing error
			if (allies[i] != NULL) {					
				j = i;
			}
			i++;
		} while (i < size || j == -1);

		// Checking if the function was called for the correct team
		if ( (this->supporting_team == vampires && typeid(*allies[j]) == typeid(Vampire)) ||
			 (this->supporting_team == werewolves && typeid(*allies[j]) == typeid(Werewolf)) ) {

			// Use one health potion
			this->health_potions--;							
			for (int i {0}; i < size; i++) {
				// Heal only alive players
				if (allies[i] != NULL) {
					// Heal only those who need healing
					if (allies[i]->get_health() < allies[i]->get_max_health()) {
						allies[i]->increase_health();
					}
				}
			}
			// Print message in color
			if (this->supporting_team == vampires) {
				cout << "\033[0;95;49mAvatar healed the vampires\033[0m" << endl;
			} else if (this->supporting_team == werewolves) {
				cout << "\033[0;93;49mAvatar healed the werewolves\033[0m" << endl;
			}
		}
	} 
	return;
}

// Called when avatar acquires a health potion from the map.
void Avatar::take_new_potion() {
	this->health_potions++;
	cout << "The avatar acquired a new health potion." << endl;
	system("sleep 2s");
	return;
}

// Pauses the game and prints some general statistics
void Avatar::pause_game() const {
	cout << "Do you want to pause the game? (Y/N): ";
	char input {};
	do {
		input = getc(stdin);
	} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');

	switch (input) {
		case 'Y':
		case 'y':
			// Skip "Enter" in buffer
			getc(stdin);
			system("clear");
			cout << "Game paused" << endl;
			cout << "=============================" << endl;
			cout << "==========Statistics=========" << endl;
			cout << "=============================" << endl;

			cout << "Time of day: ";												
			if (Map::get_time_of_day() == day) {
				cout << "Daytime" << endl;
			} else if (Map::get_time_of_day() == night) {
				cout << "Nighttime" << endl;
			}

			cout << "Avatar supports: ";											
			if (this->supporting_team == vampires) {
				cout << "Vampires" << endl;
			} else if (this->supporting_team == werewolves) {
				cout << "Werewolves" << endl;
			}

			// Print alive creatures and number of health potions
			cout << "Alive vampires: " << Vampire::get_vampire_count() << endl;		
			cout << "Alive werewolves: " << Werewolf::get_werewolf_count() << endl;
			cout << "Avatar health potions: " << this->health_potions << endl;
			cout << endl << endl << endl << endl << endl;
			this->exit_game();
			break;
		case 'N':
		case 'n':
			return;
		default:
			cout << "Invalid option! Continuing gameplay..." << endl;
	}
	return;
}

// Stops game and exits
void Avatar::exit_game() const {
	cout << "Do you want to exit the game? (Y/N): ";
	char input {};
	do {
		input = getc(stdin);
	} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');
	if (input == 'Y' || input == 'y') {
		system("clear");
		cout << "Game over! Exiting..." << endl;
		exit(0);
		return;
	} else {
		return;
	}
}

// Handles keyboard input for movement 
int* Avatar::get_move(int* p) {
	char input {};
	bool flag {true};
	do {
		input = getc(stdin);
		// Check for escape char			
		if (input == '\033') {
			// skip '['s					
			input = getc(stdin);					
			input = getc(stdin);
			switch (input) {

				// Case Up
				case ('A'):				
					flag = false;
					p[0] = this->get_x();
					p[1] = this->get_y() - 1;
					break;

				// Case Down	
				case ('B'):							
					flag = false;
					p[0] = this->get_x();
					p[1] = this->get_y() + 1;
					break;

				// Case Right
				case ('C'):							
					flag = false;
					p[0] = this->get_x() + 1;
					p[1] = this->get_y();
					break;

				// Case Left
				case ('D'):							
					flag = false;
					p[0] = this->get_x() - 1;
					p[1] = this->get_y();
					break;

				default :
					flag = true;
					break;
			}
		} else if (input == ' ') {
			// Avatar can stay still by pressing space in case it's temporarily trapped	
			flag = false;
			p[0] = this->get_x();
			p[1] = this->get_y();
		} else {
			// Input can only be an ARROW key or SPACE
			flag = true;
		}
	} while (flag);
	return p;
}

// Gives avatar all available choices
void Avatar::play_turn(Creature** allies, const int size) {
	time_of_day cur_time {Map::get_time_of_day()};

	// Vampires can be healed during the day and werewolves can be healed during the night
	if (((cur_time == day && this->supporting_team == vampires) ||
		(cur_time == night && this->supporting_team == werewolves)) && this->health_potions > 0) {

		// Give player the choice
		cout << "Do you want to heal your allies? (Y/N): ";
		char input {};
		do {
			input = getc(stdin);
		} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');
		if (input == 'Y' || input == 'y') {
			this->heal_team(allies, size);
		}
	}

	// Avatar can pause or exit the game once in every round
	this->pause_game();
	return;
}



