#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"


namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    
    enum class AlgorithmState{ READY, SEARCHING, DONE};
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
        bool stateChanged = false;

        int32_t numberOfNodeIndex;
        int32_t nodeSideLength;

        AlgorithmState algState = AlgorithmState::READY;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
