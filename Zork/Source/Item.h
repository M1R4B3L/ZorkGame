#pragma once

#include "Entity.h"

enum class ItemType
{
	Weapon,
	Armor,
	Potions,
	Other
};

class Item : public Entity
{
public:

	Item(EntityType type, const char* name, const char* description, Entity* parent, ItemType iType);
	~Item();

public:

	ItemType itemType;
};

