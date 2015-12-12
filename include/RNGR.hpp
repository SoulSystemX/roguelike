/******************************************************************************
	File:   RNGR.hpp
	Author: Chris Knowles, DCET, University of Sunderland
	Date:   Oct 2015
	Ver:    Tutorial 11B 1.0
******************************************************************************/

#ifndef _RNGR_
#define _RNGR_

#include <random>
#include <chrono>
#include <functional>

// T must be float, double, or long double
template< class T = float >
class RNGR
{
public:
	inline RNGR(const T minVal, const T maxVal) :
		minVal(minVal),
		maxVal(maxVal)
	{
		seed = std::chrono::system_clock::now().time_since_epoch().count(); // Seed based on system clock
		init();
	}

	inline RNGR(const long long seed, const T minVal, const T maxVal) :
		seed(seed), // Seed assigned by supplied parameter
		minVal(minVal),
		maxVal(maxVal)
	{
		init();
	}

	inline virtual ~RNGR() { ; }

	// Read only accessor functions, return const references to the engine and the distribution
	inline T getSeed() const { return seed; }
	inline const std::mt19937_64& getEngine() const { return engine; }
	inline const std::uniform_real_distribution<T>& getDistribution() const { return distribution; }
	inline T getMinVal() const { return minVal; }
	inline T getMaxVal() const { return maxVal; }

	// Generate a new random number in the range min (inclusive) to max (exclusive)
	inline T generate() { return distribution(engine); }

protected:

private:
	inline RNGR(volatile const RNGR& other) { ; } // Prevent public copying and make private copying do nothing
	inline RNGR& operator=(const RNGR& other) { ; } // Prevent public assignment and make private assignment do nothing

	long long seed; // Seed for this random number generator
	std::mt19937_64 engine; // 64-bit Mersenne Twister engine
	std::uniform_real_distribution<T> distribution; // Real-type uniform distribution function
	T minVal; // Minimum number to use in the generator (note, the generated number will be equal or greater than this value)
	T maxVal; // Maximum number to use in the generator (note, the generated number will be less than this value, never equal to)

	// Common initialisation
	inline void init()
	{
		engine = std::mt19937_64(seed); // Instantiate engine
		distribution = std::uniform_real_distribution<T>(minVal, maxVal); // Instantiate distribution
	}
};

#endif // _RNGR_
