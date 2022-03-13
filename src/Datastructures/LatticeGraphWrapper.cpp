#include "LatticeGraphWrapper.hpp"
#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::ILatticeGraph;

    LatticeGraphWrapper::LatticeGraphWrapper(std::unique_ptr<ILatticeGraph> latticeGraphUPtr)
        : ALatGraphWr(std::move(latticeGraphUPtr))
    {
        resetEndpoints();
    }

    void LatticeGraphWrapper::resize(int32_t height, int32_t width)
    {
        latGraphUPtr->resize(height, width);
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
        int32_t heightI = static_cast<int32_t>(latGraphUPtr->height());
        int32_t widthI = static_cast<int32_t>(latGraphUPtr->width());
        goalNodePtr = node(Vec2i(heightI - 1, widthI - 1));
        startNodePtr = node(Vec2i(0, 0));
        goalNodePtr->state = NodeState::Goal;
        startNodePtr->state = NodeState::Start;
    }

    bool LatticeGraphWrapper::inBounds(Vec2i location) const
    {
        return latGraphUPtr->inBounds(location.height, location.width);
    }

    std::size_t LatticeGraphWrapper::width() const
    {
        return latGraphUPtr->width();
    }

    std::size_t LatticeGraphWrapper::height() const
    {
        return latGraphUPtr->height();
    }

    void LatticeGraphWrapper::setGoal(Vec2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            goalNodePtr->state = NodeState::Free;
            goalNodePtr = node(location);
            goalNodePtr->state = NodeState::Goal;
        }
    }

    void LatticeGraphWrapper::setStart(Vec2i location, bool dontSetStarState)
    {
        if(node(location)->state != NodeState::Blocked)
        {
            if (node(location)->state != NodeState::Goal)
            {
                startNodePtr->state = NodeState::Free;
                startNodePtr = node(location);
                startNodePtr->state = NodeState::Start;
            }
            else if(node(location)->state == NodeState::Goal && dontSetStarState)
            {
                startNodePtr->state = NodeState::Free;
                startNodePtr = node(location);
            }
        }
    }
}