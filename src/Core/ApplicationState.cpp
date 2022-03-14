#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    using Pathfinding::Datastructures::Node;

    ApplicationState::ApplicationState(GraphDimension dim, AlgorithmStepSpeed speed)
    : dimension(dim), stepSpeed(speed)
    {
    }

    bool ApplicationState::algorithmFinished() const
    {
        return currentState == State::FOUND_PATH || currentState == State::NO_PATH;
    }
}