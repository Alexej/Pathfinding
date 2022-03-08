#include "DefaultCostFunction.hpp"
#include "Node.hpp"
#include "DStarLiteHelpers.hpp"
#include "AlgorithmFunctionHelpers.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Helpers::DStarLiteHelpers;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Helpers::twoNodesDiagonal;
 
    DefaultCostFunction::DefaultCostFunction(int32_t diagonalMovementCost_, int32_t straightMovementCost_)
    : diagonalMovementCost(diagonalMovementCost_), straightMovementCost(straightMovementCost_) {}

    double DefaultCostFunction::calculate(const Node *from, const Node *to)
    {
        if (DStarLiteHelpers::blocked(to) || DStarLiteHelpers::blocked(from))
        {
            return DStarLiteHelpers::infinity();
        }
        
        return twoNodesDiagonal(from, to) ? diagonalMovementCost * to->factor : straightMovementCost * to->factor; 
    }
}