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

namespace Pathfinding::Helpers
{
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Helpers::ALatGrWrHelpers;

    GraphOperations::GraphOperations(ApplicationState * appStateSPtr_, 
                                     std::shared_ptr<ALatticeGraphWrapper> latGraphWrapperUPtr_)
        : appStateSPtr(appStateSPtr_), 
        latGraphWrapperUPtr(latGraphWrapperUPtr_), 
        nodeSideLength(appStateSPtr_->dimension.currentNodeSideLength()) {}

    void GraphOperations::leftMouseButtonPressed(sf::Vector2i pos)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
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

    void GraphOperations::rightMouseButtonPressed(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            clearNodeAndNotifyAlgorithm(mappedCoordinates);
        }
    }

    void GraphOperations::mouseMoved(sf::Vector2i pos)
    {
        Vec2i mappedCoordinates = mapMouseToGraphCoordinates(pos, nodeSideLength);
        if (latGraphWrapperUPtr->inBounds(mappedCoordinates))
        {
            switch (currentMouseAction)
            {
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
}