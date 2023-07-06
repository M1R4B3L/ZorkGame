#include "Creature.h"
#include <cmath>

Creature::Creature(EntityType _type, const char* _name, const char* _description, Room* _location, int _level) :
	Entity(_type, _name, _description, (Entity*) _location), level(_level)
{
	strength = 2;
	health = 10;

	weapon = nullptr;
	armor = nullptr;
	target = nullptr;
}

Creature::~Creature()
{
}

void Creature::Update(int dt, std::vector<std::string>& actions)
{
}

void Creature::Go(std::string& dir)
{
}

void Creature::GetKnockOut(int damage, std::vector<std::string>& actions)
{
}

void Creature::KnockOut(std::string& target, std::vector<std::string>& actions)
{
}

bool Creature::isUnconscious() const
{
	return health <= 0;
}
