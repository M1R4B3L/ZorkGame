#pragma once

#include <string>
#include <vector>
#include <list>
#include "Timer.h"

class Entity;
class Player;

class World
{
public:

	World();
	~World();

	void Play(std::vector<std::string>& actions);
	void Loop(std::vector<std::string>& actions);
	void ExecuteActions(std::vector<std::string>& actions);
	//INPUT
	bool HandleInput(std::string& inputs, std::vector<std::string>& arg);


public:

	Timer* timer;
	std::string inputs;

	//World Options
	std::string worldName;
	std::list<Entity*> entities;
	Player* player;
};
