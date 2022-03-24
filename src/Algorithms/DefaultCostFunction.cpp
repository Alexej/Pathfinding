#include "DefaultCostFunction.hpp"

#include "Node.hpp"
#include "InformedSearchAlgorithmHelpers.hpp"
#include "AlgorithmFunctionHelpers.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Helpers::infinity;
    using Pathfinding::Helpers::blocked;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Helpers::twoNodesDiagonal;
 
    DefaultCostFunction::DefaultCostFunction(int32_t diagonalMovementCost_, int32_t straightMovementCost_)
    : diagonalMovementCost(diagonalMovementCost_), straightMovementCost(straightMovementCost_) {}

    double DefaultCostFunction::calculate(const Node *from, const Node *to)
    {
        if (blocked(to))
        {
            return infinity();
        }
        
        /**
         * @brief does this make my graph bidirectional ?
         * 
         */
        return twoNodesDiagonal(from, to) ? diagonalMovementCost * to->factor : straightMovementCost * to->factor; 
    }
}