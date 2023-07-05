#include <iostream>
#include <math.h>
#include "Player.h"
#include "Utils.h"
#include "Entity.h"
#include "Item.h"
#include "Exit.h"
#include "Room.h"


Player::Player(EntityType _type, const char* _name, const char* _description, Room* _loc) :
	Creature(_type, _name, _description, _loc)
{
	fish = nullptr;
}

Player::~Player()
{
}

void Player::Look() const
{
	parent->Look();
}

void Player::GetStats() const
{
	std::cout << "Your stats are:\n" 
		<< "- Level: " << level << '\n'
		<< "- Strength: " << strength << '\n' 
		<< "- Health: " << health << '\n';

	std::vector<Entity*> items;
	GetChildrenByType(items, EntityType::Item);

	for (std::vector<Entity*>::const_iterator it = items.cbegin(); it != items.cend(); ++it)
	{
		Item* temp = (Item*)*it;
		if (temp->itemType == ItemType::Weapon)
		{
			if (weapon != nullptr)
				std::cout << "- Weapon: " << temp->name << " +str " << temp->value << '\n';
		}
		else if (temp->itemType == ItemType::Armor)
		{
			if (armor != nullptr)
				std::cout << "- Armor: " << temp->name << " +hp " << temp->value << '\n';
		}
	}
}

void Player::GetInventory() const
{
	std::vector<Entity*> items;
	GetChildrenByType(items, EntityType::Item);

	if (!items.empty())
	{
		std::cout << "You are carrying:\n";
		for (std::vector<Entity*>::const_iterator it = items.cbegin(); it != items.cend(); ++it)
		{
			Item* temp = (Item*) *it;

			if (temp->itemType == ItemType::Weapon)
			{
				if (weapon != nullptr && weapon == temp)
					std::cout << "- " << temp->name << " (Equiped)";

				else
					std::cout << "- " << temp->name << " (UnEquiped)";
			}
			else if (temp->itemType == ItemType::Armor)
			{
				if (armor != nullptr && armor == temp)
					std::cout << "- " << temp->name << " (Equiped)";

				else
					std::cout << "- " << temp->name << " (UnEquiped)";;
			}
			else if(temp->itemType == ItemType::Container)
			{
				std::cout << "- " << temp->name << ':' << '\n';
				std::vector<Entity*> container;
				temp->GetChildrenByType(container, EntityType::Item);
				if (!container.empty())
					for (std::vector<Entity*>::const_iterator in = container.cbegin(); in != container.cend(); ++in)
						std::cout << '\t' << "- " << (*in)->name;	
				else
					std::cout << '\t' << "Empty.";

				std::cout << '\n';
			}
			else
				std::cout << "- " << (*it)->name;
			
			std::cout << '\n';
		}
	}
	else
		std::cout << "You are empty handed.\n";
}

void Player::Fish()
{
	Item* rod = nullptr;
	for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
		if (Equals((*it)->name, "FishRod"))
			rod = (Item*)(*it);

	if (rod != nullptr)
	{
		if (fish == nullptr && weapon == rod)
		{
			fish = new Item(EntityType::Item, "Seabass", "Large fish, can be used as a wepon?", this, ItemType::Weapon);
			std::cout << "I caught a Seabass! No, wait...it's at least a C++\n";
		}
		else
			std::cout << "FishRod has not been equiped\n";
	}
	else
		std::cout << "FishRod has not been found\n";
}

void Player::Pet() const
{

}

void Player::Go(std::string& dir)
{
	if (parent != nullptr)
	{
		std::vector<Entity*> ext;
		parent->GetChildrenByType(ext, EntityType::Exit);

		std::vector<Entity*> items;
		GetChildrenByType(items, EntityType::Item);

		Item* unlockItem = nullptr;

		bool correctExit = false;

		for (std::vector<Entity*>::const_iterator it = ext.cbegin(); it != ext.cend(); ++it)
		{
			Exit* exit = (Exit*)(*it);
			if (Equals(dir, exit->destination->name) || Equals(dir, exit->dir))
			{
				if (exit->unlock != nullptr)
				{
					for (std::vector<Entity*>::const_iterator i = items.cbegin(); i != items.cend(); ++i)
						if (Equals((*i)->name, exit->unlock->name))
							unlockItem = (Item*)(*i);
				}

				if (exit->lock == true)
				{
					std::cout << "Exit is locked and item is not found.\n";
					correctExit = true;
					break;
				}
				else if (exit->lock == true && exit->unlock == unlockItem)
				{
					std::cout << "Exit is locked, " << unlockItem->name << " has been fount try to unlock " << exit->name << " first.\n";
				}
				else
				{
					Room* temp = (Room*)parent;

					parent->ChangeParent(exit->destination);
					exit->parent->ChangeParent(exit->destination);

					exit->destination = temp;			//Change exit destination to the previous room
					exit->ChangeDir(dir);

					std::cout << "Going through a " << exit->name << " from: " << exit->destination->name << exit->description << exit->parent->name << '\n';

					Look();
					correctExit = true;
					break;
				}
			}
		}

		if (correctExit == false)
			std::cout << "Wrong direction, where are you looking at?\n";
	}
}

void Player::Examine(std::string& str)
{
}

void Player::Take(std::string& item)
{
}

void Player::Drop(std::string& item)
{
}

void Player::Equip(std::string& item)
{
}

void Player::UnEquip(std::string& item)
{
}

void Player::UnLock(std::string& exit)
{
}

void Player::Attack(std::string& target)
{
}
