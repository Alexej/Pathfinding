#ifndef DA283152_AB11_4665_8DD8_B9B8AEDCB18E
#define DA283152_AB11_4665_8DD8_B9B8AEDCB18E

#include "ACost.hpp"

namespace Pathfinding::Datastrucutres
{
    struct Node;
}

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Abstract::ACost;
    class DefaultCost final : public ACost
    {
        public: 
            int32_t calculate(const Node * from, const Node * to) override;
    };
}

#endif /* DA283152_AB11_4665_8DD8_B9B8AEDCB18E */
