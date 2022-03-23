#include <iostream>
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

using namespace std;

int main()
{
    cout << "# Testing Random" << endl;

    RandomGenerator r(23013);

    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";
    cout << r.randomFloat() << "\n";

    cout << r.randomInt(1, 4) << "\n";
    cout << r.randomInt(1, 4) << "\n";
    cout << r.randomInt(1, 4) << "\n";
    cout << r.randomInt(1, 4) << "\n";
    cout << r.randomInt(1, 4) << "\n";
    cout << r.randomInt(1, 4) << "\n";
}