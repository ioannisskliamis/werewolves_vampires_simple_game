main	: Avatar.o Being.o Creature.o Vampire.o Werewolf.o Map.o Game.o main.o
	g++ --std=c++11 Avatar.o Being.o Creature.o Vampire.o Werewolf.o Map.o Game.o main.o -o main

Avatar.o	: Avatar.cpp Avatar.h
	g++ --std=c++11 -c Avatar.cpp

Being.o	: Being.cpp Being.h
	g++ --std=c++11 -c Being.cpp

Creature.o	: Creature.cpp Creature.h
	g++ --std=c++11 -c Creature.cpp

Vampire.o	: Vampire.cpp Vampire.h
	g++ --std=c++11 -c Vampire.cpp

Werewolf.o	: Werewolf.cpp Werewolf.h
	g++ --std=c++11 -c Werewolf.cpp

Map.o	: Map.cpp Map.h
	g++ --std=c++11 -c Map.cpp

Game.o	: Game.cpp Game.h
	g++ --std=c++11 -c Game.cpp

main.o	: main.cpp
	g++ --std=c++11 -c main.cpp

clean:
	rm -f main *.o


