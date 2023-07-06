#include <iostream>
#include <math.h>
#include "Player.h"
#include "Utils.h"
#include "Entity.h"
#include "Item.h"
#include "Exit.h"
#include "Room.h"
#include "NPC.h"


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
				std::cout << "- Weapon: " << temp->name << '\n';
		}
		else if (temp->itemType == ItemType::Armor)
		{
			if (armor != nullptr)
				std::cout << "- Armor: " << temp->name << '\n';
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
			if (Equals(parent->name, "riverbank"))
			{
				fish = new Item(EntityType::Item, "Seabass", "Large fish, can be used as a wepon?\nStats: Strength +10", this, ItemType::Weapon);
				fish->value = 10;
				std::cout << "I caught a Seabass! No, wait...it's at least a C++\n";
			}
			else
				std::cout << "!You are trying to fish in the asphalt, find a water surface.\n";
		}
		else if (fish != nullptr && weapon == rod)
		{
			if (Equals(parent->name, "riverbank"))
				std::cout << "Not even a nibble.\n";
			else
				std::cout << "!You are trying to fish in the asphalt, find a water surface.\n";
		}
		else
			std::cout << "FishRod is not equiped\n";
	}
	else
		std::cout << "Try finding a Fishrod first!\n";


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

					this->ChangeParent(exit->destination);
					exit->ChangeParent(exit->destination);

					exit->destination = temp;			//Change exit destination to the previous room
					exit->ChangeDir(dir);

					std::cout << "Using " << dir << " exit: " << exit->description << '\n';
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
	Entity* examine = nullptr;
	for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
	{
		if (Equals(str, (*it)->name) || ((*it)->entityType == EntityType::Exit && Equals(str, ((Exit*)(*it))->destination->name)))
		{
			examine = (*it);
			break;
		}
	}

	if (examine == nullptr)
	{
		for (std::list<Entity*>::const_iterator i = children.cbegin(); i != children.cend(); ++i)
		{
			if (Equals(str, (*i)->name))
			{
				examine = (*i);
				break;
			}
		}
	}

	if (examine != nullptr)
	{
		if (examine->entityType == EntityType::Exit)
			((Exit*)examine)->destination->Look();
		else if (examine->entityType == EntityType::NPC)
		{
			((NPC*)examine)->Look();
			((NPC*)examine)->GetStats();
			((NPC*)examine)->GetInventory();
		}
		else if (examine->entityType == EntityType::Item && ((Item*)examine)->itemType == ItemType::Container)
		{
			for (std::list<Entity*>::const_iterator i = examine->children.cbegin(); i != examine->children.cend(); ++i)
			{
				(*i)->Look();
			}
		}
		else
			examine->Look();
	}
	else if (Equals(str, parent->name))
	{
		parent->Look();
	}
	else
		std::cout << "Examine is not possible.\n";
}

void Player::Take(std::string& item)
{
	Entity* take = nullptr;
	for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
		if (Equals((*it)->name, item))
			take = (*it);

	std::vector<Entity*> roomNpc;
	parent->GetChildrenByType(roomNpc, EntityType::NPC);

	std::vector<Entity*> roomItems;
	parent->GetChildrenByType(roomItems, EntityType::Item);

	if (take == nullptr)
	{
		if (!roomNpc.empty())
		{
			for (std::vector<Entity*>::const_iterator npcs = roomNpc.cbegin(); npcs != roomNpc.cend(); ++npcs)
			{
				for (std::list<Entity*>::const_iterator i = (*npcs)->children.cbegin(); i != (*npcs)->children.cend(); ++i)
					if (Equals((*i)->name, item))
						take = (*i);
			}
		}

		//Items inside other items
		if (!roomItems.empty())
		{
			for (std::vector<Entity*>::const_iterator items = roomItems.cbegin(); items != roomItems.cend(); ++items)
			{
				if (((Item*)(*items))->itemType == ItemType::Container)
				{
					for (std::list<Entity*>::const_iterator j = (*items)->children.cbegin(); j != (*items)->children.cend(); ++j)
						if (Equals((*j)->name, item))
							take = (*j);
				}
			}
		}
	}

	if (take != nullptr && take->entityType == EntityType::Item)
	{
		if (!(((Item*)take)->itemType == ItemType::Container))
		{
			std::cout << "You have taken " << take->name << " from " << take->parent->name << '\n';
			take->ChangeParent(this);
		}
	}
	else
		std::cout << "Cloud not find an item with that name.\n";
}

