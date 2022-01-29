#include "EuclidianHeuristic.hpp"
#include "Node.hpp"

namespace Pathfinding::Algorithms
{
    int64_t EuclidianHeuristic::calculate(const Node *from, const Node *to)
    {
        int64_t dx = abs(from->location.width - to->location.width);
        int64_t dy = abs(from->location.height - to->location.height);
        return static_cast<int64_t>(dx * dx + dy * dy);
    }
}
