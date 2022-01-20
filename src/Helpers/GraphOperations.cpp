#include "GraphOperations.hpp"
#include "GraphLocation.hpp"
#include "LatticeGraph.hpp"
#include "Node.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::GraphLocation;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;

    namespace
    {
        GraphLocation mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength)
        {
            int32_t faH = pos.y / currentSideLength;
            int32_t faW = pos.x / currentSideLength;
            return {faH, faW};
        }
    }

    GraphOperations::GraphOperations(LatticeGraph * graph_, int32_t nodeSideLength_ )
    : graphPtr(graph_), nodeSideLength(nodeSideLength_){ }

    void GraphOperations::leftMouseButtonPressed(sf::Vector2i pos)
    {
        GraphLocation mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
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
        }
    }

    void GraphOperations::rightMouseButtonPressed(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
    }

    void GraphOperations::mouseMoved(sf::Vector2i pos)
    {
        GraphLocation mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
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
                graphPtr->blockNode(mappedCoordinates);
                break;
            case MouseAction::CLEARING_NODE:
                graphPtr->clearNode(mappedCoordinates);
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
}