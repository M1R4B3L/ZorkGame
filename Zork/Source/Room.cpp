#include <list>
#include "Room.h"


Room::Room(EntityType _type, const char* _name, const char* _description, RoomType _rType) :
	Entity(_type, _name, _description), roomType(_rType)
{
}

Room::~Room()
{
}

