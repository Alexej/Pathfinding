#include "DStarLite.hpp"

#include <algorithm>
#include <limits>

#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vec2.hpp"
#include "DiagonalHeuristic.hpp"
#include "ApplicationState.hpp"
#include "DStarLiteHelpers.hpp"
#include "ALatGraphWr.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ALatGrWrHelpers.hpp"
#include "ICostFunction.hpp"
#include "Constants.hpp"
#include "PathfinderReturnType.hpp"


namespace Pathfinding::Algorithms
{
    using namespace Pathfinding::Helpers;
    using Pathfinding::Constants::DONT_SET_START_STATE;
    using Pathfinding::Abstract::IHeuristic;
    using Pathfinding::Abstract::ICostFunction;
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::ALatGrWrHelpers;
    using Pathfinding::Abstract::ICostFunction;

    namespace
    {
        int32_t flush(int32_t & num)
        {
            int32_t tmp = num;
            num = 0;
            return tmp;
        }
    }

    DStarLite::DStarLite(std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr_)
        : latticeGraphWrapperSPtr(latticeGraphWrapperSPtr_) {}

    void DStarLite::initialize()
    {
        kM = 0;
        sStart = latticeGraphWrapperSPtr->startNode();
        sLast = sStart;
        latticeGraphWrapperSPtr->goalNode()->rhs = 0;
        insertIntoQueueAndUpdateStateAndKey(latticeGraphWrapperSPtr->goalNode());
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
        if (!locallyConsistent(u))
        {
            insertIntoQueueAndUpdateStateAndKey(u);
        }
    }

    PathfinderReturnType DStarLite::initialRun()
    {
        computeShortestPath();
        if (sStart->g == infinity())
        {
            noPathCallBack_();
            return {false, {}, 0};
        }
        return computePath();
    }

    void DStarLite::computeShortestPath()
    {
        nodexExpanded = 0;
        while (U.topKey() < calculateKey(sStart) || !locallyConsistent(sStart))
        {
            Key kOld = U.topKey();
            nodexExpanded += 1;
            Node *u = popFromQueueAndUpdateState();
            if (kOld < calculateKey(u))
            {
                insertIntoQueueAndUpdateStateAndKey(u);
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
        auto pseudoG = std::min(s->g, s->rhs);
        auto k1New = pseudoG + heuristicUPtr->calculate(sStart, s) + kM;
        auto k2New = pseudoG;
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
        nodesChanged.clear();
        nodexExpanded = 0;
    }

    Node *DStarLite::popFromQueueAndUpdateState()
    {
        Node *u = U.pop();
        if (blocked(u))
        {
            return u;
        }
        changeNodeState(u, NodeState::Visited);
        return u;
    }

    void DStarLite::removeFromQUeueAndUpdateState(Node *node)
    {
        U.remove(node);
        if (blocked(node))
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

    void DStarLite::insertIntoQueueAndUpdateStateAndKey(Node *node)
    {
        insertIntoQueueAndUpdateKey(node);
        if (!node->visitedOnce)
        {
            node->visitedOnce = true;
        }
        if (blocked(node))
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

    PathfinderReturnType DStarLite::computePath()
    {
        std::vector<Node *> path;
        Node *currentNode = sStart;
        path.push_back(currentNode);
        while (*currentNode != *latticeGraphWrapperSPtr->goalNode())
        {
            currentNode = getMinCG(currentNode).second;
            path.push_back(currentNode);
        }
        return {true, path, flush(nodexExpanded)};
    }

    PathfinderReturnType DStarLite::moveStart()
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

        if (sStart->g == infinity())
        {
            noPathCallBack_();
            return {false, {}, 0};
        }
        moveStartToNextInPath();

        auto result = computePath();

        if (*sStart == *latticeGraphWrapperSPtr->goalNode())
        {
            doneCallBack_();    
        }
        return result;
    }

    void DStarLite::moveStartToNextInPath()
    {
        Node *prevStart = sStart;
        sStart = getMinCG(sStart).second;
        latticeGraphWrapperSPtr->setStart(sStart->location, DONT_SET_START_STATE);
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

    double DStarLite::costThisFar(const Node * u, const Node * neighbor)
    {
        return costUPtr->calculate(u, neighbor) + neighbor->g;
    }
}