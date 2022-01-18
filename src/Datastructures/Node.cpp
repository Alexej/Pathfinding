#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    bool operator==(const Node & lhs, const Node & rhs)
    {
        return lhs.location == rhs.location;
    }
}