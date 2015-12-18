/******************************************************************************
	File:   ConsoleUtils.cpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Dec 2015
	Ver:    1.0
******************************************************************************/

#include <string>
#include "ConsoleUtils.hpp"

using namespace std;

// Get the title of the console window
string ConsoleUtils::getTitle()
{
	CHAR title[1024];

	if(!GetConsoleTitle(title, 1024))
	{
		return "";
	}

	return string(title);
}

// Set the title of the console window
void ConsoleUtils::setTitle(const string& title)
{
	SetConsoleTitle(title.c_str());
}

// Get the width of the console window (in pixels, not character columns)
int ConsoleUtils::getWindowWidth()
{
	HWND hConsoleWindow = GetConsoleWindow();
	RECT consoleRect;

	if(INVALID_HANDLE_VALUE == hConsoleWindow)
	{
		return 0;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return 0;
	}

	return consoleRect.right - consoleRect.left;
};

// Get the height of the console window (in pixels, not character rows)
int ConsoleUtils::getWindowHeight()
{
	HWND hConsoleWindow = GetConsoleWindow();
	RECT consoleRect;

	if(INVALID_HANDLE_VALUE == hConsoleWindow)
	{
		return 0;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return 0;
	}

	return consoleRect.bottom - consoleRect.top;
};

// Get the width of the console (in character columns, not pixels)
SHORT ConsoleUtils::getCols()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!(GetConsoleScreenBufferInfo(hStdOut, &csbInfo)))
	{
		return 0;
	}

	return csbInfo.srWindow.Right + 1;
}

// Get the height of the console (in character rows, not pixels)
SHORT ConsoleUtils::getRows()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!(GetConsoleScreenBufferInfo(hStdOut, &csbInfo)))
	{
		return 0;
	}

	return csbInfo.srWindow.Bottom + 1;
}

// Set the size of the console to the supplied width and height (in character columns/rows, not pixels)
void ConsoleUtils::setSize(const SHORT cols, const SHORT rows)
{
	// Get the original position of the console
	int xpos = ConsoleUtils::getWindowXPos();
	int ypos = ConsoleUtils::getWindowYPos();

	HWND hDesktopWindow = GetDesktopWindow();
	HWND hConsoleWindow = GetConsoleWindow();
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if((INVALID_HANDLE_VALUE == hDesktopWindow) || (INVALID_HANDLE_VALUE == hConsoleWindow) || (INVALID_HANDLE_VALUE == hStdOut))
	{
		return;
	}

	RECT desktopRect;
	RECT consoleRect;

	if(!MoveWindow(hConsoleWindow, xpos, ypos, 1, 1, true))
	{
		return;
	}

	if(!SetConsoleScreenBufferSize(hStdOut, COORD{ cols, rows }))
	{
		return;
	}

	if(!GetWindowRect(hDesktopWindow, &desktopRect))
	{
		return;
	}

	if(!MoveWindow(hConsoleWindow, xpos, ypos, desktopRect.right, desktopRect.bottom, true))
	{
		return;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return;
	}

	int w = consoleRect.right - consoleRect.left;
	int h = consoleRect.bottom - consoleRect.top;

	MoveWindow(hConsoleWindow, xpos, ypos, w, h, true);
}

// Get the x position of the top/left corner of the console (in pixels)
int ConsoleUtils::getWindowXPos()
{
	HWND hConsoleWindow = GetConsoleWindow();
	RECT consoleRect;

	if(INVALID_HANDLE_VALUE == hConsoleWindow)
	{
		return 0;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return 0;
	}

	return consoleRect.left;
};

// Get the y position of the top/left corner of the console (in pixels)
int ConsoleUtils::getWindowYPos()
{
	HWND hConsoleWindow = GetConsoleWindow();
	RECT consoleRect;

	if(INVALID_HANDLE_VALUE == hConsoleWindow)
	{
		return 0;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return 0;
	}

	return consoleRect.top;
}

// Set the position of the top/left corner of the console on the desktop (in pixels), top/left of the
// desktop is x = 0, y = 0
void ConsoleUtils::setWindowPosition(const int x, const int y)
{
	HWND hConsoleWindow = GetConsoleWindow();

	if(INVALID_HANDLE_VALUE == hConsoleWindow)
	{
		return;
	}

	RECT consoleRect;

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return;
	}

	int w = consoleRect.right - consoleRect.left;
	int h = consoleRect.bottom - consoleRect.top;

	MoveWindow(hConsoleWindow, x, y, w, h, true);
}

// Position console at the centre of the desktop
void ConsoleUtils::centreWindowPosition()
{
	HWND hDesktopWindow = GetDesktopWindow();
	HWND hConsoleWindow = GetConsoleWindow();

	if((INVALID_HANDLE_VALUE == hDesktopWindow) || (INVALID_HANDLE_VALUE == hConsoleWindow))
	{
		return;
	}

	RECT desktopRect;
	RECT consoleRect;

	if(!GetWindowRect(hDesktopWindow, &desktopRect))
	{
		return;
	}

	if(!GetWindowRect(hConsoleWindow, &consoleRect))
	{
		return;
	}

	int w = consoleRect.right - consoleRect.left;
	int h = consoleRect.bottom - consoleRect.top;
	int x = (desktopRect.right - w) / 2;
	int y = (desktopRect.bottom - h) / 2;

	MoveWindow(hConsoleWindow, x, y, w, h, true);
}

