#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    using Pathfinding::Datastructures::Node;

    ApplicationState::ApplicationState(GraphDimension dim, AlgorithmStepSpeed speed)
    : dimension(dim), stepSpeed(speed)
    {
        showNodeInfo = false;
        stateChanged = false;
        autoStep = false;
        showPath = true;
        showPathLines = true;
        runAStar = false;
        currentState = State::READY;
        showAStarPath = true;
    }
}