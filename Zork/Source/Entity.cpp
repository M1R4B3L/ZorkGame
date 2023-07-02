#include "Entity.h"

Entity::Entity(EntityType _type, const char* _name, const char* _description, Entity* _parent) :
	entityType(_type), name(_name), description(_description), parent(_parent)
{
	if (parent)
		children.push_back(this);
}

Entity::~Entity()
{
}
