#pragma once

#include "Entity.h"

class Exit;
class Objective;

enum class RoomType
{
	Forest,
	City,
	Lobby		//Default
};

class Room : public Entity
{

public:

	Room(EntityType type, const char* name, const char* description, RoomType rType = RoomType::Lobby);
	~Room();


public:

	RoomType roomType;
	//Objective
};

