#include "NPC.h"

NPC::NPC(EntityType _type, const char* _name, const char* _description, Room* _loc, bool _hostile) :
	Creature(_type, _name, _description, _loc), hostile(_hostile)
{
}

NPC::~NPC()
{
}
