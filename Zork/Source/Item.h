#pragma once

#include "Entity.h"

enum class ItemType
{
	Weapon,
	Armor,
	Consumable,
	Container,		//Player can't take, pick up or grab (Unless I say so)
	Other
};

class Item : public Entity
{
public:

	Item(EntityType type, const char* name, const char* description, Entity* parent, ItemType iType = ItemType::Other);
	~Item();

public:

	int value;	//Damage, armor, uses...
	ItemType itemType;
};

