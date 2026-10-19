#include "RNG.h"

#include <cstdlib>
#include <ctime>

namespace RNG
{
	void Setup()
	{
		std::srand(std::time(nullptr));
	}

	void Waste()
	{
		std::rand();
	}

	int GetRandomNumber(int max)
	{
		return std::rand() % max;
	}
}