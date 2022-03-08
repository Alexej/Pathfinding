#include "GraphOperations.hpp"
#include "Vec2.hpp"
#include "LatticeGraph.hpp"
#include "Node.hpp"
#include "ApplicationState.hpp"
#include "SFMLHelpers.hpp"
#include "DStarLite.hpp"
#include "ALatticeGraphWrapper.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ALatGrWrHelpers.hpp"
#include "MouseData.hpp"
#include "Constants.hpp"

namespace Pathfinding::Helpers
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::ALatGrWrHelpers;
    using Pathfinding::Events::MouseData;

    GraphOperations::GraphOperations(ApplicationState *appStateSPtr_,
                                     std::shared_ptr<ALatticeGraphWrapper> latGraphWrapperUPtr_)
        : latGraphWrapperUPtr(latGraphWrapperUPtr_), 
          appStateSPtr(appStateSPtr_),
          nodeSideLength(appStateSPtr_->dimension.currentNodeSideLength()) {}

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
            if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
            {
                blockNodeAndNotifyAlgorithm(mappedCoordinates);
            }
        }
    }

    void GraphOperations::rightMouseButtonPressed(MouseData mouseData)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            clearNodeAndNotifyAlgorithm(mappedCoordinates);
        }
    }

    void GraphOperations::mouseMoved(MouseData mouseData)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            switch (currentMouseAction)
            {
            case MouseAction::IDLE:
                break;
            case MouseAction::SETTING_START:
                latGraphWrapperUPtr->setStart(mappedCoordinates);
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

    void GraphOperations::nodeUnderCursor(MouseData mouseData)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            appStateSPtr->nodeUnderCursor = latGraphWrapperUPtr->node(mappedCoordinates);
        }
    }

    void GraphOperations::blockNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        // Ignore operations without node state change or when events deactivated
        if (latGraphWrapperUPtr->node(mappedCoordinates)->state != NodeState::Blocked && obsticlesEvents())
        {
            ALatGrWrHelpers::blockNode(latGraphWrapperUPtr, mappedCoordinates);
            if (appStateSPtr->currentState == State::SEARCHING)
            {
                edgeChangeCallBack(latGraphWrapperUPtr->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::clearNodeAndNotifyAlgorithm(Vec2i mappedCoordinates)
    {
        if (latGraphWrapperUPtr->node(mappedCoordinates)->state != NodeState::Free && obsticlesEvents())
        {
            ALatGrWrHelpers::clearNode(latGraphWrapperUPtr, mappedCoordinates);
            if (appStateSPtr->currentState == State::SEARCHING)
            {
                edgeChangeCallBack(latGraphWrapperUPtr->node(mappedCoordinates));
            }
        }
    }

    void GraphOperations::addEdgeChangeCallBack(std::function<void(PDNode *node)> callBack)
    {
        edgeChangeCallBack = callBack;
    }

    void GraphOperations::mouseWheelMoved(MouseData mouseData)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(mouseData.cursorPosition, nodeSideLength);
        if(!latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            return;
        }
        if(mouseData.wheelDelta > 0)
        {
            if(latGraphWrapperUPtr->node(mappedCoordinates)->factor < MAX_COST_FACTOR)
            {   
                latGraphWrapperUPtr->node(mappedCoordinates)->factor += 1;
                edgeChangeCallBack(latGraphWrapperUPtr->node(mappedCoordinates));
            }
        }
        else
        {
            if(latGraphWrapperUPtr->node(mappedCoordinates)->factor > MIN_COST_FACTOR)
            {
                latGraphWrapperUPtr->node(mappedCoordinates)->factor -= 1;
                edgeChangeCallBack(latGraphWrapperUPtr->node(mappedCoordinates));
            }
        }
    }
}