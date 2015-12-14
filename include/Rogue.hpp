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
		name(""),
		maxHealthPoints(0),
		healthPoints(0),
		posX(0),
		posY(0)
	{
		;
	} // All member variables in a known state

	inline Rogue(const std::string& name, const int healthPoints, int x, int y) :
		name(name),
		maxHealthPoints(healthPoints),
		healthPoints(healthPoints),
		posX(x),
		posY(y)
	{
		;
	} // All member variables in a known state

	  //Destructor
	inline virtual ~Rogue() { ; }

	virtual void receiveAttack(const int damage); // needs to overide
	void move() override; // needs to override?

protected:
private:

	std::string name;
	int maxHealthPoints;
	int healthPoints;
	int posX;
	int posY;
	const char symbol = '@';
};

#endif // _ROGUE_