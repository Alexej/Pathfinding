#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <stdint.h>
#include "Vector2.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    enum class NodeState {Start, Goal, Free, Blocked, Frontier, Visited};
    struct Node
    {
        Vector2i location;
        NodeState state;
        int32_t rhs = std::numeric_limits<int32_t>::max();
        int32_t g = std::numeric_limits<int32_t>::max();
        Key key;
    };

    bool operator==(const Node & lhs, const Node & rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
