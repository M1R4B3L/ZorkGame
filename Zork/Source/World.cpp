#include <iostream>
#include <conio.h>
#include "World.h"
#include "Timer.h"
#include "Utils.h"
#include "Entity.h"
#include "Creature.h"
#include "Player.h"
#include "NPC.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"

World::World()
{
	timer = new Timer;

	//ROOMS
	Room* bridge = new Room(EntityType::Room, "Bridge", "");
	Room* riverbank = new Room(EntityType::Room, "Riverbank", "");
	Room* ricefields = new Room(EntityType::Room, "RiceFields", "");
	Room* street = new Room(EntityType::Room, "Streets", "");
	Room* parking = new Room(EntityType::Room, "Parking", "");
	Room* kombini = new Room(EntityType::Room, "Kombini", "");

	entities.push_back(bridge);
	entities.push_back(riverbank);
	entities.push_back(ricefields);
	entities.push_back(street);
	entities.push_back(parking);
	entities.push_back(kombini);

	//Items (Looteable)
	Item* truck = new Item(EntityType::Item, "Truck", "", bridge, ItemType::Container);
	{
		Item* ring = new Item(EntityType::Item, "Ring", "Diamond Ring, What is this for?", truck, ItemType::Other);
		Item* invoice = new Item(EntityType::Item, "Invoice", "Invoice, paper", truck, ItemType::Other);

		entities.push_back(truck);
		entities.push_back(ring);
		entities.push_back(invoice);
	}

	Item* backpack = new Item(EntityType::Item, "BackPack", "", riverbank, ItemType::Other);
	Item* rod = new Item(EntityType::Item, "FishRod", "", riverbank, ItemType::Weapon);

	Item* key = new Item(EntityType::Item, "bkey", "opens the backdoor of the kombini store", backpack, ItemType::Other);

	entities.push_back(backpack);
	entities.push_back(rod);
	entities.push_back(key);

	//EXITS
	Exit* riceStreet = new Exit(EntityType::Exit, "path", " -> ", "East", ricefields, street);
	Exit* streetBridge = new Exit(EntityType::Exit, "highway", " -> ", "South", street, bridge);
	Exit* streetParking = new Exit(EntityType::Exit, "barrier", " -> ", "East", street, parking);
	Exit* parkingRiver = new Exit(EntityType::Exit, "stairs", " -> ", "South", parking, riverbank);
	Exit* parkingKombini = new Exit(EntityType::Exit, "backdoor", " -> ", "Door", parking, kombini, true, key);

	entities.push_back(riceStreet);
	entities.push_back(streetBridge);
	entities.push_back(streetParking);
	entities.push_back(parkingRiver);
	entities.push_back(parkingKombini);


	player = new Player(EntityType::Player, "Pam", "", ricefields);
	entities.push_back(player);
	player->weapon = nullptr;
	player->armor = nullptr;
	rod->ChangeParent(player);
	backpack->ChangeParent(player);

	NPC* dog = new NPC(EntityType::NPC, "Max", "pet of the couple", street, false);
	entities.push_back(dog);
}

World::~World()
{
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

bool World::Play(std::vector<std::string>& actions)
{
    bool ret = true;

    if (!actions.empty())
        ret = ExecuteActions(actions);

	if(ret == false)
		std::cout << "Invalid action used!\n";

    Loop();

    return ret;
}

void World::Loop()
{

	timer->Tick();
	if (timer->DeltaTime() > timer->GetTimeScale()/2.0f)	//Update each half a sec
	{
		for (std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->Update();
		}

		//std::cout << timer->DeltaTime() << '\n';
		timer->Reset();
	}
}

bool World::ExecuteActions(std::vector<std::string>& actions)
{
    bool ret = true;
	
	if (actions.size() == 1)
	{
		//Look around current location
		if (Equals(actions[0], "look"))
		{
			player->Look();
		}
		else if (Equals(actions[0], "stats"))
		{
			player->GetStats();
		}
		else if (Equals(actions[0], "inventory"))
		{
			player->GetInventory();
		}
		else if (Equals(actions[0], "fish"))
		{
			player->Fish();
		}
		else if (Equals(actions[0], "pet"))
		{
			player->Pet();
		}
		else
			ret = false;
	}
	else if (actions.size() == 2)
	{
		if (Equals(actions[0], "go"))
		{
			player->Go(actions[1]);
		}
		else if(Equals(actions[0], "examine") || Equals(actions[0], "inspect"))
		{
			player->Examine(actions[1]);
		}
		else if(Equals(actions[0], "take") || Equals(actions[0], "grab"))
		{
			player->Take(actions[1]);
		}
		else if(Equals(actions[0], "drop"))
		{
			player->Drop(actions[1]);
		}
		else if(Equals(actions[0], "equip"))
		{
			player->Equip(actions[1]);
		}
		else if (Equals(actions[0], "unequip"))
		{
			player->UnEquip(actions[1]);
		}
		else if (Equals(actions[0], "unlock"))
		{
			player->UnLock(actions[1]);
		}
		else if (Equals(actions[0], "attack"))
		{
			player->Attack(actions[1]);
		}
		else
			ret = false;
	}
    else
    {
        ret = false;
    }

    return ret;
}

bool World::HandleInput(std::string& playerInput, std::vector<std::string>& args)
{

	if (_kbhit() != 0)
	{
		//Get key value
		char key = _getch();

		if (key == '\b') //Backspace, erase last key pressed
		{
			if (!playerInput.empty())
			{
				playerInput.pop_back();
				std::cout << '\b' << ' ' << '\b';
			}
		}
		else if (key == '\x1b')
		{
			if (args.empty())
			{
				std::cout << "quit";
				args.push_back("quit");
			}
			else
			{
				args.clear();
				playerInput = "";
			}
		}
		else if (key != '\r')
		{
			playerInput += key;
			std::cout << key;
		}
		else
		{
			std::string temp;
			for (char c : playerInput)
			{
				if (c == ' ')
				{
					if (!temp.empty())
					{
						args.push_back(temp);
						temp.clear();
					}
				}
				else
					temp.push_back(c);
			}

			if (!temp.empty()) {
				args.push_back(temp);
				std::cout << '\n';
			}
		}
	}

	return true;
}
