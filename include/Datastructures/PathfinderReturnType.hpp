#ifndef BCF096EA_6E8E_4825_B635_8EA161991348
#define BCF096EA_6E8E_4825_B635_8EA161991348

#include <vector>

#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    struct PathfinderReturnType
    {
        bool pathFound = false; 
        std::vector<const Node *> path;
        std::vector<const Node *> nodesExpandedAll;
    };
}

#endif /* BCF096EA_6E8E_4825_B635_8EA161991348 */
