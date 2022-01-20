#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    
    enum class AlgorithmState{ READY, SEARCHING, DONE};
    struct ApplicationState
    {
        ApplicationState()
        {
            renderNodeInfo = false;
            stateChanged = false;
            numberOfNodesChanged = false;  
            algState = AlgorithmState::READY;
        }
        
        GraphDimension dim;
        bool renderNodeInfo;
        bool stateChanged;
        bool numberOfNodesChanged;
        AlgorithmState algState;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
