#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <stdint.h>
#include "GraphLocation.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    enum class NodeState {Start, Goal, Free, Blocked, Frontier, Visited};
    struct Node
    {
        GraphLocation location;
        NodeState state;
        int32_t rhs;
        int32_t g;
        Key key;
    };

    bool operator==(const Node & lhs, const Node & rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
