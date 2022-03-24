#ifndef CDC2E736_775D_4CD3_B2C9_3AF63B5AE551
#define CDC2E736_775D_4CD3_B2C9_3AF63B5AE551

#include "Node.hpp"
#include <limits>

namespace Pathfinding::Helpers
{
    inline double infinity()
    {
        return std::numeric_limits<double>::infinity();
    }

    inline bool locallyConsistent(const Pathfinding::Datastructures::Node *node)
    {
        return node->g == node->rhs;
    }

    inline bool locallyOverconsistent(const Pathfinding::Datastructures::Node *node)
    {
        return node->g > node->rhs;
    }

    inline bool blocked(const Pathfinding::Datastructures::Node *node)
    {
        return node->state == Pathfinding::Datastructures::NodeState::Blocked;
    }
}

#endif /* CDC2E736_775D_4CD3_B2C9_3AF63B5AE551 */
