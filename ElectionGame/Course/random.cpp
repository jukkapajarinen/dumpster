#include "random.h"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::uniform_int_distribution;

namespace Interface
{

Random Random::RANDOM;

unsigned int Random::uint(unsigned int max)
{
    uniform_int_distribution<unsigned int> distribution(0, max);
	return distribution(generator_);
}

unsigned short Random::die()
{
	return uint(5) + 1;
}

Random::Random():
	generator_(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count())
{
}

} // Interface
