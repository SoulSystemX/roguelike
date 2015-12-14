#include <iostream>
#include <iomanip> 
#include <string>

// Include the header files for the classes we are testing
#include "GameUtils.hpp"
#include "Player.hpp"
#include "Rogue.hpp"
#include "GameConstants.hpp"

using namespace std;
//
//int main(int argc, char* argv[])
//{
//	// Run tests A, B, C, D, E, F, G, H, I and J
//	cout << "Run Test A:" << endl << "===========" << endl;
//	//testA();
//	cout << endl;
//
//	GameUtils::setPos();
//
//	cout << "Press any key to continue ... ";
//	GameUtils::waitForKeypress();
//
//	exit(0);
//}

int nMapArray[GameConstants::MAP_HEIGHT][GameConstants::MAP_WIDTH] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
}; // needs to go elsewere

void DrawMap(void)
{
	int zeroVal = 0;

	for (int y = 0; y < GameConstants::MAP_HEIGHT; y++)
	{
		GameUtils::setPos(zeroVal, y); // Set cursor back to start of the line ( this perhaps needs to be abstracted more )
		zeroVal = 0;
		for (int x = 0; x < GameConstants::MAP_WIDTH; x++)
		{
			// Draw the tile
			switch (nMapArray[y][x])
			{
			case GameConstants::TILE_FLOOR:
				//console.Color(7);
				cout << '.';
				break;
			case GameConstants::TILE_WALL:
				//console.Color(8);
				cout << '#';
				break;
			}
		} // end of for loop
	} // end of for loop

}

int main(void) // need to review this
{
	SetConsoleTitle(TEXT("Roguelike"));
	//Rogue* player = new Rogue("Player1", 100, 0, 0); // theres a problem with this

	// Initialize the player's on-screen location
	int nPlayerX = 1, nPlayerY = 1;
	
	// Main program loop
	while (true)
	{
		// Wipe the console clean
		GameUtils::clrScr();
		DrawMap();
		// Output phase - Draw the player to the screen
		GameUtils::setPos(nPlayerX, nPlayerY);
		cout << '@';
		GameUtils::setCursorVisible(false, 0);
		// Input phase - Wait for the player to do something

		// Processing phase - Implement the player's command
		//switch (GameUtils::waitForKeypress())
		//{
		//	// Move down
		//case 's':
		//	nPlayerY++;
		//	break;
		//	// Move left
		//case 'a':
		//	nPlayerX--;
		//	break;
		//	// Move right
		//case 'd':
		//	nPlayerX++;
		//	break;
		//	// Move up
		//case 'w':
		//	nPlayerY--;
		//	break;
		//	// Quit
		//case 'q':
		//	return 0;
		//	// Ignore any other key
		//default:
		//	break;
		//}
		cin.ignore(100);
	}
	return 0;
}

