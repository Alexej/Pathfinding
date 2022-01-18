#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "GraphLocation.hpp"

using Pathfinding::Datastructures::NodeState;
using Pathfinding::Datastructures::GraphLocation;

namespace Pathfinding::Algorithms
{
    namespace
    {
        int32_t heuristic(const Node * from ,const Node * to)
        {
            int32_t dx = abs(from->location.width - to->location.width);
            int32_t dy = abs(from->location.height - to->location.height);
            return static_cast<int32_t>(dx * dx + dy * dy);
        }

        int32_t cost(const Node * from ,const Node * to)
        {
            int32_t dx = abs(from->location.width - to->location.width);
            int32_t dy = abs(from->location.height - to->location.height);
            return dx - dy == 0 ? 2 : 1;
        }
    }

    DStarLite::DStarLite(LatticeGraph * graph)
    : graphPtr(graph) {}

    void DStarLite::initialize()
    {
        kM = 0;
        sLast = graphPtr->startNode();
        graphPtr->goalNode()->rhs = 0;
        U.insert(graphPtr->goalNode(), calculateKey(graphPtr->goalNode()));
    }

    void DStarLite::UpdateVertex(Node * u)
    {
        if(u != graphPtr->goalNode()) { u->rhs = getMinCG(u); }
        if(U.contains(u)) { U.remove(u); }
        if(u->g != u->rhs) { U.insert(u, calculateKey(u)); }
    }

    void DStarLite::computeShortestPath()
    {
        while(U.topKey() < calculateKey(graphPtr->startNode()) 
        || graphPtr->startNode()->rhs != graphPtr->startNode()->g)
        {
            Key kOld = U.topKey();
            Node * u = U.popD();
            if(kOld < calculateKey(u))
            {
                U.insert(u, calculateKey(u));
            }
            else if(u->g > u->rhs)
            {
                u->g = u->rhs;
                for(auto & pred : succ(u))
                {
                    UpdateVertex(pred);
                }
            }
            else
            {
                u->g = std::numeric_limits<int32_t>::max();
                for(auto & pred : succ(u))
                {
                    UpdateVertex(pred);
                }
                UpdateVertex(u);
            }
        }
    }   

    Key DStarLite::calculateKey(Node * s)
    {
        return {std::min(s->g, s->rhs + heuristic(graphPtr->startNode(), s) + kM), std::min(s->g, s->rhs)};
    }

    int32_t DStarLite::getMinCG(Node * u)
    {
        auto succs = succ(u);
        int32_t min = cost(u,succs[0]) + succs[0]->g;
        for(uint32_t i = 1; i < succs.size(); ++i)
        {
            int32_t currentCost = cost(u,succs[i]) + succs[0]->g;
            if(min > currentCost)
            {
                min = currentCost;
            }
        }
        return min;
    }

    std::vector<Node *> DStarLite::succ(Node * u)
    {
        std::vector<Node *> succs;
        for(int32_t h = u->location.height - 1; h <= u->location.height + 1; ++h)
        {
            for(int32_t w = u->location.width - 1; w <= u->location.width + 1; ++w)
            {
                GraphLocation location(h,w);
                if(graphPtr->inBounds(location))
                {
                    if(u->location != location && u->state == NodeState::Free)
                    {
                        succs.push_back(graphPtr->node(location));
                    }
                }
            }
        }
        return succs;
    }
}