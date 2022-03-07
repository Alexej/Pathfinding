#include "AlgorithmFunctionHelpers.hpp"
#include "Node.hpp"


namespace Pathfinding::Helpers
{
    using namespace Pathfinding::Datastructures;
    bool twoNodesDiagonal(const Node * from, const Node * to)
    {
        int32_t dx = abs(from->location.width - to->location.width);
        int32_t dy = abs(from->location.height - to->location.height);
        return dx - dy == 0;
    }
}