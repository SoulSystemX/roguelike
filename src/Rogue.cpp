/******************************************************************************
File:   Rogue.cpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    1.0
******************************************************************************/

#include <iostream>
#include "Rogue.hpp"
#include "ConsoleUtils.hpp"

using namespace std;

void Rogue::move(int xpos, int ypos) {
	switch (ConsoleUtils::waitForKeypress())
	{
		// Move down
	case 's':
		this->posY++;
		break;
		// Move left
	case 'a':
		this->posX--;
		break;
		// Move right
	case 'd':
		this->posX++;
		break;
		// Move up
	case 'w':
		this->posY--;
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