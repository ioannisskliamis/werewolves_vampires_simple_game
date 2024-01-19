#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include "Being.h"
#include "Creature.h"
#include "Avatar.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Map.h"
#include "Game.h"

using namespace std;

int main(void) {

	srand(time(NULL));

	system("clear");
	cout << "Welcome!!!" << endl;
	cout << "WnV_the_game starts now!" << endl;
	cout << "The rules are simple: " << endl;
	cout << "1) You can make your avatar move by pressing an ARROW key and then ENTER." << endl;
	cout << "2) You can make your avatar stay still by pressing SPACE  and then ENTER." << endl;
	cout << "3) Your avatar has the same color as the team you support." << endl;
	cout << "4) At the start of every round you can pause or exit the game." << endl;
	cout << "5) At the start of every round you can heal the team you support. If you have a health potion, that is..." << endl;
	cout << "6) There's a health potion placed on the map. Acquire it and give your team the advantage." << endl;
	cout << "======================================================================" << endl;
	cout << "If you're ready to play, press ENTER." << endl;

	getc(stdin);

	system("clear");

	// Exception handling for invalid map size
	int width {0};
	int height {0};	
	cout << "Enter width of map. (min 5 - max 15 for width of map): ";
	cin >> width;
	cout << "Enter height of map. (min 5 - max 15 for height of map): ";
	cin >> height;
	if ((width < 5 || width > 15) && (height < 5 || height > 15)) {
		cout << "Invalid input! Default size of map is 10x10." << endl;
		width = 10;
		height = 10;
		system("sleep 2s");
	}

	system("clear");

	Game g {width, height};

	g.start();

	return 0;
}

