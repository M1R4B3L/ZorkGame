#include <iostream>
#include <conio.h>
#include <vector>
#include "Timer.h"
#include "Utils.h"
#include "World.h"


int main()
{	
	std::vector<std::string> gameActions;

	World newWorld;

	//Mantain CMD Open
	while (1)
	{
		//PLAYER INPUT
		// -----------------------------------------------------------
		//See if player pressed a key
		newWorld.HandleInput(newWorld.inputs, gameActions);

		//GAME LOOP
		// -----------------------------------------------------------
		//TODO: Handle all game actions
		if (!gameActions.empty() && Equals(gameActions[0], "quit"))
			break;
	
		newWorld.Play(gameActions);
			
		//Handle next game action
		if (!gameActions.empty())
		{
			gameActions.clear();
			newWorld.inputs = "";
			std::cout << '>';
		}
	}

	std::cout << "Thanks for playing";

	return 0;
}