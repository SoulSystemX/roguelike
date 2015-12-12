#include <iostream>
#include <iomanip> 
#include <string>

// Include the header files for the classes we are testing
#include "GameUtils.hpp"

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

int main(void)
{
	SetConsoleTitle(TEXT("Roguelike"));

	// Initialize the player's on-screen location
	int nPlayerX = 40, nPlayerY = 12;

	// Main program loop
	while (true)
	{
		// Wipe the console clean
		GameUtils::clrScr();
		// Output phase - Draw the player to the screen
		GameUtils::setPos(nPlayerX, nPlayerY);
		cout << '@';
		// Input phase - Wait for the player to do something

		// Processing phase - Implement the player's command
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
	}
	return 0;
}