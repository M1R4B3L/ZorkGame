#include "Item.h"

Item::Item(EntityType _type, const char* _name, const char* _description, Entity* _parent, ItemType _iType) :
	Entity(_type, _name, _description, _parent), itemType(_iType)
{
	if (parent != nullptr)
		parent->children.push_back(this);
}

Item::~Item()
{
}
