#include "GraphOperations.hpp"

#include "Vec2.hpp"
#include "LatticeGraph.hpp"
#include "Node.hpp"
#include "ApplicationState.hpp"
#include "SFMLHelpers.hpp"
#include "DStarLite.hpp"
#include "ALatGraphWr.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "MouseData.hpp"
#include "Constants.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using namespace Pathfinding::Datastructures;

    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using Pathfinding::Helpers::mapMouseToGraphCoordinates;
    using Pathfinding::Events::MouseData;

    GraphOperations::GraphOperations(ApplicationState *appStateSPtr_,
                                     std::shared_ptr<ALatGraphWr> latGraphWrapperUPtr_)
        : latGraphWrapperUPtr(latGraphWrapperUPtr_), 
          appStateSPtr(appStateSPtr_),
          nodeSideLength(appStateSPtr_->dimension.currentNodeSideLength()) 
          {}

    void GraphOperations::leftMouseButtonPressed(MouseData mouseData)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (mappedCoordinates == latGraphWrapperUPtr->startNode()->location && endpointsEvents())
        {
            currentMouseAction = MouseAction::SETTING_START;
        }
        else if (mappedCoordinates == latGraphWrapperUPtr->goalNode()->location && endpointsEvents())
        {
            currentMouseAction = MouseAction::SETTING_GOAL;
        }
        else
        {
            currentMouseAction = MouseAction::BLOCKING_NODE;
            if (latGraphWrapperUPtr->latGraphSPtr->inBounds(mappedCoordinates))
            {
                blockNodeAndNotifyAlgorithm(mappedCoordinates);
            }
        }
    }

    void GraphOperations::rightMouseButtonPressed(MouseData mouseData)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (latGraphWrapperUPtr->latGraphSPtr->inBounds(mappedCoordinates))
        {
            clearNodeAndNotifyAlgorithm(mappedCoordinates);
        }
    }


    void GraphOperations::setStart(Vec2i  mappedCoordinates)
    {
        if(latGraphWrapperUPtr->latGraphSPtr->node(mappedCoordinates)->state == NodeState::Free)
        {
            latGraphWrapperUPtr->setStart(mappedCoordinates);
        }
    }   

    void GraphOperations::mouseMoved(MouseData mouseData)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (latGraphWrapperUPtr->latGraphSPtr->inBounds(mappedCoordinates))
        {
            switch (currentMouseAction)
            {
            case MouseAction::IDLE:
                break;
            case MouseAction::SETTING_START:
                setStart(mappedCoordinates);
                break;
            case MouseAction::SETTING_GOAL:
                latGraphWrapperUPtr->setGoal(mappedCoordinates);
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

    void GraphOperations::mouseButtonReleased(MouseData mouseData)
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

    void GraphOperations::disableObsticlesAndScrollEvents()
    {
        obsticlesEvents_ = false;
    }
    void GraphOperations::enableObsticlesAndScrollEvents()
    {
        obsticlesEvents_ = true;
    }

    bool GraphOperations::endpointsEvents() const
    {
        return endPointsEvents_;
    }
    bool GraphOperations::obsticlesAndScrollEvents() const
    {
        return obsticlesEvents_;
    }

    void GraphOperations::nodeUnderCursor(MouseData mouseData)
    {
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (graph->inBounds(mappedCoordinates))
        {
            appStateSPtr->nodeUnderCursor = graph->node(mappedCoordinates);
        }
    }

    void GraphOperations::blockNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        // Ignore operations without node state change or when events deactivated
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        if (graph->node(mappedCoordinates)->state != NodeState::Blocked && obsticlesAndScrollEvents())
        {
            ILatticeGraphHelpers::blockNode(*graph, mappedCoordinates);
            if (appStateSPtr->currentState == AlgorithmState::SEARCHING)
            {
                edgeChangeCallBack(graph->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::clearNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        if (graph->node(mappedCoordinates)->state != NodeState::Free && obsticlesAndScrollEvents())
        {
            ILatticeGraphHelpers::clearNode(*graph, mappedCoordinates);
            if (appStateSPtr->currentState == AlgorithmState::SEARCHING)
            {
                edgeChangeCallBack(graph->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::addEdgeChangeCallBack(std::function<void(PDNode *node)> callBack)
    {
        edgeChangeCallBack = callBack;
    }

    void GraphOperations::incrementNodeFactor(Vec2i mappedCoordinates)
    {
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        if(graph->node(mappedCoordinates)->factor < MAX_COST_FACTOR)
        {   
            graph->node(mappedCoordinates)->factor += 1;
            edgeChangeCallBack(graph->node(mappedCoordinates));
        }
    }

    void GraphOperations::decrementNodeFactor(Vec2i mappedCoordinates)
    {
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        if(graph->node(mappedCoordinates)->factor > MIN_COST_FACTOR)
        {
            graph->node(mappedCoordinates)->factor -= 1;
            edgeChangeCallBack(graph->node(mappedCoordinates));
        }
    }

    void GraphOperations::mouseWheelMoved(MouseData mouseData)
    {
        if(appStateSPtr->currentMouseWheelEvent == MouseWheelEvent::Zoom)
        {
            return;
        }
        auto graph = latGraphWrapperUPtr->latGraphSPtr;
        if(obsticlesAndScrollEvents())
        {
            Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
            if(!latGraphWrapperUPtr->latGraphSPtr->inBounds(mappedCoordinates))
            {
                return;
            }
            if(mouseData.wheelDelta > 0)
            {
                incrementNodeFactor(mappedCoordinates);
            }
            else
            {
                decrementNodeFactor(mappedCoordinates);
            }
        }
    }
}