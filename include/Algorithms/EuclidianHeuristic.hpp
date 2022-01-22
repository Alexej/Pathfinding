#ifndef B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0
#define B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0

#include "AHeuristic.hpp"

namespace Pathfinding::Datastrucutres
{
    struct Node;
}

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::AHeuristic;
    using Pathfinding::Datastructures::Node;
    class EuclidianHeuristic final : public AHeuristic
    {
        public: 
            int32_t calculate(const Node * from, const Node * to) override;
    };
}

#endif /* B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0 */
