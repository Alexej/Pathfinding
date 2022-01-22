#ifndef A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE
#define A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE

#include <stdint.h>

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    using Pathfinding::Datastructures::Node;
    class AHeuristic
    {
        public:
            virtual int32_t calculate(const Node * from, const Node * to) = 0;
            virtual ~AHeuristic() = default;
    };
}

#endif /* A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE */
