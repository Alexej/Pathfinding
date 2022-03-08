#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <cstdint>
#include "Vec2.hpp"
#include "Key.hpp"
#include <limits>

namespace Pathfinding::Datastructures
{
    enum class NodeState
    {
        Start,
        Goal,
        Free,
        Blocked,
        Frontier,
        Visited,
        Recalculated
    };
    struct Node
    {
        Node() = default;
        Node(int32_t h, int32_t w) : location(Vec2i(h,w)) {}
        Vec2i location;
        NodeState state = NodeState::Free;
        double rhs = std::numeric_limits<double>::infinity();
        double g = std::numeric_limits<double>::infinity();
        Key key;
        bool visitedOnce = false;
        int32_t factor = 1;
    };

    bool operator==(const Node &lhs, const Node &rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
