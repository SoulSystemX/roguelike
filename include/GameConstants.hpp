/******************************************************************************
	File:   GameConstants.hpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Dec 2015
	Ver:    Tutorial 11B 1.0
	Notes:	Class to contain globally scoped game constants through a class
			scope, hence keeping them all in the same place and with a
			consistent usage
******************************************************************************/

#ifndef _GAMECONSTANTS_
#define _GAMECONSTANTS_

class GameConstants final
{
public:
	const static int MAP_WIDTH = 20;
	const static int MAP_HEIGHT = 15;

	const static int TILE_FLOOR = 0;
	const static int TILE_WALL = 1;

protected:
private:
	// Prevents being able to instantiate an object instance of this class 
	inline GameConstants() { ; }

	// Copy constructor
	GameConstants(const GameConstants& other) = delete;
	// Overloaded assignment operator
	GameConstants& operator=(const GameConstants& other) = delete;

	// Prevents being able to destroy an object instance of this class
	inline virtual ~GameConstants() { ; }
};

#endif // _GAMECONSTANTS_
