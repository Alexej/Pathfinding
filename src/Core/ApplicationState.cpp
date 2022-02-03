#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    ApplicationState::ApplicationState()
    {
        showNodeInfo_ = false;
        stateChanged = false;
        autoStep_ = false;
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

    void ApplicationState::enableAutoStep()
    {
        autoStep_ = true;
    }

    void ApplicationState::disableAutoStep()
    {
        autoStep_ = false;
    }

    bool ApplicationState::autoStep()
    {
        return autoStep_;
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

    const Node * ApplicationState::nodeUnderCursor() const
    {
        return nodeUnderCursor_;
    }

    void ApplicationState::setNodeUnderCursor(const Node * node)
    {
        nodeUnderCursor_ = node;
    }
}