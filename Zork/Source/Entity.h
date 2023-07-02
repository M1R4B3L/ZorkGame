#pragma once

#include <string>
#include <list>

enum class EntityType
{
	Player,
	NPC,
	Exit,
	Room,
	Item,
	Objectives,
	Entity			//Default Key
};

class Entity 
{
public:

	Entity(EntityType type, const char* name, const char* description, Entity* parent = nullptr);
	virtual ~Entity();

public:

	EntityType entityType;
	std::string name;
	std::string description;

	Entity* parent;
	std::list<Entity*> children;
};
