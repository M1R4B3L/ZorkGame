#pragma once

#include "Creature.h"

class Player : Creature
{
public:

	Player(EntityType type, const char* name, const char* description, Room* loc);
	~Player();

	//void RecalculateExp(int x);
	int CalculateExpCap();

public:

	int experienceCap;
	int experience;
};