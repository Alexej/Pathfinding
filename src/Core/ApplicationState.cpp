#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    ApplicationState::ApplicationState()
    {
        showNodeInfo_ = false;
        stateChanged = false;
        currentState_ = State::READY;
    }

    int32_t ApplicationState::currentNumberOfNodesI() const
    {
        return dim.currentNumberOfNodesIndex();
    }
    bool ApplicationState::canShowNodeInfo() const
    {
        return dim.canShowNodeInfo();
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

    void ApplicationState::setCurrentNumberOfNodesIndex(int32_t index)
    {
        dim.setCurrentNumberOfNodesIndex(index);
    }

    int32_t ApplicationState::currentNodeSideLength() const
    {
        return dim.currentNodeSideLength();
    }

    int32_t ApplicationState::currentNumberOfNodesIndex() const
    {
        return dim.currentNumberOfNodesIndex();
    }
}