#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vector2.hpp"
#include "DiagonalHeuristic.hpp"
#include "ApplicationState.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::AHeuristic;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;

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
            return dx - dy == 0 ? static_cast<int>(10 * sqrt(2)) : 10;
        }

        bool locallyConsistent(Node *node)
        {
            return node->g == node->rhs;
        }

        bool locallyOverconsistent(Node *node)
        {
            return node->g > node->rhs;
        }

        bool blocked(Node *node)
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
            auto succs = neighbors(u);
            if (!succs.empty())
            {
                u->rhs = getMinCG(u, succs).first;
            }
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

    void DStarLite::initialRun()
    {
        computeShortestPath();
        if (sStart->g == infinity())
        {
            noPathCallBack_();
            return;
        }
        computePath();
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
    std::pair<double, Node *> DStarLite::getMinCG(Node *u, std::vector<Node *> succs)
    {
        auto itr = std::min_element(succs.begin(), succs.end(), [&u](const Node *lhs, const Node *rhs)
                                    { return (cost(u, lhs) + lhs->g) < (cost(u, rhs) + rhs->g); });
        return {(cost(u, *itr) + (*itr)->g), *itr};
    }

    /**
     * @brief returns successors/predecessors of a node.
     *
     * @param node
     * @return std::vector<Node *>
     */
    std::vector<Node *> DStarLite::neighbors(Node *node)
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
                Vec2i location(h, w);
                if (graphPtr->inBounds(location))
                {
                    if (node->location != location && !blocked(graphPtr->node(location)))
                    {
                        nbors.push_back(graphPtr->node(location));
                    }
                }
            }
        }
        return nbors;
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
     * "After computeShortestPath() returns, one can then follow a shortest path from sStart
     * to sGoal by always moving from the current vertex s, starting at Sstart, to any successor s'
     * that minimizes c(s,s') + g(s') until sGoal is reached(ties can be broken arbitrarily).""
     */
    void DStarLite::computePath()
    {
        currentPath.clear();
        Node *currentNode = sStart;
        currentPath.push_back(currentNode);
        while (*currentNode != *graphPtr->goalNode())
        {
            auto succs = neighbors(currentNode);
            if (succs.empty())
            {
                noPathCallBack_();
                return;
            }
            currentNode = getMinCG(currentNode, succs).second;
            currentPath.push_back(currentNode);
        }
    }

    void DStarLite::moveStart()
    {
        if (!nodesChanged.empty())
        {
            kM = kM + heuristicPtr->calculate(sLast, sStart);
            sLast = sStart;
            for (auto &node : nodesChanged)
            {
                /**
                 * @brief Ignoring blocked nodes since they can't be tranversed,
                 * remove them from priority queue if present.
                 */
                if (blocked(node))
                {
                    if (U.contains(node))
                    {
                        U.remove(node);
                    }
                }
                else
                {
                    UpdateVertex(node);
                }
            }
            nodesChanged.clear();
            computeShortestPath();
        }

        if (sStart->g == infinity())
        {
            noPathCallBack_();
            return;
        }

        moveStartToNextInPath();
        computePath();

        if (*sStart == *graphPtr->goalNode())
        {
            doneCallBack_();
            return;
        }
    }

    void DStarLite::moveStartToNextInPath()
    {
        Node *prevStart = sStart;
        auto succs = neighbors(sStart);
        if (succs.empty())
        {
            return;
        }
        sStart = getMinCG(sStart, succs).second;
        graphPtr->setStart(sStart->location);
        prevStart->state = NodeState::Visited;
    }

    void DStarLite::addChangedNode(Node *node)
    {
        for (auto &succ : neighbors(node))
        {
            nodesChanged.insert(succ);
        }
        nodesChanged.insert(node);
    }

    void DStarLite::addDoneCallBack(std::function<void(void)> callBack)
    {
        doneCallBack_ = callBack;
    }

    void DStarLite::addNoPathCallBack(std::function<void(void)> callBack)
    {
        noPathCallBack_ = callBack;
    }

    std::vector<Node *> DStarLite::path() const
    {
        return currentPath;
    }
}