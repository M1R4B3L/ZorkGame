#include "Exit.h"


Exit::Exit(EntityType _type, const char* _name, const char* _description, const char* _dir, Room* _source, Room* _destination, bool _lock, Entity* _unlock) :
	Entity(_type, _name, _description, (Entity*)_source), dir(_dir), destination(_destination), lock(_lock), unlock(_unlock)
{
	if (parent != nullptr)
		parent->children.push_back(this);
}

Exit::~Exit()
{
}
