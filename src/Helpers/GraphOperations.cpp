#include "GraphOperations.hpp"
#include "Vector2.hpp"
#include "LatticeGraph.hpp"
#include "Node.hpp"
#include "ApplicationState.hpp"
#include "SFMLHelpers.hpp"
#include "DStarLite.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Core::State;

    GraphOperations::GraphOperations(ApplicationState * state_, DStarLite * dstar_, LatticeGraph * graph_, int32_t nodeSideLength_ )
    : applicationStatePtr(state_), dstarPtr(dstar_), graphPtr(graph_), nodeSideLength(nodeSideLength_){ }

    void GraphOperations::leftMouseButtonPressed(sf::Vector2i pos)
    {
        Vector2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (mappedCoordinates == graphPtr->startNode()->location && endPointsEvent)
        {
            currentMouseAction = MouseAction::SETTING_START;
        }
        else if (mappedCoordinates == graphPtr->goalNode()->location && endPointsEvent)
        {
            currentMouseAction = MouseAction::SETTING_GOAL;
        }
        else
        {
            currentMouseAction = MouseAction::BLOCKING_NODE;
            Vector2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
            if (graphPtr->inBounds(mappedCoordinates))
            {
                blockNodeAndNotifyDstarLiteIfRunning(mappedCoordinates);
            }
        }
    }

    void GraphOperations::rightMouseButtonPressed(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
        Vector2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (graphPtr->inBounds(mappedCoordinates))
        {
            clearNodeAndNotifyDstarLiteIfRunning(mappedCoordinates);
        }
    }

    void GraphOperations::mouseMoved(sf::Vector2i pos)
    {
        Vector2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
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
                blockNodeAndNotifyDstarLiteIfRunning(mappedCoordinates);
                break;
            case MouseAction::CLEARING_NODE:
                clearNodeAndNotifyDstarLiteIfRunning(mappedCoordinates);
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

    void GraphOperations::disableEnpointsEvent()
    {
        endPointsEvent = false;
    }
    void GraphOperations::enableEndPointsEvent()
    {
        endPointsEvent = true;
    }

    void GraphOperations::nodeUnderCursor(sf::Vector2i pos)
    {
        Vector2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if(graphPtr->inBounds(mappedCoordinates))
        {
            applicationStatePtr->setNodeUnderCursor(graphPtr->node(mappedCoordinates));
        }
    }

    void GraphOperations::blockNodeAndNotifyDstarLiteIfRunning(Vector2i mappedCoordinates)
    {
        if(graphPtr->node(mappedCoordinates)->state != NodeState::Blocked)
        {
            graphPtr->blockNode(mappedCoordinates);
            if(applicationStatePtr->currentState() == State::SEARCHING)
            {
                dstarPtr->addChangedNode(graphPtr->node(mappedCoordinates));
            }
        }
    }
    
    void GraphOperations::clearNodeAndNotifyDstarLiteIfRunning(Vector2i mappedCoordinates)
    {
        if(graphPtr->node(mappedCoordinates)->state != NodeState::Free)
        {
            graphPtr->clearNode(mappedCoordinates);
            if(applicationStatePtr->currentState() == State::SEARCHING)
            {
                dstarPtr->addChangedNode(graphPtr->node(mappedCoordinates));
            }
        }
    }
}