// Clears the console
void ConsoleUtils::clear()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!(GetConsoleScreenBufferInfo(hStdOut, &csbi)))
	{
		return;
	}

	// Fill the console buffer with empty whitespace
	DWORD cellCount = getCols() * getRows();
	COORD homeCoords = { 0, 0 };
	DWORD count; // Ignored
	if(!(FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), cellCount, homeCoords, &count)))
	{
		return;
	}

	// Fill the console buffer with the current colours and attributes
	if(!(FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)))
	{
		return;
	}

	// Now place the console cursor to the first position in the console
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

// Clears a portion of the console defined by the bounds of a rectangle supplied to the function,
// the x and y values define the top left of the rectangle, the w and h define its width and height,
// note that the cursor stays where it was originally
void ConsoleUtils::clear(const SHORT x, const SHORT y, const SHORT w, const SHORT h)
{
	// Ensure bounds of rectangle are confined in the console buffer or otherwise return without
	// clearing the rectangle
	if((x < 0) || (y < 0) || ((x + w) > getCols()) || ((y + h) > getRows()))
	{
		// Invalid rectangle so abort
		return;
	}

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	// Get the number of cells in the current buffer
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(!(GetConsoleScreenBufferInfo(hStdOut, &csbi)))
	{
		return;
	}

	// Fill the supplied rectangle region of the console buffer with empty whitespace
	for(int r = 0; r < h; r++)
	{
		COORD homeCoords = { x, (y + r) };
		DWORD count; // Ignored
		if(!(FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), w, homeCoords, &count)))
		{
			return;
		}

		// Fill the buffer with the current colours and attributes
		if(!(FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, w, homeCoords, &count)))
		{
			return;
		}
	}
}

// Get if current colour of console foreground text is intense
bool ConsoleUtils::getFGIntensity()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return 0;
	}

	return static_cast<bool>((csbInfo.wAttributes & 0x00000008) != 0);
}

// Get if current colour of console background text is intense
bool ConsoleUtils::getBGIntensity()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return 0;
	}

	return static_cast<bool>((csbInfo.wAttributes & 0x00000080) != 0);
}

// Get current colour of console foreground text
WORD ConsoleUtils::getFGColour()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return 0;
	}

	return (csbInfo.wAttributes & 0x00000007);
}

// Get current colour of console background text
WORD ConsoleUtils::getBGColour()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return 0;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return 0;
	}

	return ((csbInfo.wAttributes & 0x00000070) >> 4);
}

// Set current colour of console foreground text
void ConsoleUtils::setFGColour(const WORD colour, const bool isIntense)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return;
	}

	WORD cAttributes = (csbInfo.wAttributes & 0xFFFFFFF0) | colour | (isIntense ? FOREGROUND_INTENSITY : 0);

	SetConsoleTextAttribute(hStdOut, cAttributes);
}

// Set current colour of console background text
void ConsoleUtils::setBGColour(const WORD colour, const bool isIntense)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return;
	}

	WORD cAttributes = (csbInfo.wAttributes & 0xFFFFFF0F) | (colour << 4) | (isIntense ? BACKGROUND_INTENSITY : 0);

	SetConsoleTextAttribute(hStdOut, cAttributes);
}

// Get the cursor column position, note the left position will be at (column = 0)
// ie. zero based co-ordinates
SHORT ConsoleUtils::getCursorCol()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return -1; // Invalid cursor column
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return -1; // Invalid cursor column
	}

	return csbInfo.dwCursorPosition.X;
}

// Get the cursor row position, note the top position will be at (row = 0) ie. zero
// based co-ordinates
SHORT ConsoleUtils::getCursorRow()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return -1; // Invalid cursor column
	}

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	if(!GetConsoleScreenBufferInfo(hStdOut, &csbInfo))
	{
		return -1; // Invalid cursor column
	}

	return csbInfo.dwCursorPosition.Y;
}

// Move the cursor position to the supplied column and row on the console, note the top
// left position will be at (column = 0) and (row = 0), ie. zero based co-ordinates
void ConsoleUtils::moveCursor(const SHORT col, const SHORT row)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	SetConsoleCursorPosition(hStdOut, COORD{ col, row });
}

// Check if the console cursor is visible
bool ConsoleUtils::isCursorVisible()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return false;
	}

	CONSOLE_CURSOR_INFO ccInfo;
	GetConsoleCursorInfo(hStdOut, &ccInfo);

	return (ccInfo.bVisible != 0);
}

// Set the visibility of the console cursor
void ConsoleUtils::setCursorVisibility(const bool isVisible)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	CONSOLE_CURSOR_INFO ccInfo;
	if(!GetConsoleCursorInfo(hStdOut, &ccInfo))
	{
		return;
	}

	ccInfo.bVisible = isVisible;

	SetConsoleCursorInfo(hStdOut, &ccInfo);
}
