#include <iostream>
#include <iomanip> 
#include <string>

// Include the header files for the classes we are testing
#include "ConsoleUtils.hpp"
#include "Player.hpp"
#include "Rogue.hpp"
#include "GameConstants.hpp"

using namespace std;

// Initialize the player's on-screen location
int nPlayerX = 1, nPlayerY = 1;

int nMapArray[GameConstants::MAP_HEIGHT][GameConstants::MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 5, 5, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 5, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
}; 

// Item map, overlaid on top of the world map
int nItemArray[GameConstants::MAP_HEIGHT][GameConstants::MAP_WIDTH];

void DrawTile(int x, int y)
{

	int nType = nMapArray[y][x];
	//ConsoleUtils::setFGColour(sTileIndex[nType].nColorCode, false);
	//cout << sTileIndex[nType].nCharacter;

	// Designate the position of the tile on screen
	ConsoleUtils::moveCursor(x, y);
	// Is there an item present at this location?
	int nColor;
	char nCharacter;
	if (nItemArray[y][x] != ITEM_NONE)
	{
		int nItemType = nItemArray[y][x];
		nColor = sItemIndex[nType].nColorCode;
		nCharacter = sItemIndex[nType].nCharacter;
	}
	else
	{
		int nTileType = nMapArray[y][x];
		nColor = sTileIndex[nType].nColorCode;
		nCharacter = sTileIndex[nType].nCharacter;
	}
	// Select the tile color
	ConsoleUtils::setFGColour(nColor);
	// Draw the tile to the screen
	cout << nCharacter;
}

void DrawMap(void)
{
	for (int y = 0; y < GameConstants::MAP_HEIGHT; y++)
	{
		ConsoleUtils::moveCursor(0, y);
		for (int x = 0; x < GameConstants::MAP_WIDTH; x++)
		{
			DrawTile(x, y);
		}
	} 
} 

bool CollisionDetection(int nMapX, int nMapY)
{
	// Before we do anything, make darn sure that the coordinates are valid
	if (nMapX < 0 || nMapX >= GameConstants::MAP_WIDTH || nMapY < 0 || nMapY >= GameConstants::MAP_HEIGHT)
		return false;
	// Store the value of the tile specified
	int nTileValue = nMapArray[nMapY][nMapX];
	// Return true if it's passable
	return sTileIndex[nTileValue].bPassable;
}

void OpenDoorCommand(void)
{
	// Draw some notification to the user
	ConsoleUtils::moveCursor(2, 22);
	cout << "Which direction? (w,a,s,d)";
	// Let the user decide where to look
	int nDeltaX = 0;
	int nDeltaY = 0;
	switch (ConsoleUtils::waitForKeypress())
	{
		// SOUTH
	case 's':
		nDeltaX = 0;
		nDeltaY = 1;
		break;
		// WEST
	case 'a':
		nDeltaX = -1;
		nDeltaY = 0;
		break;
		// EAST
	case 'd':
		nDeltaX = 1;
		nDeltaY = 0;
		break;
		// NORTH
	case 'w':
		nDeltaX = 0;
		nDeltaY = -1;
		break;
		// Not a valid direction
	default:
		// No direction specified, so abort
		return;
	}
	// Is there a closed door present in the direction specified?
	if (nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_CLOSEDDOOR)
	{
		// If there is a closed door, change it to an open one
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_OPENDOOR;
	}
	// Clear the screen to get rid of the notification text
	ConsoleUtils::clear();
}

void CloseDoorCommand(void)
{
	// Draw some notification to the user
	ConsoleUtils::moveCursor(2, 22);
	cout << "Which direction? (w,a,s,d)";
	// Let the user decide where to look
	int nDeltaX = 0;
	int nDeltaY = 0;
	switch (ConsoleUtils::waitForKeypress())
	{
		// SOUTH
	case 's':
		nDeltaX = 0;
		nDeltaY = 1;
		break;
		// WEST
	case 'a':
		nDeltaX = -1;
		nDeltaY = 0;
		break;
		// EAST
	case 'd':
		nDeltaX = 1;
		nDeltaY = 0;
		break;
		// NORTH
	case 'w':
		nDeltaX = 0;
		nDeltaY = -1;
		break;
		// Not a valid direction
	default:
		// No direction specified, so abort
		return;
	}
	// Is there a closed door present in the direction specified?
	if (nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] == TILE_CLOSEDDOOR)
	{
		// If there is a closed door, change it to an open one
		nMapArray[nPlayerY + nDeltaY][nPlayerX + nDeltaX] = TILE_OPENDOOR;
	}
	// Clear the screen to get rid of the notification text
	ConsoleUtils::clear();
}

int main(void) // need to review this
{
	ConsoleUtils::setTitle("Roguelike");
	string playerName = "Player1";
	int DeltaX = 0;
	int DeltaY = 0;
	//Rogue* player = new Rogue(playerName, 100, 0, 0); // theres a problem with this
	
	// Initialize the item map
	memset(nItemArray, 0, sizeof(nItemArray));        
													  // Add a few items to the map
	nItemArray[9][6] = ITEM_ROCK;                       
	nItemArray[4][12] = ITEM_POTION;                    

	// Main program loop
	while (true)
	{
		// Wipe the console clean
		ConsoleUtils::clear();
		DrawMap();
		// Output phase - Draw the player to the screen
		ConsoleUtils::moveCursor(nPlayerX, nPlayerY);
		ConsoleUtils::setFGColour(ConsoleUtils::WHITE, true);
		cout << '@';
		ConsoleUtils::setCursorVisibility(false);
		// Input phase - Wait for the player to do something
		switch (ConsoleUtils::waitForKeypress())
		{
			// Move up
		case 'w':
			// Look ahead to see if we can enter this location
			DeltaX = 0;
			DeltaY = -1;
			break;
			// Move left
		case 'a':
			// Look ahead to see if we can enter this location
			DeltaX = -1;
			DeltaY = 0;
			break;
			// Move right
		case 'd':
			// Look ahead to see if we can enter this location
			DeltaX = 1;
			DeltaY = 0;
			break;
			// Move down
		case 's':
			// Look ahead to see if we can enter this location
			DeltaX = 0;
			DeltaY = 1;
			break;
		case 'o':
			OpenDoorCommand();
			break;
		case 'c':
			CloseDoorCommand();
			break;
			// Quit
		case 'q':
			return 0;
			// Ignore any other key
		default:
			break;
		}
		if (CollisionDetection(nPlayerX + DeltaX, nPlayerY + DeltaY))
		{
			// If allowed, move in the direction specified
			nPlayerX += DeltaX;
			nPlayerY += DeltaY;
		}
		// Processing phase - Implement the player's command
	}
	return 0;
}



