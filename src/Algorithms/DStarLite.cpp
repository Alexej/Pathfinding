#include "DStarLite.hpp"
#include <algorithm>
#include <limits>
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vec2.hpp"
#include "DiagonalHeuristic.hpp"
#include "ApplicationState.hpp"
#include "DStarLiteHelpers.hpp"
#include "ALatticeGraphWrapper.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ALatGrWrHelpers.hpp"
#include "ICostFunction.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::IHeuristic;
    using Pathfinding::Abstract::ICostFunction;
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::DStarLiteHelpers;
    using Pathfinding::Helpers::ALatGrWrHelpers;
    using Pathfinding::Abstract::ICostFunction;

    DStarLite::DStarLite(std::shared_ptr<ALatticeGraphWrapper> latticeGraphWrapperSPtr_)
        : latticeGraphWrapperSPtr(latticeGraphWrapperSPtr_) {}

    void DStarLite::setHeuristic(std::unique_ptr<IHeuristic> heuristicUPtr_)
    {
        heuristicUPtr = std::move(heuristicUPtr_);
    }

    void DStarLite::setCostFunction(std::unique_ptr<ICostFunction> costUPtr_)
    {
        costUPtr = std::move(costUPtr_);
    }

    void DStarLite::initialize()
    {
        kM = 0;
        sStart = latticeGraphWrapperSPtr->startNode();
        sLast = sStart;
        latticeGraphWrapperSPtr->goalNode()->rhs = 0;
        insertIntoQueueAndUpdateState(latticeGraphWrapperSPtr->goalNode());
    }

    void DStarLite::UpdateVertex(Node *u)
    {
        if (u != latticeGraphWrapperSPtr->goalNode())
        {
            u->rhs = getMinCG(u).first;
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
        auto k1New = std::min(s->g, s->rhs) + heuristicUPtr->calculate(sStart, s) + kM;
        auto k2New = std::min(s->g, s->rhs);
        s->key.k1 = k1New;
        s->key.k2 = k2New;
        return {k1New, k2New};
    }


    std::pair<double, Node *> DStarLite::getMinCG(Node *u)
    {
        auto succs = ALatGrWrHelpers::neighbors(latticeGraphWrapperSPtr, u);
        auto itr = std::min_element(succs.begin(), succs.end(),
        [this, &u](const Node *lhs, const Node *rhs)
        {
            return costThisFar(u,lhs) < costThisFar(u,rhs);
        });
        return {costThisFar(u, *itr), *itr};
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
        if (DStarLiteHelpers::blocked(u))
        {
            return u;
        }
        changeNodeState(u, NodeState::Visited);
        return u;
    }

    void DStarLite::removeFromQUeueAndUpdateState(Node *node)
    {
        U.remove(node);
        if (DStarLiteHelpers::blocked(node))
        {
            return;
        }
        changeNodeState(node, NodeState::Visited);
    }

    void DStarLite::insertIntoQueueAndUpdateKey(Node *node)
    {
        calculateKey(node);
        U.insert(node);
    }

    void DStarLite::insertIntoQueueAndUpdateState(Node *node)
    {
        insertIntoQueueAndUpdateKey(node);
        if (!node->visitedOnce)
        {
            node->visitedOnce = true;
        }
        if (DStarLiteHelpers::blocked(node))
        {
            return;
        }
        changeNodeState(node, NodeState::Frontier);
    }

    void DStarLite::updateNeighbors(Node *node)
    {
        for (auto &pred : ALatGrWrHelpers::neighbors(latticeGraphWrapperSPtr, node))
        {
            UpdateVertex(pred);
        }
    }

    void DStarLite::changeNodeState(Node *node, NodeState newState)
    {
        if (*node != *latticeGraphWrapperSPtr->goalNode() && *node != *latticeGraphWrapperSPtr->startNode())
        {
            node->state = newState;
        }
    }

    void DStarLite::computePath()
    {
        currentPath.clear();
        Node *currentNode = sStart;
        currentPath.push_back(currentNode);
        while (*currentNode != *latticeGraphWrapperSPtr->goalNode())
        {
            currentNode = getMinCG(currentNode).second;
            currentPath.push_back(currentNode);
        }
    }

    void DStarLite::moveStart()
    {
        if (!nodesChanged.empty())
        {
            kM = kM + heuristicUPtr->calculate(sLast, sStart);
            sLast = sStart;
            for (auto &node : nodesChanged)
            {
                UpdateVertex(node);
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

        if (*sStart == *latticeGraphWrapperSPtr->goalNode())
        {
            doneCallBack_();
            return;
        }
    }

    void DStarLite::moveStartToNextInPath()
    {
        Node *prevStart = sStart;
        sStart = getMinCG(sStart).second;
        latticeGraphWrapperSPtr->setStart(sStart->location);
        prevStart->state = NodeState::Visited;
    }

    void DStarLite::addChangedNode(Node *node)
    {
        for (auto &succ : ALatGrWrHelpers::neighbors(latticeGraphWrapperSPtr, node))
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

    double DStarLite::costThisFar(const Node * u, const Node * neighbor)
    {
        return costUPtr->calculate(u, neighbor) + neighbor->g;
    }
}