/******************************************************************************
File:   Enemy.hpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    0.1
******************************************************************************/

#ifndef _ENEMY_
#define _ENEMY_

#include <string>
#include "ConsoleUtils.hpp"

class Enemy
{
public:
	// Default constructor
	Enemy(void) { ; }

	// Class destructor
	~Enemy(void) { ; }

	// Changes how the actor appears in the game world
	void SetAppearance(char nDisplayChar, short nDisplayColor);

	// Changes the position of the actor
	void SetPos(int x, int y);

	// Draws the actor to the screen
	void Draw(void);

	// Periodic update routine for the actor
	void    Update(void);

protected:

	// Horizontal coordinate of the actor, relative to the level's origin
	int     nPosX;

	// Vertical coordinate of the actor, relative to the level's origin.
	int     nPosY;

	// ASCII character code used to draw the actor to the screen
	char    nDisplayChar;

	// Color code for this actor
	short   nColorCode;
};

#endif // _ENEMY_