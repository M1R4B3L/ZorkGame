#include "Creature.h"
#include <cmath>

Creature::Creature(EntityType _type, const char* _name, const char* _description, Room* _location, int _level) :
	Entity(_type, _name, _description, (Entity*) _location), level(_level)
{
	strength = 0;
	health = 0;

	weapon = nullptr;
	armor = nullptr;
	target = nullptr;
}

Creature::~Creature()
{
}

void Creature::Update()
{
}

void Creature::Go(std::string& dir)
{
}

void Creature::Attack(std::string& dir)
{
}

bool Creature::isAlive() const
{
	return health < 0;
}
