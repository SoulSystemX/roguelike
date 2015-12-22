/******************************************************************************
File:   Player.cpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    1.0
******************************************************************************/

#include <iostream>
#include "Player.hpp"
#include "GameConstants.hpp"

using namespace std;

void Player::move(int xpos, int ypos) {
	
}


void Player::receiveAttack(const int damage) {

}

void Player::Draw(void)
{
	// Skip drawing if the actor's coordinates aren't on the map
	if ((this->posX < 0) || (this->posX >= GameConstants::MAP_WIDTH) ||
		(this->posY < 0) || (this->posY >= GameConstants::MAP_HEIGHT))
		return;
	// Draw the actor as it wants to be drawn
	ConsoleUtils::setFGColour(this->nColorCode);
	ConsoleUtils::moveCursor(this->posX, this->posY);
	cout << this->nDisplayChar;
}

// Changes how the actor appears in the game world
void Player::SetAppearance(char nDisplayChar, short nDisplayColor)
{
	this->nDisplayChar = nDisplayChar;
	this->nColorCode = nDisplayColor;
}