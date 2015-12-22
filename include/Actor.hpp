//#ifndef ACTOR_H_
//#define ACTOR_H_
//
//class Actor
//{
//public:
//
//	Actor(void);
//
//	//Destructor
//	inline virtual ~Actor() { ; }
//
//	// Changes how the actor appears in the game world
//	void    SetAppearance(char nDisplayChar, short nDisplayColor);
//	// Changes the position of the actor
//	void    SetPos(int x, int y);
//	// Draws the actor to the screen
//	void    Draw(void);
//	// Periodic update routine for the actor
//	void    Update(void);
//
//	bool AddActorToList(Actor *p_cNewActor);
//	
//	bool RemoveActorFromList(Actor *p_cActor);
//	
//	}
//
//protected:
//	
//	// Horizontal coordinate of the actor, relative to the level's origin
//	int     nPosX;
//	// Vertical coordinate of the actor, relative to the level's origin.
//	int     nPosY;
//	// ASCII character code used to draw the actor to the screen
//	char    nDisplayChar;
//	// Color code for this actor
//	short   nColorCode;
//};
//#endif // ACTOR_H 