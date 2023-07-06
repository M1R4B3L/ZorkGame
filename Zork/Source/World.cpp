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
	Room* bridge = new Room(EntityType::Room, "Bridge", "Closed Bridge, at north is the Street");
	Room* riverbank = new Room(EntityType::Room, "Riverbank", "Small land close to the river, at north there's a Parking");
	Room* ricefields = new Room(EntityType::Room, "RiceFields", "Cultivating Ricefields, at east is the Street");
	Room* street = new Room(EntityType::Room, "Street", "Deserted road, west of it are the RiceFields and at east a Parking, \nbetween them, there is a Kombini with the main door blocked by a crashed car. \nMax is there");
	Room* parking = new Room(EntityType::Room, "Parking", "Car parking lot, there are the Backdoor of the Kombini and the Riverbank at south");
	Room* kombini = new Room(EntityType::Room, "Kombini", "Ah!, there is a burglar inside your Kombini defeat him as fast as possible");

	entities.push_back(bridge);
	entities.push_back(riverbank);
	entities.push_back(ricefields);
	entities.push_back(street);
	entities.push_back(parking);
	entities.push_back(kombini);

	//NPC
	NPC* dog = new NPC(EntityType::NPC, "Max", "pet of the couple", street, false);
	NPC* vincent = new NPC(EntityType::NPC, "Vincent", "shady guy, he's unconscious", ricefields, false);
	NPC* will = new NPC(EntityType::NPC, "Will", "burglar, he has a weapon be carefull", kombini, false);
	NPC* lewis = new NPC(EntityType::NPC, "Lewis", "husban, unconscious right now", bridge, false);

	entities.push_back(dog);
	entities.push_back(vincent);
	entities.push_back(will);
	entities.push_back(lewis);

	//ITEMS

	//Bridge
	Item* truck = new Item(EntityType::Item, "Truck", " Stopped truck in the middle of the road", bridge, ItemType::Container);
	Item* ring = new Item(EntityType::Item, "Ring", " Diamond Ring, What is this for?", truck, ItemType::Other);
	Item* invoice = new Item(EntityType::Item, "Invoice", " Invoice, paper", truck, ItemType::Other);

	entities.push_back(truck);
	entities.push_back(ring);
	entities.push_back(invoice);

	//Riverbank
	Item* backpack = new Item(EntityType::Item, "BackPack", "fishing backpack", riverbank, ItemType::Container);
	Item* key = new Item(EntityType::Item, "DoorKey", "opens the backdoor of the kombini store", backpack, ItemType::Other);
	Item* vest = new Item(EntityType::Item, "Vest", "small vest, increases health when equiped: Health +5", backpack, ItemType::Armor);
	vest->value = 5;
	Item* rod = new Item(EntityType::Item, "FishRod", "old rod, it still works: Strength +0", riverbank, ItemType::Weapon);

	entities.push_back(backpack);
	entities.push_back(vest);
	entities.push_back(key);
	entities.push_back(rod);

	//Ricefields
	Item* shovel = new Item(EntityType::Item, "Shovel", "Pam's rusty shovel: Strength +5", vincent, ItemType::Weapon);
	shovel->value = 5;
	Item* letter = new Item(EntityType::Item, "Letter", "bloddy paper: VINCENT!, KILL THE COUPLE AND GET THE RING", vincent, ItemType::Other);
	Item* ckey = new Item(EntityType::Item, "Carkey", "car keys", vincent, ItemType::Other);

	entities.push_back(shovel);
	entities.push_back(letter);
	entities.push_back(ckey);

	//Street
	Item* car = new Item(EntityType::Item, "Car", "crashed car", street, ItemType::Container);
	Item* stick = new Item(EntityType::Item, "Stick", "drooled weapon: Strength +2", dog, ItemType::Weapon);
	stick->value = 2;
	Item* collar = new Item(EntityType::Item, "Collar", "I'm Max, if lost call the local Kombini", dog, ItemType::Other);

	entities.push_back(car);
	entities.push_back(stick);
	entities.push_back(collar);

	//Parking

	//Shop
	Item* crowbar = new Item(EntityType::Item, "Crowbar", "irron weapon: Strength +5", will, ItemType::Weapon);
	crowbar->value = 5;
	Item* cone = new Item(EntityType::Item, "Cone", "traffic cone, it gives armor: Health +2", will, ItemType::Armor);
	cone->value = 2;

	will->weapon = crowbar;
	will->armor = cone;
	will->strength += crowbar->value;
	will->health += cone->value;

	entities.push_back(crowbar);
	entities.push_back(cone);

	//EXITS
	Exit* riceStreet = new Exit(EntityType::Exit, "path", "connects the Ricefields and the Street ", "East", ricefields, street);
	Exit* streetBridge = new Exit(EntityType::Exit, "highway", "connects the Bridge and the Street ", "South", street, bridge);
	Exit* streetParking = new Exit(EntityType::Exit, "barrier", "connects the Parking and the Street ", "East", street, parking);
	Exit* parkingRiver = new Exit(EntityType::Exit, "stairs", "connects the Parking and the Riverbank ", "South", parking, riverbank);
	Exit* parkingKombini = new Exit(EntityType::Exit, "backdoor", "connects the Parking and the Kombini ", "Backdoor", parking, kombini, true, key);

	entities.push_back(riceStreet);
	entities.push_back(streetBridge);
	entities.push_back(streetParking);
	entities.push_back(parkingRiver);
	entities.push_back(parkingKombini);

	player = new Player(EntityType::Player, "Pam", "You, the PLAYER", ricefields);

	entities.push_back(player);

	player->Look();

	std::cout << ">";
}

World::~World()
{
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

void World::Play(std::vector<std::string>& actions)
{

    if (!actions.empty())
        ExecuteActions(actions);

    Loop(actions);
}

void World::Loop(std::vector<std::string>& actions)
{
	timer->Tick();
	if (timer->DeltaTime() > timer->GetTimeScale()/2.0f)	//Update each sec
	{
		for (std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->Update(timer->DeltaTime(), actions);
		}

		//std::cout << timer->DeltaTime() << '\n';
		timer->Reset();
	}
}

void World::ExecuteActions(std::vector<std::string>& actions)
{
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
			std::cout << "That's not a valid action!\n";
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
			player->KnockOut(actions[1], actions);
		}
		else
			std::cout << "I don't recognise that verb " << actions[0] << '\n';
	}
	else if (actions.size() == 3)
	{
		if (Equals(actions[0], "drop"))
		{
			player->Drop(actions[1], actions[2]);
		}
		else
		std::cout << "I don't recognise that verb " << actions[0] << '\n';
	}
    else
    {
		std::cout << "Three are the maximun words neeed!\n";
    }

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
