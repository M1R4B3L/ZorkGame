#pragma once

#include "Entity.h"

class Room;

class Exit : public Entity
{
public:

	Exit(EntityType type, const char* name, const char* description, const char* dir, Room* source, Room* destination, bool lock = false, Entity* unlock = nullptr);
	~Exit();

public:

	std::string dir;
	//Room* source -> parent.
	Room* destination;
	bool lock;
	Entity* unlock;			//Obecjtive or Item
};

