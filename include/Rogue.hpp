/******************************************************************************
File:   Rogue.hpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    0.1
******************************************************************************/

#ifndef _ROGUE_
#define _ROGUE_

#include <string>
#include "Player.hpp"
#include "GameUtils.hpp"

class Rogue : public Player
{
public:
	inline Rogue() :
		Player("", 0, 0, 0)
	{
		;
	} // All member variables in a known state

	inline Rogue(const std::string& name, const int healthPoints, int x, int y) :
		Player(name, healthPoints, x, y)
	{
		;
	} // All member variables in a known state

	  //Destructor
	inline virtual ~Rogue() { ; }

	//inline void receiveAttack(const int damage) override { }
	//virtual void move(int xpos, int ypos) override;
	
protected:
private:

	// Copy constructor
	Rogue(const Rogue& other) = delete;
	// Overloaded assignment operator
	Rogue& operator=(const Rogue& other) = delete;

	std::string name;
	int maxHealthPoints;
	int healthPoints;
	int posX;
	int posY;
	const char symbol = '@';
};

#endif // _ROGUE_