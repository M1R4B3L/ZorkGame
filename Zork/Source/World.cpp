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
	Room* fGasStation = new Room(EntityType::Room, "Front Gas Station", "");
	Room* bGasStation = new Room(EntityType::Room, "Back Gas Station", "");
	Room* iGasStation = new Room(EntityType::Room, "Inside Gas Station", "");

	entities.push_back(bridge);
	entities.push_back(riverbank);
	entities.push_back(ricefields);
	entities.push_back(fGasStation);
	entities.push_back(bGasStation);
	entities.push_back(iGasStation);

	//Items (Looteable)
	Item* truck = new Item(EntityType::Item, "Truck", "", bridge, ItemType::Other);
	{
		Item* ring = new Item(EntityType::Item, "Ring", "Diamond Ring, What is this for?", truck, ItemType::Other);
		Item* invoice = new Item(EntityType::Item, "Invoice", "Invoice, paper", truck, ItemType::Other);

		entities.push_back(truck);
		entities.push_back(ring);
		entities.push_back(invoice);
	}
	Item* backpack = new Item(EntityType::Item, "BackPack", "", riverbank, ItemType::Other);

	entities.push_back(backpack);


	player = new Player(EntityType::Player, "Pam", "", ricefields);
	entities.push_back(player);
}

World::~World()
{
}

bool World::Play(std::vector<std::string>& actions)
{
    bool ret = true;

    if (!actions.empty())
        ret = ExecuteActions(actions);

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
			player->Look(actions);
		}
		else if (Equals(actions[0], "stats"))
		{

		}
		else if (Equals(actions[0], "inventory"))
		{
			 
		}
		else if (Equals(actions[0], "fish"))
		{
			
		}
		else if (Equals(actions[0], "pet"))
		{

		}
	}
	else if (actions.size() == 2)
	{

	}
    else
    {
        std::cout << "Invalid action used!\n";
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
