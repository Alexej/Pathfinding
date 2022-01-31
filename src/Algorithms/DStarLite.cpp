#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vector2.hpp"
#include "EuclidianHeuristic.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vector2i;

    namespace
    {
        double cost(const Node *from, const Node *to)
        {
            int32_t dx = abs(from->location.width - to->location.width);
            int32_t dy = abs(from->location.height - to->location.height);
            return dx - dy == 0 ? 1 : 1;
        }
    }

    DStarLite::DStarLite(LatticeGraph *graph)
        : graphPtr(graph) {}

    void DStarLite::setHeuristic(std::shared_ptr<AHeuristic> heuristicPtr_)
    {
        heuristicPtr = heuristicPtr_;
    }

    void DStarLite::initialize()
    {
        kM = 0;
        sStart = graphPtr->startNode();
        graphPtr->goalNode()->rhs = 0;
        U.insert(graphPtr->goalNode(), calculateKey(graphPtr->goalNode()));
    }

    void DStarLite::UpdateVertex(Node *u)
    {
        if (u != graphPtr->goalNode())
        {
            u->rhs = getMinCG(u).first;
        }
        if (U.contains(u))
        {
            U.remove(u);
        }
        if (u->g != u->rhs)
        {
            U.insert(u, calculateKey(u));
        }
    }

    void DStarLite::computeShortestPath()
    {
        while (U.topKey() < calculateKey(sStart) || sStart->rhs != sStart->g)
        {
            Key kOld = U.topKey();
            Node *u = U.popD();
            if (kOld < calculateKey(u))
            {
                U.insert(u, calculateKey(u));
            }
            else if (u->g > u->rhs)
            {
                u->g = u->rhs;
                for (auto &pred : succ(u))
                {
                    UpdateVertex(pred);
                }
            }
            else
            {
                u->g = std::numeric_limits<double>::infinity();
                for (auto &pred : succ(u))
                {
                    UpdateVertex(pred);
                }
                UpdateVertex(u);
            }
        }
    }

    Key DStarLite::calculateKey(Node *s)
    {
        auto k1New = std::min(s->g, s->rhs) + heuristicPtr->calculate(sStart, s) + kM;
        auto k2New = std::min(s->g, s->rhs);
        s->key.k1 = k1New;
        s->key.k2 = k2New;
        return {k1New, k2New};
    }

    /**
     * @brief returns minimum c(s,s') + g(s') and its node of all successors of u
     * 
     * @param u 
     * @return std::pair<int32_t, Node *> 
     */
    std::pair<double, Node *> DStarLite::getMinCG(Node *u)
    {
        auto succs = succ(u);
        double min = cost(u, succs[0]) + succs[0]->g;
        Node * currentNode = succs[0];
        for (uint32_t i = 1; i < succs.size(); ++i)
        {
            double currentCost = cost(u, succs[i]) + succs[i]->g;
            if (min >= currentCost)
            {
                min = currentCost;
                currentNode = succs[i];
            }
        }
        return {min, currentNode};
    }

    std::vector<Node *> DStarLite::succ(Node *u)
    {
        std::vector<Node *> succs;
        int32_t hFrom = u->location.height - 1;
        int32_t hTo = u->location.height + 1;
        int32_t wFrom = u->location.width - 1;
        int32_t wTo = u->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                Vector2i location(h, w);
                if (graphPtr->inBounds(location))
                {
                    if (u->location != location && graphPtr->node(location)->state != NodeState::Blocked)
                    {
                        succs.push_back(graphPtr->node(location));
                    }
                }
            }
        }
        return succs;
    }

    void DStarLite::setPathInGraph()
    {
        for(auto & node : currentPath)
        {
            node->state = NodeState::Path;
        }
    }

    void DStarLite::clearPathInGraph()
    {
        for(auto & node : currentPath)
        {
            node->state = NodeState::Free;
        }
    }


    void DStarLite::reset()
    {
        sStart = nullptr;
        U.reset();
        kM = 0;
        currentPath.clear();
    }   


    /**
     * @brief 
     * "After computeShortestPath() returns, one can then follow a shortest path from Sstart 
     * to Sgoal by always moving from the current vertex s, starting at Sstart, to any successor s' 
     * that minimizes c(s,s') + g(s') until Sgoal is reached(ties can be broken arbitrarily).""
     */
    void DStarLite::computePath()
    {
        Node * currentNode = sStart;
        while(true)
        {
            currentNode = getMinCG(currentNode).second;
            if(currentNode == graphPtr->goalNode())
            {
                break;
            }
            currentPath.push_back(currentNode);
        }
    }
}