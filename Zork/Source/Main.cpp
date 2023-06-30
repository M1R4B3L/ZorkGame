#include <iostream>
#include <conio.h>
#include <vector>
#include "Globals.h"


int main()
{
	char key;	
	std::string playerInput;			
	std::vector<std::string> gameActions;

	//Mantain CMD Open
	while (1)
	{
		//PLAYER INPUT
		// -----------------------------------------------------------
		//See if player pressed a key
		if (_kbhit() != 0)
		{
			//Get key value
			key = _getch();
		
			if (key == '\b') //Backspace, erase last key pressed
			{
				if (!playerInput.empty())
				{
					playerInput.pop_back();
					std::cout << '\b' << ' ' << '\b';
				}
			}
			else if(key == '\x1b')
			{
				if(!gameActions.empty())
					gameActions.push_back("quit");
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
							gameActions.push_back(temp);
							temp.clear();
						}
					}
					else
						temp.push_back(c);	
				}	

				if (!temp.empty()) {
					gameActions.push_back(temp);
				}
			}
		}

		//GAME LOOP
		// -----------------------------------------------------------
		//Handle if game action is quit
		if (!gameActions.empty() && Equals(gameActions[0], "quit"))
			break;

		//TODO: Handle all game actions
		
		//Handle next game action
		if (!gameActions.empty())
		{
			gameActions.clear();
			playerInput = "";
			std::cout << '-';
		}
	}

	std::cout << "\nThanks for playing";

	return 0;
}