#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Classe.h"      
#include "Coord.h"       
#include "Orientation.h"

class Character {

public:
	Classe classe;
	int hp;
	Coord coord;
	Orientation orientation;
	int level;

	Character(Classe classe, int hp, Coord coord, Orientation orientation, int level);

	// Getters
	Classe getClasse();

	// Méthodes
	void takeDamage(int damage);
	void move(int dx, int dy);
	void turnLeft();
	void turnRight();
	void turnUp();
	void turnDown();
	void levelUp();
};

#endif
