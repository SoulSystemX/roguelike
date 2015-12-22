///******************************************************************************
//File:   Rogue.cpp
//Author: Lee Maguire
//Date:   Dec 2015
//Ver:    1.0
//******************************************************************************/
//
//#include <iostream>
//#include "Actor.hpp"
//#include "GameConstants.hpp"
//
//using namespace std;
//
//bool AddActorToList(Actor *p_cNewActor)
//{
//	// Run through the list looking for an empty slot
//	for (int i = 0; i < MAX_ACTORS; i++)
//	{
//		// Is this empty?
//		if (p_cActorList[i] == NULL)
//		{
//			// If so, use it!
//			p_cActorList[i] = p_cNewActor;
//
//			// Finished! Report success
//			return true;
//		}
//	}
//
//	// Couldn't find a free slot. Report failure.
//	return false;
//}
//
//
//bool RemoveActorFromList(Actor *p_cActor)
//{
//	// Run through the list, looking for the specified actor instance.
//	for (int i = 0; i < MAX_ACTORS; i++)
//	{
//		// Is this the actor?
//		if (p_cActorList[i] == p_cActor)
//		{
//			// If so, deallocate it!
//			delete p_cActor;
//
//			// Clear the slot, allowing it to be used again.
//			p_cActorList[i] = NULL;
//
//			// Finished! Report success
//			return true;
//		}
//	}
//
//	// Couldn't find the actor in the list. Report failure.
//	return false;
//}