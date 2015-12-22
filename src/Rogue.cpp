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

//void Rogue::move(int xpos, int ypos) {
//	switch (ConsoleUtils::waitForKeypress())
//	{
//		// Move up
//	case 'w':
//		// Look ahead to see if we can enter this location
//		DeltaX = 0;
//		DeltaY = -1;
//		break;
//		// Move left
//	case 'a':
//		// Look ahead to see if we can enter this location
//		DeltaX = -1;
//		DeltaY = 0;
//		break;
//		// Move right
//	case 'd':
//		// Look ahead to see if we can enter this location
//		DeltaX = 1;
//		DeltaY = 0;
//		break;
//		// Move down
//	case 's':
//		// Look ahead to see if we can enter this location
//		DeltaX = 0;
//		DeltaY = 1;
//		break;
//	case 'o':
//		OpenDoorCommand();
//		break;
//	case 'c':
//		CloseDoorCommand();
//		break;
//	case 'g':
//		GetCommand();
//		break;
//	case 'f':
//		DropCommand();
//		break;
//		// Quit
//	case 'q':
//		return 0;
//		// Ignore any other key
//	default:
//		break;
//	}
//	if (CollisionDetection(nPlayerX + DeltaX, nPlayerY + DeltaY))
//	{
//		// If allowed, move in the direction specified
//		nPlayerX += DeltaX;
//		nPlayerY += DeltaY;
//
//	}
//}


void receiveAttack(const int damage) {

}