#include "DStarLite.hpp"

#include <algorithm>
#include <limits>

#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Vec2.hpp"
#include "DiagonalHeuristic.hpp"
#include "ApplicationState.hpp"
#include "InformedSearchAlgorithmHelpers.hpp"
#include "ALatGraphWr.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "ICostFunction.hpp"
#include "Constants.hpp"
#include "PathfinderReturnType.hpp"
#include "CppHelpers.hpp"


namespace Pathfinding::Algorithms
{
    using namespace Pathfinding::Helpers;
    using Pathfinding::Abstract::IHeuristic;
    using Pathfinding::Abstract::ICostFunction;
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Datastructures::Key; 
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::flushVector;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using Pathfinding::Abstract::ICostFunction;


    DStarLite::DStarLite(std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr_)
    : AIncrementalInformedAlgorithm(latticeGraphWrapperSPtr_) {}

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
            noPathCallBack();
            return {false, {}, {}};
        }
        return computePath();
    }

    void DStarLite::computeShortestPath()
    {
        nodexExpanded.clear();
        while (U.topKey() < calculateKey(sStart) || !locallyConsistent(sStart))
        {
            Key kOld = U.topKey();
            Node *u = popFromQueueAndUpdateState();
            nodexExpanded.push_back(u);
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

    Key DStarLite::calculateKey(const Node *s) const
    {
        auto pseudoG = std::min(s->g, s->rhs);
        auto k1 = pseudoG + heuristicUPtr->calculate(sStart, s) + kM;
        auto k2 = pseudoG;
        return {k1, k2};
    }

    void DStarLite::updateKey(Node *s)
    {
        s->key = calculateKey(s);
    }

    std::pair<double, Node *> DStarLite::getMinCG(Node *u)
    {
        auto succs = ILatticeGraphHelpers::neighbors(*latticeGraphWrapperSPtr->latGraphSPtr, u);
        auto itr = std::ranges::min_element(succs,
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
        nodexExpanded.clear();
    }

    Node *DStarLite::popFromQueueAndUpdateState()
    {
        Node *u = U.pop();
        latticeGraphWrapperSPtr->changeNodeStateWhenNodeFreeOrVisited(u, NodeState::Visited);
        return u;
    }

    void DStarLite::removeFromQUeueAndUpdateState(Node *node)
    {
        U.remove(node);
        latticeGraphWrapperSPtr->changeNodeStateWhenNodeFreeOrVisited(node, NodeState::Visited);
    }
    
    void DStarLite::insertIntoQueueAndUpdateStateAndKey(Node *node)
    {
        insertIntoQueueAndUpdateKey(node);
        latticeGraphWrapperSPtr->changeNodeStateWhenNodeFreeOrVisited(node, NodeState::Frontier);
    }

    void DStarLite::insertIntoQueueAndUpdateKey(Node *node)
    {
        updateKey(node);
        U.insert(node);
    }


    void DStarLite::updateNeighbors(Node *node)
    {
        for (auto &pred : ILatticeGraphHelpers::neighbors(*latticeGraphWrapperSPtr->latGraphSPtr, node))
        {
            UpdateVertex(pred);
        }
    }


    PathfinderReturnType DStarLite::computePath()
    {
        std::vector<const Node *> path;
        Node *currentNode = sStart;
        path.push_back(currentNode);
        while (*currentNode != *latticeGraphWrapperSPtr->goalNode())
        {
            currentNode = getMinCG(currentNode).second;
            path.push_back(currentNode);
        }
        return {true, path, flushVector(nodexExpanded)};
    }

    PathfinderReturnType DStarLite::followingRun()
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
            noPathCallBack();
            return {false, {}, {}};
        }
        moveStartToNextInPath();

        auto result = computePath();

        if (*sStart == *latticeGraphWrapperSPtr->goalNode())
        {
            doneCallBack();    
        }
        return result;
    }

    void DStarLite::moveStartToNextInPath()
    {
        Node *prevStart = sStart;
        sStart = getMinCG(sStart).second;
        latticeGraphWrapperSPtr->setStart(sStart->location);
        latticeGraphWrapperSPtr->changeNodeStateWhenNodeFreeOrVisited(prevStart, NodeState::Visited);
    }

    void DStarLite::addChangedNode(Node *node)
    {
        for (auto &succ : ILatticeGraphHelpers::neighbors(*latticeGraphWrapperSPtr->latGraphSPtr, node))
        {
            nodesChanged.insert(succ);
        }
        nodesChanged.insert(node);
    }

    double DStarLite::costThisFar(const Node * u, const Node * neighbor)
    {
        return costUPtr->calculate(u, neighbor) + neighbor->g;
    }
}