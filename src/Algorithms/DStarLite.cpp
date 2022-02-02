#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vector2.hpp"
#include "DiagonalHeuristic.hpp"

#include <iostream>

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vector2i;

    namespace
    {
        double infinity()
        {
            return std::numeric_limits<double>::infinity();
        }

        double cost(const Node *from, const Node *to)
        {
            int32_t dx = abs(from->location.width - to->location.width);
            int32_t dy = abs(from->location.height - to->location.height);
            return dx - dy == 0 ? sqrt(2) : 1;
        }

        bool locallyConsistent(Node *node)
        {
            return node->g == node->rhs;
        }

        bool locallyOverconsistent(Node *node)
        {
            return node->g > node->rhs;
        }

        bool blocked(Node * node)
        {
            return node->state == NodeState::Blocked;
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
        sLast = sStart;
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
            removeFromQUeueAndUpdateState(u);
        }
        if (!locallyConsistent(u))
        {
            insertIntoQueueAndUpdateState(u);
        }
    }

    void DStarLite::computeShortestPath()
    {
        while (U.topKey() < calculateKey(sStart) || !locallyConsistent(sStart))
        {
            Key kOld = U.topKey();
            Node *u = popFromQueueAndUpdateState();
            if (kOld < calculateKey(u))
            {
                insertIntoQueueAndUpdateState(u);
            }
            else if (locallyOverconsistent(u))
            {
                u->g = u->rhs;
                updateNeighbors(u);
            }
            else
            {
                u->g = infinity();
                updateNeighbors(u);
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
     * @brief returns minimum cost(s,s') + g(s') and its node of all successors of u
     *
     * @param u
     * @return std::pair<int32_t, Node *>
     */
    std::pair<double, Node *> DStarLite::getMinCG(Node *u)
    {
        auto succs = neighbors(u);
        auto itr = std::min_element(succs.begin(), succs.end(), [&u](const Node * lhs, const Node * rhs)
        {
             return (cost(u, lhs) + lhs->g) < (cost(u, rhs) + rhs->g);
        });
        return {(cost(u, *itr) + (*itr)->g), *itr};
    }

    /**
     * @brief same as succ and pred.
     *
     * @param u
     * @return std::vector<Node *>
     */
    std::vector<Node *> DStarLite::neighbors(Node *u)
    {
        std::vector<Node *> nbors;
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
                        nbors.push_back(graphPtr->node(location));
                    }
                }
            }
        }
        return nbors;
    }

    void DStarLite::setPathInGraph()
    {
        for (auto &node : currentPath)
        {
            changeState(node, NodeState::Path);
        }
    }

    void DStarLite::clearPathInGraph()
    {
        for (auto &node : currentPath)
        {
            if(node->state != NodeState::Blocked)
            {
                changeState(node, NodeState::Visited);
            }
        }
    }

    void DStarLite::reset()
    {
        sStart = nullptr;
        sLast = nullptr;
        U.reset();
        kM = 0;
        currentPath.clear();
        nodesChanged.clear();
    }

    Node *DStarLite::popFromQueueAndUpdateState()
    {
        Node *u = U.popD();
        changeState(u, NodeState::Visited);
        return u;
    }

    void DStarLite::removeFromQUeueAndUpdateState(Node *node)
    {
        U.remove(node);
        changeState(node, NodeState::Visited);
    }

    void DStarLite::insertIntoQueueAndUpdateState(Node *node)
    {
        U.insert(node, calculateKey(node));
        changeState(node, NodeState::Frontier);
    }

    void DStarLite::updateNeighbors(Node *node)
    {
        for (auto &pred : neighbors(node))
        {
            UpdateVertex(pred);
        }
    }

    void DStarLite::changeState(Node *node, NodeState newState)
    {
        if (*node != *graphPtr->goalNode() && *node != *graphPtr->startNode())
        {
            node->state = newState;
        }
    }

    /**
     * @brief
     * "After computeShortestPath() returns, one can then follow a shortest path from Sstart
     * to Sgoal by always moving from the current vertex s, starting at Sstart, to any successor s'
     * that minimizes c(s,s') + g(s') until Sgoal is reached(ties can be broken arbitrarily).""
     */
    void DStarLite::computePath()
    {
        currentPath.clear();
        Node *currentNode = sStart;
        if (*sStart == *graphPtr->goalNode())
        {
            return;
        }
        while (true)
        {
            currentNode = getMinCG(currentNode).second;
            if (*currentNode == *graphPtr->goalNode())
            {
                break;
            }
            currentPath.push_back(currentNode);
        }
    }

    void DStarLite::moveAgent()
    {
        clearPathInGraph();
        if (*sStart != *graphPtr->goalNode())
        {
            if (sStart->g == infinity())
            {
                printf("no path");
                return;
            }
            if (!nodesChanged.empty())
            {
                kM = kM + heuristicPtr->calculate(sLast, sStart);
                sLast = sStart;
                for (auto &node : nodesChanged)
                {
                    if(blocked(node))
                    {
                        if(U.contains(node))
                        {
                            U.remove(node);
                        }
                    }
                    /**
                     * @brief We need to check whether the node is blocked or not
                     *  because its state can change while in nodesChanged vector(trough adjacent blocked nodes).
                     */
                    else
                    {
                        UpdateVertex(node); 
                        changeState(node, NodeState::Recalculated);
                    }
                }
                nodesChanged.clear();
                computeShortestPath();
            }
            moveStartToNextInPath();
            computePath();
            setPathInGraph();
        }
        else
        {
            printf("Found path");
        }
    }

    void DStarLite::moveStartToNextInPath()
    {
        Node *prevStart = sStart;
        sStart = getMinCG(sStart).second;
        graphPtr->setStart(sStart->location);
        prevStart->state = NodeState::Visited;
    }

    void DStarLite::addChangedNode(Node *node)
    {
        for(auto & succ : neighbors(node))
        {
            nodesChanged.insert(succ);
        }
        nodesChanged.insert(node);
    }
}