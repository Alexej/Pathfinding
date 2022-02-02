#include "DiagonalHeuristic.hpp"
#include "Node.hpp"

namespace Pathfinding::Algorithms
{
    double DiagonalHeuristic::calculate(const Node *from, const Node *to)
    {
        double D = 1;
        double D2 = 1;
        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
    }
}
