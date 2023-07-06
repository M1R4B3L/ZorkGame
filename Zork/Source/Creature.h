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

	virtual void Update(int dt, std::vector<std::string>& actions);

	virtual void Go(std::string& dir);
	virtual void GetKnockOut(int damage, std::vector<std::string>& actions);
	virtual void KnockOut(std::string& target, std::vector<std::string>& actions);

	bool isUnconscious() const;

public:
	//TODO: RPG CLASS SYSTEM Should i do it??

	int strength;	//% Add to Armor and Damage
	int health;
	int level;
	Item* weapon;
	Item* armor;

	Creature* target;
};

