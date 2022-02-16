#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vector2.hpp"
#include "DiagonalHeuristic.hpp"
#include "ApplicationState.hpp"
#include "DStarLiteHelpers.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::AHeuristic;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::DStarLiteHelpers;
    using Pathfinding::Datastructures::neighbors;

    namespace
    {
        double cost(const Node *from, const Node *to)
        {
            int32_t dx = abs(from->location.width - to->location.width);
            int32_t dy = abs(from->location.height - to->location.height);
            return dx - dy == 0 ? static_cast<int>(10 * sqrt(2)) : 10;
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
        insertIntoQueueAndUpdateState(graphPtr->goalNode());
    }

    void DStarLite::UpdateVertex(Node *u)
    {
        if (u != graphPtr->goalNode())
        {
            auto succs = neighbors(*graphPtr, u);
            if (!succs.empty())
            {
                u->rhs = getMinCG(u, succs).first;
            }
        }
        if (U.contains(u))
        {
            removeFromQUeueAndUpdateState(u);
        }
        if (!DStarLiteHelpers::locallyConsistent(u))
        {
            insertIntoQueueAndUpdateState(u);
        }
    }

    void DStarLite::initialRun()
    {
        computeShortestPath();
        if (sStart->g == DStarLiteHelpers::infinity())
        {
            noPathCallBack_();
            return;
        }
        computePath();
    }

    void DStarLite::computeShortestPath()
    {
        while (U.topKey() < calculateKey(sStart) || !DStarLiteHelpers::locallyConsistent(sStart))
        {
            Key kOld = U.topKey();
            Node *u = popFromQueueAndUpdateState();
            if (kOld < calculateKey(u))
            {
                insertIntoQueueAndUpdateState(u);
            }
            else if (DStarLiteHelpers::locallyOverconsistent(u))
            {
                u->g = u->rhs;
                updateNeighbors(u);
            }
            else
            {
                u->g = DStarLiteHelpers::infinity();
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
        changeNodeState(u, NodeState::Visited);
        return u;
    }

    void DStarLite::removeFromQUeueAndUpdateState(Node *node)
    {
        U.remove(node);
        changeNodeState(node, NodeState::Visited);
    }


    void DStarLite::insertIntoQueueAndUpdateKey(Node * node)
    {
        calculateKey(node);
        U.insert(node);
    }

    void DStarLite::insertIntoQueueAndUpdateState(Node *node)
    {
        insertIntoQueueAndUpdateKey(node);
        if(!node->visitedOnce)
        {
            node->visitedOnce = true;
        }
        changeNodeState(node, NodeState::Frontier);
    }

    void DStarLite::updateNeighbors(Node *node)
    {
        for (auto &pred : neighbors(*graphPtr, node))
        {
            UpdateVertex(pred);
        }
    }

    void DStarLite::changeNodeState(Node *node, NodeState newState)
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
            auto succs = neighbors(*graphPtr, currentNode);
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
                 * @brief Ignoring blocked nodes since they can't be traversed,
                 * remove them from priority queue if present.
                 */
                if (DStarLiteHelpers::blocked(node))
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

        if (sStart->g == DStarLiteHelpers::infinity())
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
        auto succs = neighbors(*graphPtr, sStart);
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
        for (auto &succ : neighbors(*graphPtr, node))
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