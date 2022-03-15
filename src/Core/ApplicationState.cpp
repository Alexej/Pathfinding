#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    using Pathfinding::Datastructures::Node;

    ApplicationState::ApplicationState(GraphDimension dim)
    : dimension(dim)
    {
    }

    bool ApplicationState::algorithmFinished() const
    {
        return currentState == AlgorithmState::FOUND_PATH || currentState == AlgorithmState::NO_PATH;
    }
}