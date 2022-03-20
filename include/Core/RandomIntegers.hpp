#ifndef B56BD4FA_DD81_4671_9491_B83614D42DE4
#define B56BD4FA_DD81_4671_9491_B83614D42DE4

#include <random>
#include "Constants.hpp"

namespace Pathfinding::Core
{
    class RandomIntegers
    {
        public:
            RandomIntegers()
            {
                mt = std::mt19937(rd());
            }

            int32_t getRandomInteger(int32_t lower, int32_t upper)
            {
                dist = std::uniform_int_distribution<int32_t>(lower, upper);
                return dist(mt);
            }

            int32_t getRandomInteger()
            {
                return getRandomInteger(Pathfinding::Constants::LOWER_DEFAULT_RANDOM_NUMBER, 
                                        Pathfinding::Constants::UPPER_DEFAULT_RANDOM_NUMBER);
            }

        private:
            std::random_device rd;
            std::mt19937 mt;
            std::uniform_int_distribution<int32_t> dist;
    };  
}

#endif /* B56BD4FA_DD81_4671_9491_B83614D42DE4 */
