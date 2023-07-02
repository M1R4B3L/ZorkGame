#pragma once

#include <list>
#include <string>

class Entity;

class World
{
public:

	World();
	~World();

public:

	//Handle Game Ticks

	//World Options
	std::string worldName;
	std::list<Entity*> entities;
};
