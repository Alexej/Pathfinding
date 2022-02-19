#include "LatticeGraphWrapper.hpp"
#include "ALatticeGraphWrapper.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Abstract::ILatticeGraph;

    LatticeGraphWrapper::LatticeGraphWrapper(std::unique_ptr<ILatticeGraph> latticeGraphUPtr)
        : ALatticeGraphWrapper(std::move(latticeGraphUPtr))
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

    void LatticeGraphWrapper::setGoal(Vec2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            goalNodePtr->state = NodeState::Free;
            goalNodePtr = node(location);
            goalNodePtr->state = NodeState::Goal;
        }
    }

    void LatticeGraphWrapper::setStart(Vec2i location)
    {
        if (node(location)->state != NodeState::Goal && node(location)->state != NodeState::Blocked)
        {
            startNodePtr->state = NodeState::Free;
            startNodePtr = node(location);
            startNodePtr->state = NodeState::Start;
        }
    }

    void LatticeGraphWrapper::blockNode(Vec2i location)
    {
        if (node(location)->state != NodeState::Start && node(location)->state != NodeState::Goal)
        {
            node(location)->state = NodeState::Blocked;
        }
    }

    void LatticeGraphWrapper::clearNode(Vec2i location)
    {
        if (node(location)->state == NodeState::Blocked)
        {
            if (node(location)->visitedOnce)
            {
                node(location)->state = NodeState::Visited;
            }
            else
            {
                node(location)->state = NodeState::Free;
            }
        }
    }

    void LatticeGraphWrapper::resetEndpoints()
    {
        int32_t heightI = static_cast<int32_t>(latGraphUPtr->height());
        int32_t widthI = static_cast<int32_t>(latGraphUPtr->width());
        goalNodePtr = node(Vec2i(heightI - 1, widthI - 1));
        startNodePtr = node(Vec2i(0,0));
        goalNodePtr->state = NodeState::Goal;
        startNodePtr->state = NodeState::Start;
    }

    void LatticeGraphWrapper::initRandomGraph()
    {
        for (int32_t h = 0; h < latGraphUPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latGraphUPtr->width(); ++w)
            {
                if (node(Vec2i(h,w))->state == NodeState::Free && rand() % 3 == 0)
                {
                    node(Vec2i(h,w))->state = NodeState::Blocked;
                }
            }
        }
    }

    std::vector<Node *> LatticeGraphWrapper::neighbors(Node *node_)
    {
        std::vector<Node *> nbors;
        int32_t hFrom = node_->location.height - 1;
        int32_t hTo = node_->location.height + 1;
        int32_t wFrom = node_->location.width - 1;
        int32_t wTo = node_->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                if (latGraphUPtr->inBounds(h, w) && node_->location != Vec2i(h, w))
                {
                    nbors.push_back(node(Vec2i(h,w)));
                }
            }
        }
        return nbors;
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
}