#pragma once

#include "Creature.h"

class Player : public Creature
{
public:

	Player(EntityType type, const char* name, const char* description, Room* loc);
	~Player();

	void Look(std::vector<std::string>& str) const override;

public:

};