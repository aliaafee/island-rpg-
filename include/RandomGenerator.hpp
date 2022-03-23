#ifndef __RANDOMGENERATOR_H__
#define __RANDOMGENERATOR_H__

#include <random>

class RandomGenerator : std::minstd_rand0
{
public:
    RandomGenerator(uint_fast32_t seed) : std::minstd_rand0(seed){};

    float randomFloat()
    {
        return static_cast<float>(std::minstd_rand0::operator()()) / static_cast<float>(RAND_MAX);
    }

    int randomInt(int start, int end)
    {
        float v = randomFloat();
        return std::round((float)start + (v * (float)(end - start)));
    }
};
#endif // __RANDOMGENERATOR_H__