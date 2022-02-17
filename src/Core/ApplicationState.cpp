#include "ApplicationState.hpp"

namespace Pathfinding::Core
{
    using Pathfinding::Datastructures::Node;

    ApplicationState::ApplicationState()
    {
        showNodeInfo_ = false;
        stateChanged = false;
        autoStep_ = false;
        path_ = true;
        pathLines_ = true;
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

    bool ApplicationState::autoStep() const
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

    GraphDimension &ApplicationState::dimension()
    {
        return dim;
    }

    const Node *ApplicationState::nodeUnderCursor() const
    {
        return nodeUnderCursor_;
    }

    void ApplicationState::setNodeUnderCursor(const Node *node)
    {
        nodeUnderCursor_ = node;
    }

    bool ApplicationState::showPathLines() const
    {
        return pathLines_;
    }
    bool ApplicationState::showPath() const
    {
        return path_;
    }

    void ApplicationState::enablePath()
    {
        path_ = true;
    }
    void ApplicationState::disablePath()
    {
        path_ = false;
    }

    void ApplicationState::enablePathLines()
    {
        pathLines_ = true;
    }
    void ApplicationState::disablePathLines()
    {
        pathLines_ = false;
    }

    void ApplicationState::setAlgorithmStepSpeed(AlgorithmStepSpeed algoStepSpeed)
    {
        stepSpeed = algoStepSpeed;
    }

    AlgorithmStepSpeed & ApplicationState::algorithmStepSpeed()
    {
        return stepSpeed;
    }
}