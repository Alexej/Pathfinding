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
            numberOfNodeIndex = numberOfNodes;
            nodeSideLength = NUMBER_OF_NODES_IN_ROW[numberOfNodes];
        }
        
        bool canRenderNodeInfo = true;
        bool renderNodeInfo = false;
        bool numberOfNodesChanged = false;

        int32_t numberOfNodeIndex;
        int32_t nodeSideLength;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
