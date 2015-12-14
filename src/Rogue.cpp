/******************************************************************************
File:   Rogue.cpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    1.0
******************************************************************************/

#include <iostream>
#include "Rogue.hpp"
#include "GameUtils.hpp"

using namespace std;

void Rogue::move() 
{
	switch (GameUtils::waitForKeypress())
	{
		// Move down
	case 's':
		Rogue::posY++;
		break;
		// Move left
	case 'a':
		Rogue::posX--;
		break;
		// Move right
	case 'd':
		Rogue::posX++;
		break;
		// Move up
	case 'w':
		Rogue::posY--;
		break;
		// Quit
	//case 'q':
		//return 0;
		// Ignore any other key
	default:
		break;
	}
}

void receiveAttack(const int damage) {

}