#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    bool operator<(const Key &lhs, const Key &rhs)
    {
        return std::tie(lhs.k1, lhs.k2) < std::tie(rhs.k1, rhs.k2);
    }

    bool operator==(const Key &lhs, const Key &rhs)
    {
        return lhs.k1 == rhs.k1 && lhs.k2 == rhs.k2;
    }

    bool operator>(const Key &lhs, const Key &rhs)
    {
        return std::tie(lhs.k1, lhs.k2) > std::tie(rhs.k1, rhs.k2);
    }
}