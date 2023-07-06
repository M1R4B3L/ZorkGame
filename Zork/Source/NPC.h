#pragma once
#pragma once

#include "Creature.h"

class NPC : public Creature
{
public:

	NPC(EntityType type, const char* name, const char* description, Room* loc, bool hostile);
	~NPC();

	//TODO: Need update to comprovate if player is room Attack him
	void Update(int dt, std::vector<std::string>& actions) override;

	void GetStats() const;
	void GetInventory() const;
	void Go(std::string& dir) override;

	void GetKnockOut(int damage, std::vector<std::string>& actions) override;
	void KnockOut(std::string& target, std::vector<std::string>& actions) override;

public:

	bool hostile;

private:

	int targetTime = 5;
};