void Player::Drop(std::string& item)
{
	Entity* drop = nullptr;
	for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
		if (Equals((*it)->name, item))
			drop = (*it);

	std::vector<Entity*> Npc;
	parent->GetChildrenByType(Npc, EntityType::NPC);

	if (drop == nullptr)
	{
		for (std::vector<Entity*>::const_iterator npcs = Npc.cbegin(); npcs != Npc.cend(); ++npcs)
		{
			for (std::list<Entity*>::const_iterator items = (*npcs)->children.cbegin(); items != (*npcs)->children.cend(); ++items)
				if (Equals((*items)->name, item))
					drop = (*items);
		}
	}

	if (drop != nullptr && drop->entityType == EntityType::Item)
	{	
		std::cout << "You have dropped " << drop->name << " from " << drop->parent->name << '\n';
		drop->ChangeParent(parent);	
	}
	else
		std::cout << "Cloud not find an item with that name.\n";
}

void Player::Equip(std::string& item)
{
	Item* equiped = nullptr;
	for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
		if (Equals((*it)->name, item))
			equiped = (Item*)(*it);

	if (equiped != nullptr)
	{
		if (equiped->itemType == ItemType::Weapon) //Nothing Equiped
		{
			if (weapon != nullptr)
			{
				if(Equals(weapon->name, equiped->name))
					std::cout << equiped->name << " already equiped.\n";
				else
				{
					UnEquip(weapon->name);
					weapon = equiped;
					strength += equiped->value;
					std::cout << equiped->name << " has been equiped in weapon slot.\n";
				}
			}
			else
			{
				weapon = equiped;
				strength += equiped->value;
				std::cout << equiped->name << " has been equiped in weapon slot.\n";
			}
		}
		else if (armor == nullptr && equiped->itemType == ItemType::Armor) //Nothing Equiped
		{
			if (armor != nullptr)
			{
				if (Equals(armor->name, equiped->name))
					std::cout << equiped->name << " already equiped.\n";
				else
				{
					UnEquip(armor->name);
					armor = equiped;
					strength += equiped->value;
					std::cout << equiped->name << " has been equiped in armor slot.\n";
				}
			}
			else
			{
				armor = equiped;
				health += equiped->value;
				std::cout << equiped->name << " has been equiped in armor slot.\n";
			}
		}
		else
		{
			std::cout << equiped->name << " cannot be equiped.\n";
		}
	}
	else
		std::cout << "You don't that item in your inventory\n.";
}

void Player::UnEquip(std::string& item)
{
	if (weapon != nullptr)
	{
		if (Equals(item, weapon->name))
		{
			strength -= weapon->value;
			std::cout << weapon->name << "has been unequiped.\n";
			weapon = nullptr;
		}
		else
			std::cout << "That item is not equiped in weapon\n";
	}
	else if (armor != nullptr)
	{
		if (Equals(item, armor->name))
		{
			health -= armor->value;
			std::cout << armor->name << "has been unequiped.\n";
			armor = nullptr;
		}
		else
			std::cout << "That item is not equiped in armor slot\n";
	}
	else
		std::cout << "You have no items in weapon or armor slots\n";
}

void Player::UnLock(std::string& exit)
{
	Exit* ext = nullptr;
	for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
		if (Equals((*it)->name, exit))
			ext = (Exit*)(*it);

	if (ext == nullptr)
		std::cout << "No exit in that direction\n";

	if (ext->lock == false)
		std::cout << "Door already unlocked\n";

	Item* item = nullptr;
	for (std::list<Entity*>::const_iterator it = children.cbegin(); it != children.cend(); ++it)
		if (Equals((*it)->name, ext->unlock->name))
			item = (Item*)(*it);

	if (item != nullptr)
	{
		std::cout << item->name << " used to unlock the" << ext->name << '\n';
		ext->lock = false;
	}
	else
		std::cout << "Correct item not found in your inventory\n";
	

}

void Player::GetKnockOut(int damage, std::vector<std::string>& actions)
{

	std::cout << " Damage: " << damage << ".\n";
	health -= damage;

	if (isUnconscious())
	{
		std::cout << "You failed, your Kombini has been destroyed burglar escaped.\n";
		std::cout << "quit";	//Close game
		actions.push_back("quit");
	}
	else
		std::cout << "Wow! You survived the impact " << name << "->Health: " << health << ".\n";

}

void Player::KnockOut(std::string& str, std::vector<std::string>& actions)
{
	NPC* trgt = nullptr;
	for (std::list<Entity*>::const_iterator it = parent->children.cbegin(); it != parent->children.cend(); ++it)
		if (Equals((*it)->name, str))
			trgt = (NPC*)(*it);

	if (trgt != nullptr)
	{
		target = trgt;
		std::cout << name << " attack to " << target->name << " succeded ->";
		if (weapon != nullptr)
			trgt->GetKnockOut(weapon->value, actions);
		else
			trgt->GetKnockOut(strength, actions);
	}
	else
		std::cout << "In " << parent->name << " there is no one called" << str <<  ".\n";

}

void Player::EndGame(std::vector<std::string>& actions)
{
	actions.push_back("quit");
}

