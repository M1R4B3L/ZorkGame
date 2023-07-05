#include "Exit.h"
#include "Utils.h"

Exit::Exit(EntityType _type, const char* _name, const char* _description, const char* _dir, Room* _source, Room* _destination, bool _lock, Entity* _unlock) :
	Entity(_type, _name, _description, (Entity*)_source), dir(_dir), destination(_destination), lock(_lock), unlock(_unlock)
{
}

Exit::~Exit()
{
}

void Exit::ChangeDir(std::string& newDir)
{
	if (Equals(newDir, "north"))
		dir = "south";
	else if (Equals(newDir, "south"))
		dir = "north";
	else if (Equals(newDir, "east"))
		dir = "west";
	else if (Equals(newDir, "west"))
		dir = "east";
}
