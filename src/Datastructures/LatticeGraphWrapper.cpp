#include "LatticeGraphWrapper.hpp"

#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"
#include "IMazeGenerator.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "CppHelpers.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Abstract::IMazeGenerator;
    using Pathfinding::Helpers::neighbors;
    using Pathfinding::Helpers::isNullptr;

    namespace
    {
        std::optional<Node *> getFreeNode(std::vector<Node *> vec)
        {
            for (auto possibleFreeNode : vec)
            {
                if (possibleFreeNode->state == NodeState::Free)
                {
                    return possibleFreeNode;
                }
            }
            return {};
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

    const Node * LatticeGraphWrapper::startNode() const
    {
        return startNodePtr;
    }

    const Node * LatticeGraphWrapper::goalNode() const
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

        setEndpointsToNullPtr();

        if(auto startNode = getFreeNodeFrom3By3(possibleStart); startNode)
        {
            startNodePtr = *startNode;
            startNodePtr->state = NodeState::Start;
        }

        if(auto goalNode = getFreeNodeFrom3By3(possibleGoal); goalNode)
        {
            goalNodePtr = *goalNode;
            goalNodePtr->state = NodeState::Goal;
        }

        if(!endpointsInitialized())
        {
            throw std::exception("Error when initializing endpoints");
        }
    }

    bool LatticeGraphWrapper::endpointsInitialized() const
    {
        return !isNullptr(startNodePtr) && !isNullptr(goalNodePtr);
    }


    void LatticeGraphWrapper::setEndpointsToNullPtr()
    {
        startNodePtr = nullptr;
        goalNodePtr = nullptr;
    }

    std::optional<Node *> LatticeGraphWrapper::getFreeNodeFrom3By3(Node * node)
    {
        std::vector<Node *> possibleNodes;
        possibleNodes.push_back(node);
        for (auto node : neighbors(*latGraphSPtr, node))
        {
            possibleNodes.push_back(node);
        }
        return getFreeNode(possibleNodes);
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

    void LatticeGraphWrapper::reset()
    {
        latGraphSPtr->reset();
        resetEndpoints();
    }
}