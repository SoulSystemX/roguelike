///******************************************************************************
//File:   Game.hpp
//Author: Lee Maguire
//Date:   Dec 2015
//Ver:    0.1
//******************************************************************************/
//
//#ifndef _GAME_
//#define _GAME_
//
////#include <string>
//#include "GameConstants.hpp"
//
//class Game
//{
//public:
//	inline Game() {	;} // All member variables in a known state
//
//	  //Destructor
//	inline virtual ~Game() { ; }
//
//	inline bool CollisionDetection(int nMapX, int nMapY)
//	{
//		// Before we do anything, make darn sure that the coordinates are valid
//		if (nMapX < 0 || nMapX >= GameConstants::MAP_WIDTH || nMapY < 0 || nMapY >= GameConstants::MAP_HEIGHT)
//			return false;
//		// Store the value of the tile specified
//		int nTileValue = nMapArray[nMapY][nMapX];
//		// Return true if it's passable
//		return sTileIndex[nTileValue].bPassable;
//	}
//
//protected:
//private:
//	// Copy constructor
//	Game(const Game& other) = delete;
//	// Overloaded assignment operator
//	Game& operator=(const Game& other) = delete;
//
//};
//
//#endif // _GAME_