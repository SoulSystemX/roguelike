/******************************************************************************
File:   Player.hpp
Author: Lee Maguire
Date:   Dec 2015
Ver:    0.1
******************************************************************************/

#ifndef _PLAYER_
#define _PLAYER_

#include <string>

class Player
{
public:
	inline Player() :
		name(""),
		maxHealthPoints(0),
		healthPoints(0),
		posX(0),
		posY(0)
	{
		;
	} // All member variables in a known state

	inline Player(const std::string& name, const int healthPoints, int x, int y) :
		name(name),
		maxHealthPoints(healthPoints),
		healthPoints(healthPoints),
		posX(x),
		posY(y)
	{
		;
	} // All member variables in a known state

	//Destructor
	inline virtual ~Player() { ; }

	inline std::string getName() const { return name; }
	inline int getMaxHealthPoints() const { return maxHealthPoints; }
	inline int getHealthPoints() const { return healthPoints; }

	//virtual void receiveAttack(const int damage);
	inline bool isAlive() const { return (healthPoints > 0); }
	void receiveHealing(const int amount);
	virtual void move(int xpos, int ypos);

protected:
private:
	// Copy constructor
	Player(const Player& other) = delete;
	// Overloaded assignment operator
	Player& operator=(const Player& other) = delete;

	std::string name;
	int maxHealthPoints;
	int healthPoints;
	int posX;
	int posY;
	const char symbol = '@';
};

#endif // _PLAYER_