/******************************************************************************
File:   Enemy.cpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    1.0
******************************************************************************/

#include <iostream>
#include "Enemy.hpp"
#include "GameConstants.hpp"


using namespace std;

void Enemy::SetAppearance(char nDisplayChar, short nDisplayColor)
{
	this->nDisplayChar = nDisplayChar;
	this->nColorCode = nDisplayColor;
}
void Enemy::SetPos(int x, int y)
{
	// Don't change anything if the new coordinates are invalid
	if ((x < 0) || (x >= GameConstants::MAP_WIDTH) ||
		(y< 0) || (y >= GameConstants::MAP_HEIGHT))
		return;

	// Move the actor to the coordinates specified
	this->nPosX = x;
	this->nPosY = y;
}
void Enemy::Draw(void)
{
	// Skip drawing if the actor's coordinates aren't on the map
	if ((this->nPosX < 0) || (this->nPosX >= GameConstants::MAP_WIDTH) ||
		(this->nPosY < 0) || (this->nPosY >= GameConstants::MAP_HEIGHT))
		return;
	// Draw the actor as it wants to be drawn
	ConsoleUtils::setFGColour(this->nColorCode);
	ConsoleUtils::moveCursor(this->nPosX, this->nPosY);
	cout << this->nDisplayChar;
}

void Enemy::Update(void)
{
	// Generate a new set of deltas for this actor
	int iDeltaX = (rand() % 3) - 1;
	int iDeltaY = (rand() % 3) - 1;
	// See if this new position is allowed
	//if (CollisionDetection(this->nPosX + iDeltaX, this->nPosY + iDeltaY))
	//{
		this->nPosX += iDeltaX;
		this->nPosY += iDeltaY;
	//}
}
