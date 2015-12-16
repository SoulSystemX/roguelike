/******************************************************************************
	File:   ConsoleUtils.hpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Dec 2015
	Ver:    1.0
	Notes:	Class to contain globally scoped console utility functions through
			a class scope, hence keeping them all in the same place and with a
			consistent usage
******************************************************************************/

#ifndef _CONSOLEUTILS_
#define _CONSOLEUTILS_

#include <windows.h> // This is only available for Windows O/S target executables and libraries
#include <conio.h>

class ConsoleUtils final
{
public:
	// Windows C++ console functions reference https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx

	// Colour constants for setting the console foreground and background colours
	const static WORD BLACK = 0x00000000;
	const static WORD WHITE = 0x00000007;
	const static WORD BLUE = 0x00000001;
	const static WORD GREEN = 0x00000002;
	const static WORD RED = 0x00000004;
	const static WORD CYAN = 0x00000003;
	const static WORD MAGENTA = 0x00000005;
	const static WORD YELLOW = 0x00000006;

	// Static member functions, note all the console related functions only work on a Windows
	// operating system console

	// Get the title of the console window
	static std::string getTitle();

	// Set the title of the console window
	static void setTitle(const std::string& title);

	// Get the width of the console window (in pixels, not character columns)
	static int getWindowWidth();
	
	// Get the height of the console window (in pixels, not character rows)
	static int getWindowHeight();

	// Get the width of the console (in character columns, not pixels)
	static SHORT getCols();

	// Get the height of the console (in character rows, not pixels)
	static SHORT getRows();

	// Set the size of the console to the supplied width and height (in character columns/rows, not pixels)
	static void setSize(const SHORT cols, const SHORT rows);

	// Get the x position of the top/left corner of the console (in pixels)
	static int getWindowXPos();

	// Get the y position of the top/left corner of the console (in pixels)
	static int getWindowYPos();

	// Set the position of the top/left corner of the console on the desktop (in pixels), top/left of the
	// desktop is x = 0, y = 0
	static void setWindowPosition(const int x, const int y);

	// Position console at the centre of the desktop
	static void centreWindowPosition();

	// Clears the console
	static void clear();

	// Get if current colour of console foreground text is intense
	static bool getFGIntensity();

	// Get if current colour of console background text is intense
	static bool getBGIntensity();

	// Get current colour of console foreground text
	static WORD getFGColour();

	// Get current colour of console background text
	static WORD getBGColour();

	// Set current colour of console foreground text
	static void setFGColour(const WORD colour, const bool isIntense = false);

	// Set current colour of console background text
	static void setBGColour(const WORD colour, const bool isIntense = false);

	// Get the cursor column position, note the left position will be at (column = 0)
	// ie. zero based co-ordinates
	static SHORT getCursorCol();

	// Get the cursor row position, note the top position will be at (row = 0) ie. zero
	// based co-ordinates
	static SHORT getCursorRow();

	// Move the cursor position to the supplied column and row on the console, note the top
	// left position will be at (column = 0) and (row = 0), ie. zero based co-ordinates
	static void moveCursor(const SHORT col, const SHORT row);
	
	// Check if the console cursor is visible
	static bool isCursorVisible();

	// Set the visibility of the console cursor
	static void setCursorVisibility(const bool isVisible);

	// Hide the console cursor
	inline static void hideCursor() { setCursorVisibility(false); }

	// Show the console cursor
	inline static void showCursor() { setCursorVisibility(true); }

	// Toggle the visibility of the console cursor
	inline static void toggleCursorVisibility() { setCursorVisibility(!isCursorVisible());  }

	// Waits for key to be pressed then returns the key as a char value
	inline static char waitForKeypress() { while(!_kbhit()); return _getch(); }

	// Check if key has been pressed, if true then returns the key as a char value else returns 0
	inline static char getKeypress() { if(_kbhit()) { return _getch(); } return 0; }

protected:

private:
	// Prevents being able to instantiate an object instance of this class 
	inline ConsoleUtils() { ; }

	// Copy constructor
	ConsoleUtils(const ConsoleUtils& other) = delete;
	// Overloaded assignment operator
	ConsoleUtils& operator=(const ConsoleUtils& other) = delete;

	// Prevents being able to destroy an object instance of this class
	inline virtual ~ConsoleUtils() { ; }
};

#endif // _CONSOLEUTILS_
