#include "DiagonalHeuristic.hpp"

#include "Node.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::Node;

    DiagonalHeuristic::DiagonalHeuristic(int32_t diagonalMovementCost_, int32_t straightMovementCost_)
    : diagonalMovementCost(diagonalMovementCost_), straightMovementCost(straightMovementCost_) {}

    double DiagonalHeuristic::calculate(const Node *from, const Node *to)
    {
        double D = straightMovementCost;
        double D2 = diagonalMovementCost;
        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
    }
}
