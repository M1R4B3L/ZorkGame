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

void NPC::Update()
{
	//TODO: Make the dog move slower 
	/*std::string dir = "south";

	Go(dir);

	dir = "north";*/
}

void NPC::Go(std::string& dir)
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

void NPC::Attack(std::string& target)
{
}
