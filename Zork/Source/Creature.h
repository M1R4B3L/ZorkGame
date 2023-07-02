#pragma once

#include "Entity.h"
#include <vector>

class Room;
class Item;

class Creature : public Entity
{
public:

	Creature(EntityType type, const char* name, const char* description, Room* location, int level = 1);
	virtual ~Creature();


	bool isAlive() const;

public:
	//TODO: RPG CLASS SYSTEM Should i do it??

	int strength;	//% Add to Armor and Damage
	int health;
	int level;
	Item* weapon;
	Item* armor;
	Item* potion;

	Creature* target;
};

