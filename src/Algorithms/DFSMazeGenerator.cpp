#include "DFSMazeGenerator.hpp"
#include "ILatticeGraph.hpp"
#include "LatticeGraph.hpp"
#include <type_traits>
#include "Node.hpp"
#include "Vec2.hpp"
#include "OtherHelpers.hpp"
#include "RandomIntegers.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Core::RandomIntegers;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::inVector;
    using Pathfinding::Helpers::isEven;
    using Pathfinding::Helpers::pop;

    namespace
    {
        Vec2i getWallPosition(Node *from, Node *to)
        {
            Vec2i wallPosition;
            if (from->location.height == to->location.height)
            {
                wallPosition = {from->location.height, std::min(from->location.width, to->location.width) + 1};
            }
            else
            {
                wallPosition = {std::min(from->location.height, to->location.height) + 1, to->location.width};
            }
            return wallPosition;
        }
    }

    void DFSMazeGenerator::generate(ILatticeGraph &latGraph, RandomIntegers & ri)
    {
        setWalls(latGraph);
        DFS(Vec2i(0, 0), latGraph, ri);
    }

    void DFSMazeGenerator::connectNodes(PAIlatticeGraph &latGraph, PDNode *from, PDNode *to)
    {
        Vec2i wallPos = getWallPosition(from, to);
        latGraph.node(wallPos)->state = NodeState::Free;
    }

    void DFSMazeGenerator::DFS(PDVec2i from, PAIlatticeGraph &latGraph, RandomIntegers & ri)
    {
        pathStack.push(latGraph.node(from));
        while (!pathStack.empty())
        {
            auto currentNode = pop(pathStack);
            visited.push_back(currentNode);
            auto neighbors = getAvailableneighbors(latGraph, currentNode);
            if (!neighbors.empty())
            {
                std::size_t randNumber = static_cast<std::size_t>(ri.getRandomInteger() % neighbors.size());
                for (std::size_t i = 0; i < neighbors.size(); ++i)
                {
                    connectNodes(latGraph, currentNode, neighbors[i]);
                    if (i != randNumber)
                    {
                        pathStack.push(neighbors[i]);
                        visited.push_back(neighbors[i]);
                    }
                }
                pathStack.push(neighbors[randNumber]);
            }
        }
    }

    std::vector<Node *> DFSMazeGenerator::getAvailableneighbors(PAIlatticeGraph &latGraph, PDNode *node) const
    {
        const std::vector<Vec2i> neighborOffsets = {Vec2i(-2, 0), Vec2i(2, 0), Vec2i(0, -2), Vec2i(0, 2)};
        std::vector<PDNode *> legalNeighbors;
        for (auto offset : neighborOffsets)
        {
            auto potentialNeighbor = node->location + offset;
            if (latGraph.inBounds(potentialNeighbor) && !inVector(visited, latGraph.node(potentialNeighbor)))
            {
                legalNeighbors.push_back(latGraph.node(potentialNeighbor));
            }
        }
        return legalNeighbors;
    }

    void DFSMazeGenerator::setWalls(ILatticeGraph &latGraph)
    {
        for (std::size_t h = 0; h < latGraph.height(); ++h)
        {
            for (std::size_t w = 0; w < latGraph.width(); ++w)
            {
                if (!isEven(h) || !isEven(w))
                {
                    auto pos = Vec2i(static_cast<int32_t>(h), static_cast<int32_t>(w));
                    latGraph.node(pos)->state = NodeState::Blocked;
                }
            }
        }
    }
}