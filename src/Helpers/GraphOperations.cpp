#include "GraphOperations.hpp"
#include "Vector2.hpp"
#include "LatticeGraph.hpp"
#include "Node.hpp"
#include "ApplicationState.hpp"
#include "SFMLHelpers.hpp"
#include "DStarLite.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;

    GraphOperations::GraphOperations(ApplicationState *state_, LatticeGraph *graph_)
        : applicationStatePtr(state_), graphPtr(graph_), nodeSideLength(state_->dimension().currentNodeSideLength()) {}

    void GraphOperations::leftMouseButtonPressed(sf::Vector2i pos)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (mappedCoordinates == graphPtr->startNode()->location && endpointsEvents())
        {
            currentMouseAction = MouseAction::SETTING_START;
        }
        else if (mappedCoordinates == graphPtr->goalNode()->location && endpointsEvents())
        {
            currentMouseAction = MouseAction::SETTING_GOAL;
        }
        else
        {
            currentMouseAction = MouseAction::BLOCKING_NODE;
            if (graphPtr->inBounds(mappedCoordinates))
            {
                blockNodeAndNotifyAlgorithm(mappedCoordinates);
            }
        }
    }

    void GraphOperations::rightMouseButtonPressed(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (graphPtr->inBounds(mappedCoordinates))
        {
            clearNodeAndNotifyAlgorithm(mappedCoordinates);
        }
    }

    void GraphOperations::mouseMoved(sf::Vector2i pos)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (graphPtr->inBounds(mappedCoordinates))
        {
            switch (currentMouseAction)
            {
            case MouseAction::SETTING_START:
                graphPtr->setStart(mappedCoordinates);
                break;
            case MouseAction::SETTING_GOAL:
                graphPtr->setGoal(mappedCoordinates);
                break;
            case MouseAction::BLOCKING_NODE:
                blockNodeAndNotifyAlgorithm(mappedCoordinates);
                break;
            case MouseAction::CLEARING_NODE:
                clearNodeAndNotifyAlgorithm(mappedCoordinates);
                break;
            }
        }
    }

    void GraphOperations::mouseButtonReleased(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::IDLE;
    }

    void GraphOperations::resize(int32_t nodeSideLength_)
    {
        nodeSideLength = nodeSideLength_;
    }

    void GraphOperations::disableEndpointsEvent()
    {
        endPointsEvents_ = false;
    }
    void GraphOperations::enableEndPointsEvent()
    {
        endPointsEvents_ = true;
    }

    void GraphOperations::disableObsticlesEvents()
    {
        obsticlesEvents_ = false;
    }
    void GraphOperations::enableObsticlesEvents()
    {
        obsticlesEvents_ = true;
    }

    bool GraphOperations::endpointsEvents() const
    {
        return endPointsEvents_;
    }
    bool GraphOperations::obsticlesEvents() const
    {
        return obsticlesEvents_;
    }

    void GraphOperations::nodeUnderCursor(sf::Vector2i pos)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (graphPtr->inBounds(mappedCoordinates))
        {
            applicationStatePtr->setNodeUnderCursor(graphPtr->node(mappedCoordinates));
        }
    }

    void GraphOperations::blockNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        // Ignore operations without node state change or when events deactivated
        if (graphPtr->node(mappedCoordinates)->state != NodeState::Blocked && obsticlesEvents())
        {
            graphPtr->blockNode(mappedCoordinates);
            if (applicationStatePtr->currentState() == State::SEARCHING)
            {
                edgeChangeCallBack(graphPtr->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::clearNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        if (graphPtr->node(mappedCoordinates)->state != NodeState::Free && obsticlesEvents())
        {
            graphPtr->clearNode(mappedCoordinates);
            if (applicationStatePtr->currentState() == State::SEARCHING)
            {
                edgeChangeCallBack(graphPtr->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::addEdgeChangeCallBack(std::function<void(PDNode * node)> callBack)
    {
        edgeChangeCallBack = callBack;
    }
}