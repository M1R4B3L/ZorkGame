
#include <iostream>
#include <math.h>
#include "Player.h"

Player::Player(EntityType _type, const char* _name, const char* _description, Room* _loc) :
	Creature(_type, _name, _description, _loc)
{
}

Player::~Player()
{
}

void Player::Look(std::vector<std::string>& action) const
{
	parent->Look();
}
