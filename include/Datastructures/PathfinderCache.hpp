#ifndef BDFBF26D_BD08_4957_A301_B1BF962441A7
#define BDFBF26D_BD08_4957_A301_B1BF962441A7

#include <vector>
#include "PathfinderReturnType.hpp"
#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    struct PathfinderCache
    {
        std::vector<Node *> currentPath;
        std::vector<int32_t> nodesExpandedAll;

        void cache(PathfinderReturnType aStarReturnType)
        {
            currentPath = aStarReturnType.path;
            nodesExpandedAll.push_back(aStarReturnType.nodesExpanded);
        }

        void reset()
        {
            currentPath.clear();
            nodesExpandedAll.clear();
        }
    };  
}


#endif /* BDFBF26D_BD08_4957_A301_B1BF962441A7 */
