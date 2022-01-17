#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"

using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    struct ApplicationState
    {
        bool canRenderNodeInfo = true;
        bool renderNodeInfo = false;
        int32_t currentNumberOfNodeIndex = 0;
        int32_t currentNodeSideLength = NUMBER_OF_NODES_IN_ROW[currentNumberOfNodeIndex];
        bool numberOfNodesChanged = false;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
