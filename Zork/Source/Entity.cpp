#include <iostream>
#include "Entity.h"


Entity::Entity(EntityType _type, const char* _name, const char* _description, Entity* _parent) :
	entityType(_type), name(_name), description(_description), parent(_parent)
{
	if (parent != nullptr)
		parent->children.push_back(this);
}

Entity::~Entity()
{
}

void Entity::Update(int dt, std::vector<std::string>& actions)
{
}

void Entity::Look() const
{
	if (entityType == EntityType::Room)
	{
		std::cout << name << " -> ";
		std::cout << description << '\n';

		for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
		{
			if (((*it)->entityType == EntityType::Item) || ((*it)->entityType == EntityType::NPC))
			{
				std::cout << (*it)->name << ": ";
				std::cout << (*it)->description << '\n';
			}
			
		}
	}
	else
	{
		std::cout << name << " -> ";
		std::cout << description << '\n';
	}
}

void Entity::GetChildrenByType(std::vector<Entity*>& entities, EntityType type) const
{
	for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
	{
		if ((*it)->entityType == type)
			entities.push_back((*it));
	}
}

void Entity::RemoveChild(Entity* entity)
{
	children.remove(entity);
}

void Entity::AddChild(Entity* entity)
{
	children.push_back(entity);
}

void Entity::ChangeParent(Entity* entity)
{
	if(parent != nullptr)
		parent->RemoveChild(this);

	parent = entity;
	
	if (parent != nullptr)
		parent->AddChild(this);
}
