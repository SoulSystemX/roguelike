/******************************************************************************
	File:   GameUtils.cpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Dec 2015
	Ver:    Tutorial 11B 1.0
******************************************************************************/

#include "GameUtils.hpp"

using namespace std;

// This only works on a Windows O/S console
void GameUtils::clrScr()
{

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


	// Fill the buffer with empty whitespace
	DWORD cellCount = csbi.dwSize.X *csbi.dwSize.Y;
	COORD homeCoords = { 0, 0 };
	DWORD count;
	if(!(FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), cellCount, homeCoords, &count)))
	{
		return;
	}

	// Fill the buffer with the current colours and attributes
	if(!(FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)))
	{
		return;
	}

	// Now place the console cursor to the first position in the console
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void GameUtils::setPos(int &x, int &y)
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE == hStdOut)
	{
		return;
	}

	// Get the number of cells in the current buffer
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!(GetConsoleScreenBufferInfo(hStdOut, &csbi)))
	{
		return;
	}

	DWORD cellCount = csbi.dwSize.X *csbi.dwSize.Y;
	COORD homeCoords = { x,y };
	DWORD count;

	// Fill the buffer with the current colours and attributes
	if (!(FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)))
	{
		return;
	}

	// Now place the console cursor to the first position in the console
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void GameUtils::setCursorVisible(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &lpCursor);
}
