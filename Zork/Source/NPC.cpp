#include <iostream>
#include "NPC.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Utils.h"


NPC::NPC(EntityType _type, const char* _name, const char* _description, Room* _loc, bool _hostile) :
	Creature(_type, _name, _description, _loc), hostile(_hostile)
{
}

NPC::~NPC()
{
}

void NPC::Update(int dt, std::vector<std::string>& actions)
{
	if (hostile == true)
	{
		for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
			if ((*it)->entityType == EntityType::Player)
				target = (Creature*)(*it);

		if (target != nullptr)
		{
			if (!isUnconscious() && !(target->isUnconscious()))
			{
				KnockOut(target->name, actions);
				std::cout << ">";
			}
		}
	}

}

void NPC::GetStats() const
{
	std::cout << name << " stats are:\n"
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
				std::cout << "- Weapon: " << temp->name << '\n';
		}
		else if (temp->itemType == ItemType::Armor)
		{
			if (armor != nullptr)
				std::cout << "- Armor: " << temp->name << '\n';
		}
	}
}

void NPC::GetInventory() const
{
	std::vector<Entity*> items;
	GetChildrenByType(items, EntityType::Item);

	if (!items.empty())
	{
		std::cout << name << " is carrying:\n";
		for (std::vector<Entity*>::const_iterator it = items.cbegin(); it != items.cend(); ++it)
		{
			Item* temp = (Item*)*it;

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
			else if (temp->itemType == ItemType::Container)
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
		std::cout << name << "is empty handed.\n";
}

void NPC::Go(std::string& dir)
{
}


void NPC::GetKnockOut(int damage, std::vector<std::string>& actions)
{
	std::cout << " Damage: " << damage << ".\n";

	health -= damage;

	hostile = true;

	if (isUnconscious())
	{
		std::cout << "Congratulations for saving your Kombini from the burglars.\n";
		std::cout << "quit";	//Close game
		actions.push_back("quit");
	}
	else
		std::cout << "Your strenght is not enought to defeat " << name << " -> Health: " << health<< ".\n";
}

void NPC::KnockOut(std::string& str, std::vector<std::string>& actions)
{
	if (hostile == true)
	{
		if (Equals(target->name, str))
		{
			std::cout << name << " attack to "<< target->name << " succeded ->";
			if(weapon != nullptr)
				target->GetKnockOut(weapon->value, actions);
			else
				target->GetKnockOut(strength, actions);

			hostile = false;
		}
		else
			std::cout << "In " << parent->name << " there is no one called " << str << ".\n";
	}
}

