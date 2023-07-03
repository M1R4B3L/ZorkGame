#pragma once

#include <string>
#include <vector>
#include <list>
#include "Timer.h"

class Entity;

class World
{
public:

	World();
	~World();

	bool Play(std::vector<std::string>& actions);
	void Loop();
	bool ExecuteActions(std::vector<std::string>& actions);
	//INPUT
	bool HandleInput(std::string& inputs, std::vector<std::string>& arg);


public:

	Timer* timer;
	std::string inputs;

	//World Options
	std::string worldName;
	std::list<Entity*> entities;
};
