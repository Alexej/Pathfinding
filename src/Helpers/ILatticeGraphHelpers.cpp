#ifndef B15A85B1_6958_4A28_833B_2236EE9D4AE5
#define B15A85B1_6958_4A28_833B_2236EE9D4AE5

#include "ILatticeGraphHelpers.hpp"

#include "ILatticeGraph.hpp"
#include "Vec2.hpp"
#include "RandomIntegers.hpp"
#include "ApplicationState.hpp"

namespace Pathfinding::Helpers
{
    using namespace Pathfinding::Datastructures;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Core::RandomIntegers;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Datastructures::Node;


    void initRandomGraph(ILatticeGraph & latticeGraphSPtr, RandomIntegers & ri)
    {
        iterateOverLatticeGraph(latticeGraphSPtr, [&](Node *node, int32_t h, int32_t w)
                                        {
            if (node->state == NodeState::Free && ri.getRandomInteger() % 3 == 0)
            {
                node->state = NodeState::Blocked;
            } });
    }

    std::vector<Node *>
    neighbors(ILatticeGraph & latticeGraph, const Node *node)
    {
        std::vector<Node *> nbors;
        int32_t hFrom = node->location.height - 1;
        int32_t hTo = node->location.height + 1;
        int32_t wFrom = node->location.width - 1;
        int32_t wTo = node->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                auto coord = Vec2i(h, w);
                if (latticeGraph.inBounds(coord) && node->location != coord)
                {
                    nbors.push_back(latticeGraph.node(coord));
                }
            }
        }
        return nbors;
    }

    std::vector<const Node *> 
    neighborsConst(ILatticeGraph & LatticeGraph, const Node *node)
    {
        std::vector<const Node *> nbors;
        int32_t hFrom = node->location.height - 1;
        int32_t hTo = node->location.height + 1;
        int32_t wFrom = node->location.width - 1;
        int32_t wTo = node->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                auto coord = Vec2i(h, w);
                if (LatticeGraph.inBounds(coord) && node->location != coord)
                {
                    nbors.push_back(LatticeGraph.node(coord));
                }
            }
        }
        return nbors;
    }


    void blockNode(ILatticeGraph & ilatticeGraph, Vec2i location)
    {
        if (ilatticeGraph.node(location)->state != NodeState::Start &&
            ilatticeGraph.node(location)->state != NodeState::Goal)
        {
            ilatticeGraph.node(location)->state = NodeState::Blocked;
        }
    }

    void clearNode(ILatticeGraph & ilatticeGraph, Vec2i location)
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
}

#endif /* B15A85B1_6958_4A28_833B_2236EE9D4AE5 */
