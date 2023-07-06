#pragma once

#include "Creature.h"
#include "Item.h"

class Player : public Creature
{
public:

	Player(EntityType type, const char* name, const char* description, Room* loc);
	~Player();

	void Look() const;
	void GetStats() const;
	void GetInventory() const;
	void Fish();
	void Pet() const;

	void Go(std::string& dir) override;

	void Examine(std::string& str);
	void Take(std::string& item);
	void Drop(std::string& item);
	void Equip(std::string& item);
	void UnEquip(std::string& item);
	void UnLock(std::string& exit);

	void GetKnockOut(int damage, std::vector<std::string>& actions) override;
	void KnockOut(std::string& target, std::vector<std::string>& actions) override;

	void EndGame(std::vector<std::string>& actions);

public:
	Item* fish;
};