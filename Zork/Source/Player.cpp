
#include <iostream>
#include <math.h>
#include "Player.h"

Player::Player(EntityType _type, const char* _name, const char* _description, Room* _loc) :
	Creature(_type, _name, _description, _loc)
{
	experienceCap = CalculateExpCap();
	experience = 0;
}

Player::~Player()
{
}

int Player::CalculateExpCap()
{
	return (int)std::pow((double)level, 4.0 / 3.0) * 15.0;
}