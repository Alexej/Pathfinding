#include "EuclidianHeuristic.hpp"
#include "Node.hpp"

namespace Pathfinding::Algorithms
{
    int32_t EuclidianHeuristic::calculate(const Node *from, const Node *to)
    {
        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return static_cast<int32_t>(dx * dx + dy * dy);
    }
}
