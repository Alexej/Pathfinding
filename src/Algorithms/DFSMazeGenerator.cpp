#include "DFSMazeGenerator.hpp"
#include "ILatticeGraph.hpp"
#include "LatticeGraph.hpp"
#include <type_traits>
#include "Node.hpp"
#include "Vec2.hpp"

namespace Pathfinding::Algorithms
{
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::Vec2i;

    void DFSMazeGenerator::generate(ILatticeGraph & latGraph)
    {
        setWalls(latGraph);
        DFS(Vec2i(0,0), latGraph);
    }

    void DFSMazeGenerator::connectNodes(PAIlatticeGraph & latGraph, PDNode * from ,PDNode * to)
    {
        Vec2i wallPos = getWallPosition(from, to);
        latGraph.node(wallPos)->state = NodeState::Free;
    }


    void DFSMazeGenerator::DFS(PDVec2i from, PAIlatticeGraph & latGraph)
    {
        pathStack.push(latGraph.node(from));
        while(!pathStack.empty())
        {
            auto currentNode = pop(pathStack);
            visited.push_back(currentNode);
            auto neighbors = getAvailableneighbors(latGraph, currentNode);
            if(!neighbors.empty())
            {
                std::size_t randNumber = static_cast<std::size_t>(rand() % neighbors.size());
                for(std::size_t i = 0; i < neighbors.size(); ++i)
                {
                    connectNodes(latGraph, currentNode, neighbors[i]);
                    if(i != randNumber) 
                    { 
                        pathStack.push(neighbors[i]); 
                        visited.push_back(neighbors[i]);
                    }
                }
                pathStack.push(neighbors[randNumber]);
            }
        }
    }

    std::vector<Node*> DFSMazeGenerator::getAvailableneighbors(PAIlatticeGraph & latGraph, PDNode * node) const
    {
        const std::vector<Vec2i> neighborOffsets = {Vec2i(-2,0), Vec2i(2,0), Vec2i(0,-2), Vec2i(0,2)};
        std::vector<PDNode *> legalNeighbors;
        for(auto offset : neighborOffsets)
        {
            auto potentialNeighbor = node->location + offset;
            if(latGraph.inBounds(potentialNeighbor) && !inVector(visited, latGraph.node(potentialNeighbor)))
            {
                legalNeighbors.push_back(latGraph.node(potentialNeighbor));
            }
        }
        return legalNeighbors;
    }
    
    void DFSMazeGenerator::setWalls(ILatticeGraph & latGraph)
    {
        for(std::size_t h = 0; h < latGraph.height(); ++h)
        {
            for(std::size_t w = 0; w < latGraph.width(); ++w)
            {
                if(!isEven(h) || !isEven(w))
                {
                    auto pos = Vec2i(static_cast<int32_t>(h),static_cast<int32_t>(w));
                    latGraph.node(pos)->state = NodeState::Blocked;
                }
            }
        }
    }
}