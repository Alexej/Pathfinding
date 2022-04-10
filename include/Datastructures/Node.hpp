#ifndef EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4
#define EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4

#include <cstdint>
#include <limits>

#include "Vec2.hpp"
#include "Key.hpp"

namespace Pathfinding::Abstract { class IDrawNodeStrategy; }

namespace Pathfinding::Datastructures
{
    enum class NodeState { Start, Goal, Free, Blocked, Frontier, Visited };

    struct Node final
    {   
        Node(int32_t h, int32_t w) : location(Vec2i(h,w)) { initNode(); }

        void initNode();
        
        void reset();

        void draw(Pathfinding::Abstract::IDrawNodeStrategy & drawStrategy) const;

        Vec2i location;
        NodeState state;
        double rhs;
        double g;
        Key key;
        bool visitedOnce;
        int32_t factor;
    };

    bool operator==(const Node &lhs, const Node &rhs);
}

#endif /* EA7DED5B_A2DD_40EB_9E16_BAB60E8C98E4 */
