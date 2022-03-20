#ifndef BCF096EA_6E8E_4825_B635_8EA161991348
#define BCF096EA_6E8E_4825_B635_8EA161991348

#include <vector>

#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    struct PathfinderReturnType
    {
        PathfinderReturnType(bool pathFound_, std::vector<Pathfinding::Datastructures::Node *> path_, std::vector<Node *> nodesExpanded_)
            : pathFound(pathFound_),
              path(path_)
              ,nodesExpandedAll(nodesExpanded_)
        {}

        bool pathFound = false; 
        std::vector<Pathfinding::Datastructures::Node *> path;
        std::vector<Node *> nodesExpandedAll;

    };
}

#endif /* BCF096EA_6E8E_4825_B635_8EA161991348 */
