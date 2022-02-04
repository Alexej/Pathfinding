#include "DiagonalHeuristic.hpp"
#include "Node.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::Node;

    double DiagonalHeuristic::calculate(const Node *from, const Node *to)
    {
        double D = 10 * 1;
        double D2 = static_cast<int>(10 * sqrt(2));
        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
    }
}
