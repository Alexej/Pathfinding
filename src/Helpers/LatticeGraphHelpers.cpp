#ifndef B15A85B1_6958_4A28_833B_2236EE9D4AE5
#define B15A85B1_6958_4A28_833B_2236EE9D4AE5

#include "LatticeGraphHelpers.hpp"

#include "ILatticeGraph.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"
#include "Vec2.hpp"
#include "RandomIntegers.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;

    void LatticeGraphHelpers::initRandomGraph(std::shared_ptr<ILatticeGraph> latticeGraphSPtr, RandomIntegers & ri)
    {
        iterateOverLatticeGraph(latticeGraphSPtr, [&](PDNode *node, int32_t h, int32_t w)
                                        {
            if (node->state == NodeState::Free && ri.getRandomInteger() % 3 == 0)
            {
                node->state = NodeState::Blocked;
            } });
    }

    std::vector<Node *>
    LatticeGraphHelpers::neighbors(std::shared_ptr<ILatticeGraph> latticeGraphSPtr, Node *node_)
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
                auto coord = Vec2i(h, w);
                if (latticeGraphSPtr->inBounds(coord) && node_->location != coord)
                {
                    nbors.push_back(latticeGraphSPtr->node(coord));
                }
            }
        }
        return nbors;
    }

    void LatticeGraphHelpers::blockNode(std::shared_ptr<ILatticeGraph> latticeGraphSPtr, Vec2i location)
    {
        if (latticeGraphSPtr->node(location)->state != NodeState::Start &&
            latticeGraphSPtr->node(location)->state != NodeState::Goal)
        {
            latticeGraphSPtr->node(location)->state = NodeState::Blocked;
        }
    }

    void LatticeGraphHelpers::clearNode(std::shared_ptr<ILatticeGraph> latticeGraphSPtr, Vec2i location)
    {
        if (latticeGraphSPtr->node(location)->state == NodeState::Blocked)
        {
            if (latticeGraphSPtr->node(location)->visitedOnce)
            {
                latticeGraphSPtr->node(location)->state = NodeState::Visited;
            }
            else
            {
                latticeGraphSPtr->node(location)->state = NodeState::Free;
            }
        }
    }

    void LatticeGraphHelpers::iterateOverLatticeGraphConst(const std::shared_ptr<ILatticeGraph> latticeGraphSPtr,
                                                   std::function<void(const Node *node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < latticeGraphSPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latticeGraphSPtr->width(); ++w)
            {
                func(latticeGraphSPtr->node(Vec2i(h, w)), h, w);
            }
        }
    }

    void LatticeGraphHelpers::iterateOverLatticeGraph(std::shared_ptr<ILatticeGraph> latticeGraphSPtr,
                                           std::function<void(Node *node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < latticeGraphSPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latticeGraphSPtr->width(); ++w)
            {
                func(latticeGraphSPtr->node(Vec2i(h, w)), h, w);
            }
        }
    }
}

#endif /* B15A85B1_6958_4A28_833B_2236EE9D4AE5 */
