#include "LatticeGraphWrapper.hpp"
#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"
#include "IMazeGenerator.hpp"
#include "LatticeGraphHelpers.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Abstract::IMazeGenerator;
    using Pathfinding::Helpers::ILatticeGraphHelpers;

    namespace
    {
        Node *getFreeNode(std::vector<Node *> vec)
        {
            for (auto possibleFreeNode : vec)
            {
                if (possibleFreeNode->state == NodeState::Free)
                {
                    return possibleFreeNode;
                }
            }
            return nullptr;
        }
    }

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

        auto possibleGoal = latGraphSPtr->node(Vec2i(heightI - 1, widthI - 1));
        auto possibleStart = latGraphSPtr->node(Vec2i(0, 0));

        std::vector<Node *> possibleGoals;
        std::vector<Node *> possibleStarts;

        possibleGoals.push_back(possibleGoal);
        possibleStarts.push_back(possibleStart);

        for (auto node : ILatticeGraphHelpers::neighbors(*latGraphSPtr, possibleGoal))
        {
            possibleGoals.push_back(node);
        }

        for (auto node : ILatticeGraphHelpers::neighbors(*latGraphSPtr, possibleStart))
        {
            possibleStarts.push_back(node);
        }

        goalNodePtr = getFreeNode(possibleGoals);
        startNodePtr = getFreeNode(possibleStarts);

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

    void LatticeGraphWrapper::changeNodeStateWhenNodeFreeOrVisited(Node *node, NodeState newState)
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

    void LatticeGraphWrapper::removeEndpointsFromGraph()
    {
        endpointsSet_ = false;
        goalNodePtr->state = NodeState::Free;
        startNodePtr->state = NodeState::Free;
        goalNodePtr = nullptr;
        startNodePtr = nullptr;
    }

    void LatticeGraphWrapper::addEndpointsToGraph()
    {
        endpointsSet_ = true;
        resetEndpoints();
    }
}