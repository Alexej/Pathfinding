#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    ApplicationState::ApplicationState()
    {
        showNodeInfo_ = false;
        stateChanged = false;
        currentState_ = State::READY;
    }


    bool ApplicationState::showNodeInfo() const
    {
        return showNodeInfo_;
    }

    void ApplicationState::enableNodeInfo()
    {
        showNodeInfo_ = true;
    }

    void ApplicationState::disableNodeInfo()
    {
        showNodeInfo_ = false;
    }

    void ApplicationState::setState(State state)
    {
        currentState_ = state;
    }

    State ApplicationState::currentState() const
    {
        return currentState_;
    } 

    GraphDimension & ApplicationState::dimension()
    {
        return dim;
    }
}