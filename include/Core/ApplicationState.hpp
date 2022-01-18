#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"

using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    struct ApplicationState
    {
        explicit ApplicationState(int32_t numberOfNodes)
        {
            currentNumberOfNodeIndex = numberOfNodes;
            currentNodeSideLength = NUMBER_OF_NODES_IN_ROW[numberOfNodes];
        }
        
        bool canRenderNodeInfo = true;
        bool renderNodeInfo = false;
        bool numberOfNodesChanged = false;

        int32_t currentNumberOfNodeIndex;
        int32_t currentNodeSideLength;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
