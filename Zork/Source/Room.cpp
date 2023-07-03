#include <list>
#include "Room.h"


Room::Room(EntityType _type, const char* _name, const char* _description) :
	Entity(_type, _name, _description)
{
}

Room::~Room()
{
}

