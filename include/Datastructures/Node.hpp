#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <cstdint>
#include "Vector2.hpp"
#include "Key.hpp"

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
        Vec2i location;
        NodeState state;
        double rhs = std::numeric_limits<double>::infinity();
        double g = std::numeric_limits<double>::infinity();
        Key key;
    };

    bool operator==(const Node &lhs, const Node &rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
