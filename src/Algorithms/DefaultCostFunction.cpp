#include "DefaultCostFunction.hpp"
#include "Node.hpp"
#include "DStarLiteHelpers.hpp"


namespace Pathfinding::Algorithms
{
    using Pathfinding::Helpers::DStarLiteHelpers;
    using Pathfinding::Datastructures::Node;
    
    DefaultCostFunction::DefaultCostFunction(int32_t diagonalMovementCost_, int32_t straightMovementCost_)
    : diagonalMovementCost(diagonalMovementCost_), straightMovementCost(straightMovementCost_) {}

    double DefaultCostFunction::calculate(const Node *from, const Node *to)
    {
        if (DStarLiteHelpers::blocked(to) || DStarLiteHelpers::blocked(from))
        {
            return DStarLiteHelpers::infinity();
        }

        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return dx - dy == 0 ? diagonalMovementCost : straightMovementCost;
    }
}