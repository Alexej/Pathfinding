#ifndef BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4
#define BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4

#include "Node.hpp"

namespace Pathfinding::Helpers
{
    inline std::string getSubstrBeforeChar(std::string string, char character)
    {
        return string.substr(0, string.find(character, 0));
    }

    inline std::vector<Pathfinding::Datastructures::Node *> 
    flushVector(std::vector<Pathfinding::Datastructures::Node *> & nodesExpanded)
    {
        auto tmpNodesExpanded = nodesExpanded;
        nodesExpanded.clear();
        return tmpNodesExpanded;
    }
}

#endif /* BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4 */
