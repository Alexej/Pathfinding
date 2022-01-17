#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"

using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    struct ApplicationState
    {
        const bool canRenderNodeInfo = NODE_SIDE_LENGTH >= MINIMUM_NODE_SIDE_LENGHT_FOR_NODE_INFO;
        bool renderNodeInfo = false;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
