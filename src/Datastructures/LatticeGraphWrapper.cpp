#include "LatticeGraphWrapper.hpp"
#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::ILatticeGraph;

    LatticeGraphWrapper::LatticeGraphWrapper(std::shared_ptr<ILatticeGraph> latticeGraphUPtr)
        : ALatGraphWr(latticeGraphUPtr)
    {
        resetEndpoints();
    }

    void LatticeGraphWrapper::resize(int32_t height, int32_t width)
    {
        latGraphSPtr->resize(height, width);
        resetEndpoints();
    }

    const Node *LatticeGraphWrapper::startNode() const
    {
        return startNodePtr;
    }

    const Node *LatticeGraphWrapper::goalNode() const
    {
        return goalNodePtr;
    }

    Node *LatticeGraphWrapper::startNode()
    {
        return startNodePtr;
    }

    Node *LatticeGraphWrapper::goalNode()
    {
        return goalNodePtr;
    }

    void LatticeGraphWrapper::resetEndpoints()
    {
        int32_t heightI = static_cast<int32_t>(latGraphSPtr->height());
        int32_t widthI = static_cast<int32_t>(latGraphSPtr->width());
        goalNodePtr = latGraphSPtr->node(Vec2i(heightI - 1, widthI - 1));
        startNodePtr = latGraphSPtr->node(Vec2i(0, 0));
        goalNodePtr->state = NodeState::Goal;
        startNodePtr->state = NodeState::Start;
    }

    void LatticeGraphWrapper::setGoal(Vec2i location)
    {
        if (latGraphSPtr->node(location)->state == NodeState::Free)
        {
            goalNodePtr->state = NodeState::Free;
            goalNodePtr = latGraphSPtr->node(location);
            goalNodePtr->state = NodeState::Goal;
        }
    }

    void LatticeGraphWrapper::setStart(Vec2i location)
    {
        if (latGraphSPtr->node(location)->state != NodeState::Blocked)
        {
            startNodePtr->state = NodeState::Free;
            startNodePtr = latGraphSPtr->node(location);
            startNodePtr->state = NodeState::Start;
        }
    }

    void LatticeGraphWrapper::changeNodeState(Node *node, NodeState newState)
    {
        if (!node->visitedOnce)
        {
            node->visitedOnce = true;
        }
        if (*node != *goalNode() && *node != *startNode() && node->state != NodeState::Blocked)
        {
            node->state = newState;
        }
    }
}