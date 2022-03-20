#ifndef BDFBF26D_BD08_4957_A301_B1BF962441A7
#define BDFBF26D_BD08_4957_A301_B1BF962441A7

#include <vector>
#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    struct PathfinderReturnType;
    struct PathfinderCache
    {
        std::vector<Node *> currentPath;
        std::vector<std::vector<Node *>> nodesExpandedAll;

        void cache(PathfinderReturnType aStarReturnType);

        void reset();

    };  
}


#endif /* BDFBF26D_BD08_4957_A301_B1BF962441A7 */
