#include <iostream>
#include <iomanip> 
#include <string>

// Include the header files for the classes we are testing
#include "ConsoleUtils.hpp"
#include "Player.hpp"
#include "Rogue.hpp"
#include "GameConstants.hpp"

using namespace std;

int nMapArray[GameConstants::MAP_HEIGHT][GameConstants::MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
}; // needs to go elsewere

//void DrawMap(void)
//{
//	int zeroVal = 0;
//
//	for (int y = 0; y < GameConstants::MAP_HEIGHT; y++)
//	{
//		GameUtils::setPos(zeroVal, y); // Set cursor back to start of the line ( this perhaps needs to be abstracted more )
//		zeroVal = 0;
//		for (int x = 0; x < GameConstants::MAP_WIDTH; x++)
//		{
//			// Draw the tile
//			switch (nMapArray[y][x])
//			{
//			case GameConstants::TILE_FLOOR:
//				//console.Color(7);
//				cout << '.';
//				break;
//			case GameConstants::TILE_WALL:
//				//console.Color(8);
//				cout << '#';
//				break;
//			}
//		} // end of for loop
//	} // end of for loop
//
//}

void DrawMap(void)
{
	for (int y = 0; y < GameConstants::MAP_HEIGHT; y++)
	{
		ConsoleUtils::moveCursor(0, y);
		for (int x = 0; x < GameConstants::MAP_WIDTH; x++)
		{
			// Draw the tile
			switch (nMapArray[y][x])
			{
			case GameConstants::TILE_FLOOR:
				ConsoleUtils::setFGColour(ConsoleUtils::GREEN, true);
				//ConsoleUtils::setBGColour(ConsoleUtils::GREEN, false);
				cout << '.';
				break;
			case GameConstants::TILE_WALL:
				ConsoleUtils::setFGColour(ConsoleUtils::YELLOW, true);
				//ConsoleUtils::setBGColour(ConsoleUtils::GREEN, false);
				cout << '#';
				break;
			}
		} // end of for loop
	} // end of for loop

}

int main(void) // need to review this
{
	ConsoleUtils::setTitle("Roguelike");
	string playerName = "Player1";

	Rogue* player = new Rogue(playerName, 100, 0, 0); // theres a problem with this

	// Initialize the player's on-screen location
	int nPlayerX = 1, nPlayerY = 1;
	
	// Main program loop
	while (true)
	{
		// Wipe the console clean
								//GameUtils::clrScr();
		ConsoleUtils::clear();
		DrawMap();
		// Output phase - Draw the player to the screen
		//ConsoleUtils::moveCursor(); // get player position?
		cout << '@';
		ConsoleUtils::setCursorVisibility(false);
		// Input phase - Wait for the player to do something
		switch (GameUtils::waitForKeypress())
		{
			// Move down
		case 's':
			nPlayerY++;
			break;
			// Move left
		case 'a':
			nPlayerX--;
			break;
			// Move right
		case 'd':
			nPlayerX++;
			break;
			// Move up
		case 'w':
			nPlayerY--;
			break;
			// Quit
		case 'q':
			return 0;
			// Ignore any other key
		default:
			break;
		}
		cin.ignore(100);
		// Processing phase - Implement the player's command
	}
	return 0;
}

