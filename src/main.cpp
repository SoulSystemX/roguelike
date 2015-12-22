#include <iostream>
#include <iomanip> 
#include <string>

// Include the header files for the classes we are testing
#include "ConsoleUtils.hpp"
#include "Player.hpp"
#include "Rogue.hpp"
#include "Enemy.hpp"
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

// The player's inventory
int nInventory[INVENTORY_SLOTS];

// Item map, overlaid on top of the world map
int nItemArray[GameConstants::MAP_HEIGHT][GameConstants::MAP_WIDTH];

// List of actors
Enemy *	p_cActorList[MAX_ACTORS];

void DrawMap(void);
void DrawTile(int x, int y);
bool CollisionDetection(int nMapX, int nMapY);
void OpenDoorCommand(void);
void CloseDoorCommand(void);
void ShowInventory(void);
void GetCommand(void);
void DropCommand(void);

bool AddActorToList(Enemy *p_cNewActor);
bool RemoveActorFromList(Enemy *p_cNewActor);

int main(void) // need to review this
{
	ConsoleUtils::setTitle("Roguelike");
	string playerName = "Player1";

	Rogue *player = new Rogue(playerName, 100, 1, 1); // theres a problem with this
	player->SetAppearance('@', ConsoleUtils::WHITE);

	// Initialize the item map
	memset(nItemArray, 0, sizeof(nItemArray));
	// Add a few items to the map
	nItemArray[9][6] = ITEM_ROCK;
	nItemArray[4][12] = ITEM_POTION;

	// Initialize the item map
	memset(nInventory, 0, sizeof(nInventory));

	// Initialize the list to be empty
	for (int i = 0; i < MAX_ACTORS; i++)
		p_cActorList[i] = NULL;

	for (int i = 0; i < MAX_ACTORS; i++)
	{
		int x, y;
		Enemy *p_cNewActor = new Enemy();

		do {
			x = rand() % GameConstants::MAP_WIDTH;
			y = rand() % GameConstants::MAP_HEIGHT;
		} while (!CollisionDetection(x, y));

		p_cNewActor->SetAppearance('<', ConsoleUtils::RED);
		p_cNewActor->SetPos(x, y);
		AddActorToList(p_cNewActor);
	}


	// Main program loop
	while (true)
	{
		int DeltaX = 0;
		int DeltaY = 0;


		// Wipe the console clean
		ConsoleUtils::clear();
		DrawMap();
		// Draw the inventory
		ShowInventory();

		for (int i = 0; i < MAX_ACTORS; i++)
		{
			if (p_cActorList[i] != NULL)
			{
				p_cActorList[i]->Update();
				p_cActorList[i]->Draw();
			}
		}

		//player->Draw();


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
																			case 'g':
																				GetCommand();
																				break;
																			case 'f':
																				DropCommand();
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

void GetCommand(void)
{
	// First check to see if there's actually an item present
	if (nItemArray[nPlayerY][nPlayerX] == ITEM_NONE)
	{
		// Complain that there isn't an item here
		// Abort the rest of the command, we're done
		return;
	}
	// Run through the inventory, checking for the first available slot
	for (int i = 0; i < INVENTORY_SLOTS; i++)
	{
		// Found an open slot?
		if (nInventory[i] == ITEM_NONE)
		{
			// If so, move the item to the slot and remove it from the world
			nInventory[i] = nItemArray[nPlayerY][nPlayerX];
			nItemArray[nPlayerY][nPlayerX] = ITEM_NONE;

			// Finished the command
			return;
		}
	}

	// If execution gets here, it means that there is no open slots available. So
	// complain about it somehow and then abort

	return;     // ABORT!
}

void DropCommand(void)
{
	// Ask the user which inventory slot they're trying to drop
	ConsoleUtils::moveCursor(2, GameConstants::MAP_HEIGHT + 2);
	cout << "Drop from which slot?";
	
	// Convert the key press into an inventory slot
	int nSlot = ConsoleUtils::waitForKeypress() - 'a';
	// Verify that this is a valid slot
	if (nSlot < 0 || nSlot >= INVENTORY_SLOTS)
	{
		// Complain to the user
		ConsoleUtils::moveCursor(2, GameConstants::MAP_HEIGHT + 3);
		cout << "Invalid slot";
		// Wait for the user to press a key
		ConsoleUtils::waitForKeypress();
	}
	// Verify that there actually is something present in this slot
	else if (nInventory[nSlot] == ITEM_NONE)
	{
		// Complain to the user
		ConsoleUtils::moveCursor(2, GameConstants::MAP_HEIGHT + 3);
		cout << "No item present";
		// Wait for the user to press a key
		ConsoleUtils::waitForKeypress();
	}
	// Verify that there's room on the ground to actually drop this
	else if (nItemArray[nPlayerY][nPlayerX] != ITEM_NONE)
	{
		// Complain to the user
		ConsoleUtils::moveCursor(2, GameConstants::MAP_HEIGHT + 3);
		cout << "No room to drop item";
		// Wait for the user to press a key
		ConsoleUtils::waitForKeypress();
	}
	// Everything's happy and awesome, ready to go
	else
	{
		// Place the item on the ground
		nItemArray[nPlayerY][nPlayerX] = nInventory[nSlot];
		nInventory[nSlot] = ITEM_NONE;
	}
	// Clear the screen to get rid of all the text
	ConsoleUtils::clear();
}

void DrawTile(int x, int y)
{
	int nType = nMapArray[y][x];

	// Designate the position of the tile on screen
	ConsoleUtils::moveCursor(x, y);
	// Is there an item present at this location?
	int nColor;
	char nCharacter;
	if (nItemArray[y][x] != ITEM_NONE)
	{
		int nItemType = nItemArray[y][x];
		nColor = sItemIndex[nItemType].nColorCode;
		nCharacter = sItemIndex[nItemType].nCharacter;
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

void ShowInventory(void)
{
	ConsoleUtils::setFGColour(ConsoleUtils::WHITE);
	ConsoleUtils::moveCursor(GameConstants::MAP_WIDTH + 2, 1);
	cout << "INVENTORY";
	ConsoleUtils::moveCursor(GameConstants::MAP_WIDTH + 2, 2);
	cout << "---------";
	ConsoleUtils::setFGColour(ConsoleUtils::WHITE);
	for (int i = 0; i < INVENTORY_SLOTS; i++)
	{
		// Grab the item type being stored in this inventory slot
		int nItemType = nInventory[i];
		// Draw the items name to the console
		ConsoleUtils::moveCursor(GameConstants::MAP_WIDTH + 2, 3 + i);
		cout << (char)('A' + i) << ": " << sItemIndex[nItemType].p_szName;
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
} // Removed collision detection and placed in Game

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

bool AddActorToList(Enemy *p_cNewActor)
{
//	 Run through the list looking for an empty slot
	for (int i = 0; i < MAX_ACTORS; i++)
	{
	//	 Is this empty?
		if (p_cActorList[i] == NULL)
		{
		//	 If so, use it!
			p_cActorList[i] = p_cNewActor;

//			 Finished! Report success
			return true;
		}
	}

	// Couldn't find a free slot. Report failure.
	return false;
} //moved to game

bool RemoveActorFromList(Enemy *p_cActor)
{
	// Run through the list, looking for the specified actor instance.
	for (int i = 0; i < MAX_ACTORS; i++)
	{
		// Is this the actor?
		if (p_cActorList[i] == p_cActor)
		{
		//	 If so, deallocate it!
			delete p_cActor;

		//	 Clear the slot, allowing it to be used again.
			p_cActorList[i] = NULL;

		//	 Finished! Report success
			return true;
		}
	}

//	 Couldn't find the actor in the list. Report failure.
	return false;
} // moved to game





