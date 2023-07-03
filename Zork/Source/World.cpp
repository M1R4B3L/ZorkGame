#include <iostream>
#include <conio.h>
#include "World.h"
#include "Timer.h"
#include "Entity.h"

World::World()
{
	timer = new Timer;
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

   
    if (_strcmpi(actions[0].c_str(), "look") == 0)
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
			}
			std::cout << '\n';
		}
	}

	return true;
}
