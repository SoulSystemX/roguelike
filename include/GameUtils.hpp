/******************************************************************************
	File:   GameUtils.hpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Dec 2015
	Ver:    Tutorial 11B 1.0
	Notes:	Class to contain globally scoped game utility functions through a
			class scope, hence keeping them all in the same place and with a
			consistent usage
******************************************************************************/

#ifndef _GAMEUTILS_
#define _GAMEUTILS_

#include <windows.h> // This is only available for Windows O/S target executables and libraries
#include <conio.h>

class GameUtils final
{
public:
	// Static member functions
	
	// Clears the console, note this only works on a Windows O/S console
	static void clrScr();

	// Clears the console, note this only works on a Windows O/S console
	static void setPos(int &x, int &y);
	
	// Waits for key to be pressed then returns the key as a char value
	inline static char waitForKeypress() { while(!_kbhit()); return _getch(); }

	// Check if key has been pressed, if true then returns the key as a char value else returns 0
	inline static char getKeypress() { if(_kbhit()) { return _getch(); } return 0; }

protected:

private:
	// Prevents being able to instantiate an object instance of this class 
	inline GameUtils() { ; }

	// Copy constructor
	GameUtils(const GameUtils& other) = delete;
	// Overloaded assignment operator
	GameUtils& operator=(const GameUtils& other) = delete;

	// Prevents being able to destroy an object instance of this class
	inline virtual ~GameUtils() { ; }
};

#endif // _GAMEUTILS_
