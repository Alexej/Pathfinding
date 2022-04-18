#include "AStar.hpp"

#include <queue>
#include <vector>
#include <unordered_map>

#include "ALatGraphWr.hpp"
#include "PathfinderReturnType.hpp"
#include "IHeuristic.hpp"
#include "ICostFunction.hpp"
#include "Node.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "ILatticeGraph.hpp"
#include "InformedSearchFunctions.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::ICostFunction;
    using Pathfinding::Abstract::IHeuristic;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Datastructures::InformedSearchFunctions;
    using Pathfinding::Helpers::neighborsConst;

    namespace
    {
        template <typename KeyType, typename ValueType>
        ValueType getMapDefaultInf(const std::unordered_map<KeyType, ValueType> &map, const KeyType &key)
        {
            const auto it = map.find(key);
            return it != map.end() ? it->second : std::numeric_limits<ValueType>::infinity();
        }

        std::vector<const Node *> reconstructPath(std::unordered_map<const Node *, const Node *> cameFrom, const Node *current)
        {
            std::vector<const Node *> path;
            path.push_back(current);
            while (cameFrom.find(current) != cameFrom.end())
            {
                current = cameFrom[current];
                path.push_back(current);
            }
            return path;
        }
    }

    PathfinderReturnType AStar::calculatePath(const ALatGraphWr & graphWrapper, const InformedSearchFunctions & functions) const
    {
        std::vector<const Node*> nodesExpanded;
        std::priority_queue<QueueElement, std::vector<QueueElement>, AStarQueueComperator> openSet;
        std::unordered_map<const Node *, const Node *> cameFrom;
        std::unordered_map<const Node *, double> gScore;
        std::unordered_map<const Node *, double> fScore;

        gScore[graphWrapper.startNode()] = 0;
        fScore[graphWrapper.startNode()] = functions.heuristicUPtr->calculate(graphWrapper.startNode(), graphWrapper.goalNode());
        openSet.push({{fScore[graphWrapper.startNode()], gScore[graphWrapper.startNode()]}, graphWrapper.startNode()});

        while (!openSet.empty())
        {
            auto current = openSet.top().node;
            nodesExpanded.push_back(current);
            if (current == graphWrapper.goalNode())
            {
                return {true, reconstructPath(cameFrom, current), nodesExpanded};
            }
            openSet.pop();
            auto neighbors = neighborsConst(*graphWrapper.latGraphSPtr, current);
            for (auto neighbor : neighbors)
            {
                auto tentativeGscore = getMapDefaultInf(gScore, current) + functions.costUPtr->calculate(current, neighbor);
                if (tentativeGscore < getMapDefaultInf(gScore, neighbor))
                {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGscore;
                    fScore[neighbor] = tentativeGscore + functions.heuristicUPtr->calculate(neighbor, graphWrapper.goalNode());
                    openSet.push({{fScore[neighbor], gScore[neighbor]}, neighbor});
                }
            }
        }
        return {false, {}, {}};
    }
}
