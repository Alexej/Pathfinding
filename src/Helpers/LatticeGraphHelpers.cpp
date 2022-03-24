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
    using namespace Pathfinding::Datastructures;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Core::RandomIntegers;

    void ILatticeGraphHelpers::initRandomGraph(ILatticeGraph & latticeGraphSPtr, RandomIntegers & ri)
    {
        iterateOverLatticeGraph(latticeGraphSPtr, [&](PDNode *node, int32_t h, int32_t w)
                                        {
            if (node->state == NodeState::Free && ri.getRandomInteger() % 3 == 0)
            {
                node->state = NodeState::Blocked;
            } });
    }

    std::vector<Node *>
    ILatticeGraphHelpers::neighbors(ILatticeGraph & latticeGraphSPtr, Node *node_)
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
                if (latticeGraphSPtr.inBounds(coord) && node_->location != coord)
                {
                    nbors.push_back(latticeGraphSPtr.node(coord));
                }
            }
        }
        return nbors;
    }

    void ILatticeGraphHelpers::blockNode(ILatticeGraph & ilatticeGraph, Vec2i location)
    {
        if (ilatticeGraph.node(location)->state != NodeState::Start &&
            ilatticeGraph.node(location)->state != NodeState::Goal)
        {
            ilatticeGraph.node(location)->state = NodeState::Blocked;
        }
    }

    void ILatticeGraphHelpers::clearNode(ILatticeGraph & ilatticeGraph, Vec2i location)
    {
        if (ilatticeGraph.node(location)->state == NodeState::Blocked)
        {
            if (ilatticeGraph.node(location)->visitedOnce)
            {
                ilatticeGraph.node(location)->state = NodeState::Visited;
            }
            else
            {
                ilatticeGraph.node(location)->state = NodeState::Free;
            }
        }
    }

    void ILatticeGraphHelpers::iterateOverLatticeGraphConst(const ILatticeGraph & ilatticeGraph,
                                                   std::function<void(const Node *node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < ilatticeGraph.height(); ++h)
        {
            for (int32_t w = 0; w < ilatticeGraph.width(); ++w)
            {
                func(ilatticeGraph.node(Vec2i(h, w)), h, w);
            }
        }
    }

    void ILatticeGraphHelpers::iterateOverLatticeGraph(ILatticeGraph & ilatticeGraph,
                                           std::function<void(Node *node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < ilatticeGraph.height(); ++h)
        {
            for (int32_t w = 0; w < ilatticeGraph.width(); ++w)
            {
                func(ilatticeGraph.node(Vec2i(h, w)), h, w);
            }
        }
    }
}

#endif /* B15A85B1_6958_4A28_833B_2236EE9D4AE5 */
