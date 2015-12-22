/******************************************************************************
	File:   GameConstants.hpp
	Author: Lee Maguire
	Date:   Dec 2015
	Ver:    1.0
	Notes:	Class to contain globally scoped game constants through a class
			scope, hence keeping them all in the same place and with a
			consistent usage
******************************************************************************/

#ifndef _GAMECONSTANTS_
#define _GAMECONSTANTS_

// Tile Types
#define TILE_ROCKFLOOR	0
#define TILE_WALL		1
#define TILE_CLOSEDDOOR	2
#define TILE_OPENDOOR	3
#define TILE_GRASS		4
#define TILE_TREE		5
#define TILE_WATER		6

// Maximum number of items that the player can hold
#define INVENTORY_SLOTS		10

// Maximum number of actors the game can support at the same time
#define MAX_ACTORS			10

// Item Types
#define ITEM_NONE           0
#define ITEM_POTION         1
#define ITEM_ROCK           2

struct TILE_TYPE
{
	char    nCharacter; // ASCII character for this tile type
	short   nColorCode; // Color code for this tile type
	bool    bPassable;  // Set to true if you can walk on this tile
};

struct ITEM_TYPE
{
	char    nCharacter; // ASCII character code
	short   nColorCode; // Display color for this item type
	char *  p_szName;   // Name of the item type
};

const TILE_TYPE sTileIndex[] = {
	{ '.', 7,  true },   // (0) TILE_ROCKFLOOR
	{ '#', 7,  false },  // (1) TILE_WALL
	{ '+', 6,  false },  // (2) TILE_CLOSEDDOOR
	{ '/', 6,  true },   // (3) TILE_OPENDOOR
	{ '.', 10, true },   // (4) TILE_GRASS
	{ 'T', 10, false },  // (5) TILE_TREE
	{ '~', 9, false }    // (6) TILE_WATER
};

// Global array used to define all item types used in the game
const ITEM_TYPE sItemIndex[] = {
	{ ' ', ConsoleUtils::WHITE, "EMPTY" },  // (0) ITEM_NONE (Unused inventory slot)
	{ (char)173, ConsoleUtils::CYAN, "Potion" }, // (1) ITEM_POTION
	{ '*', ConsoleUtils::WHITE, "Rock" },   // (2) ITEM_ROCK 
};

class GameConstants final
{
public:
	const static int MAP_WIDTH = 20;
	const static int MAP_HEIGHT = 15;

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
