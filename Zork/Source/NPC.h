#pragma once
#pragma once

#include "Creature.h"

class NPC : Creature
{
public:

	NPC(EntityType type, const char* name, const char* description, Room* loc, bool hostile);
	~NPC();

	//TODO: Need update to comprovate if player is room Attack him
	void Update();

public:

	bool hostile;
};