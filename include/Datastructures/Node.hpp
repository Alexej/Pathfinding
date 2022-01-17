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
        NodeState state = NodeState::Free;
        int32_t rhs = std::numeric_limits<int32_t>::max();
        int32_t g = std::numeric_limits<int32_t>::max();
        Key key;
    };
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
