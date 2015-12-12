/******************************************************************************
	File:   RNGI.hpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Oct 2015
	Ver:    Tutorial 11B 1.0
******************************************************************************/

#ifndef _RNGI_
#define _RNGI_

#include <random>
#include <chrono>
#include <functional>

// T must be short, int, long, long long, unsigned short, unsigned int, unsigned long, or unsigned long long 
template< class T = int >
class RNGI
{
public:
	inline RNGI(const T minVal, const T maxVal) :
		minVal(minVal),
		maxVal(maxVal)
	{
		seed = std::chrono::system_clock::now().time_since_epoch().count(); // Seed based on system clock
		init();
	}

	inline RNGI(const long long seed, const T minVal, const T maxVal) :
		seed(seed), // Seed assigned by supplied parameter
		minVal(minVal),
		maxVal(maxVal)
	{
		init();
	}

	inline virtual ~RNGI() { ; }

	// Read only accessor functions, return const references to the engine and the distribution
	inline T getSeed() const { return seed; }
	inline const std::mt19937_64& getEngine() const { return engine; }
	inline const std::uniform_int_distribution<T>& getDistribution() const { return distribution; }
	inline T getMinVal() const { return minVal; }
	inline T getMaxVal() const { return maxVal; }

	// Generate a new random number in the range min to max (both inclusive)
	inline T generate() { return distribution(engine); }

protected:

private:
	inline RNGI(volatile const RNGI& other) { ; } // Prevent public copying and make private copying do nothing
	inline RNGI& operator=(const RNGI& other) { ; } // Prevent public assignment and make private assignment do nothing

	long long seed; // Seed for this random number generator
	std::mt19937_64 engine; // 64-bit Mersenne Twister engine
	std::uniform_int_distribution<T> distribution; // Integral-type uniform distribution function
	T minVal; // Minimum number to use in the generator (note, the generated number will be equal to or greater than this value)
	T maxVal; // Maximum number to use in the generator (note, the generated number will be less than or equal to this value)

	// Common initialisation
	inline void init()
	{
		engine = std::mt19937_64(seed); // Instantiate engine
		distribution = std::uniform_int_distribution<T>(minVal, maxVal); // Instantiate distribution
	}
};

#endif // _RNGI_
