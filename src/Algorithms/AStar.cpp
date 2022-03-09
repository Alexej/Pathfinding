#include "AStar.hpp"

#include <queue>
#include <vector>
#include <unordered_map>
#include "ALatticeGraphWrapper.hpp"
#include "AStarReturnType.hpp"
#include "IHeuristic.hpp"
#include "ICostFunction.hpp"
#include "Node.hpp"
#include "ALatGrWrHelpers.hpp"
#include "ILatticeGraph.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::ICostFunction;
    using Pathfinding::Abstract::IHeuristic;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Datastructures::AStarReturnType;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Helpers::ALatGrWrHelpers;

    namespace
    {
        template<typename KeyType, typename ValueType>
        ValueType getMapDefaultInf(const std::unordered_map<KeyType, ValueType> & map, const KeyType & key)
        {
            const auto it = map.find(key);
            return it != map.end() ?  it->second : std::numeric_limits<ValueType>::infinity();
        }

        std::vector<Node*> reconstructPath(std::unordered_map<Node *, Node *> cameFrom, Node * current)
        {
            std::vector<Node*> path;
            path.push_back(current);
            while(cameFrom.find(current) != cameFrom.end())
            {
                current = cameFrom[current];
                path.push_back(current);
            }
            return path;
        }
    }

    AStarReturnType AStar::calculatePath(std::shared_ptr<ALatticeGraphWrapper> graphWrapper)
    {
        int32_t nodesExpanded = 0;
        std::priority_queue<QueueElement, std::vector<QueueElement>, AStarQueueComperator> openSet;
        std::unordered_map<Node *, Node *> cameFrom;
        std::unordered_map<Node *, double> gScore;
        std::unordered_map<Node *, double> fScore;

        gScore[graphWrapper->startNode()] = 0;
        fScore[graphWrapper->startNode()] = heuristicUPtr->calculate(graphWrapper->startNode(), graphWrapper->goalNode());
        openSet.push({{fScore[graphWrapper->startNode()],gScore[graphWrapper->startNode()]}, graphWrapper->startNode()});

        while(!openSet.empty())
        {
            auto current = openSet.top().node;
            if(current == graphWrapper->goalNode())
            {
                return {true, reconstructPath(cameFrom, current), nodesExpanded};
            }
            openSet.pop();
            for(auto neighbor : ALatGrWrHelpers::neighbors(graphWrapper, current))
            {
                auto tentativeGscore = getMapDefaultInf(gScore, current) + costUPtr->calculate(current, neighbor);
                if(tentativeGscore < getMapDefaultInf(gScore, neighbor))
                {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGscore;
                    fScore[neighbor] = tentativeGscore + heuristicUPtr->calculate(neighbor, graphWrapper->goalNode());
                    openSet.push({{fScore[neighbor],gScore[neighbor]}, neighbor});
                }
            }
        }
        return {false, {}, 0};
    }
}