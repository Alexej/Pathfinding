#ifndef BCF096EA_6E8E_4825_B635_8EA161991348
#define BCF096EA_6E8E_4825_B635_8EA161991348

#include <vector>

#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    struct PathfinderReturnType
    {
        PathfinderReturnType(bool pathFound_, std::vector<Pathfinding::Datastructures::Node *> path_, int32_t nodesExpanded_)
            : pathFound(pathFound_),
              path(path_),
              nodesExpanded(nodesExpanded_)
        {}

        bool pathFound = false; 
        std::vector<Pathfinding::Datastructures::Node *> path;
        int32_t nodesExpanded = 0;
    };
}

#endif /* BCF096EA_6E8E_4825_B635_8EA161991348 */
