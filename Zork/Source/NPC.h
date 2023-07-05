#pragma once
#pragma once

#include "Creature.h"

class NPC : public Creature
{
public:

	NPC(EntityType type, const char* name, const char* description, Room* loc, bool hostile);
	~NPC();

	//TODO: Need update to comprovate if player is room Attack him
	void Update();

	void Go(std::string& dir) override;
	void Attack(std::string& target) override;

public:

	bool hostile;
};