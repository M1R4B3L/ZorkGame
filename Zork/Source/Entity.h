#pragma once

#include <string>
#include <list>
#include <vector>

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

	virtual void Update(int dt, std::vector<std::string>& actions);

	void Look() const;
	void GetChildrenByType(std::vector<Entity*>& entities, EntityType type) const;

	void RemoveChild(Entity* entity);
	void AddChild(Entity* entity);

	void ChangeParent(Entity* entity);

public:

	EntityType entityType;
	std::string name;
	std::string description;

	Entity* parent;
	std::list<Entity*> children;
};
