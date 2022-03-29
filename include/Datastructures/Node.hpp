#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <cstdint>
#include <limits>

#include "Vec2.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    enum class NodeState { Start, Goal, Free, Blocked, Frontier, Visited, Recalculated };
    struct Node
    {
        Node() = default;
        
        Node(int32_t h, int32_t w) : location(Vec2i(h,w)) { initNode(); }

        void initNode()
        {
            state = NodeState::Free;
            rhs = std::numeric_limits<double>::infinity();
            g = std::numeric_limits<double>::infinity();
            visitedOnce = false;
            factor = 1;
        }
        
        void reset()
        {
            initNode();
            location = Vec2i();
            key = Key();
        }

        Vec2i location;
        NodeState state;;
        double rhs;;
        double g;;
        Key key;
        bool visitedOnce;
        int32_t factor;
    };

    bool operator==(const Node &lhs, const Node &rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
