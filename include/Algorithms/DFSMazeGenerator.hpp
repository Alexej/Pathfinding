#ifndef A6815231_9623_4CAC_A973_3D5406AD5FA6
#define A6815231_9623_4CAC_A973_3D5406AD5FA6

#include <vector>
#include <stack>

#include "IMazeGenerator.hpp"
#include "Vec2.hpp"
#include "Node.hpp"


//https://hurna.io/academy/algorithms/maze_generator/dfs.html
namespace Pathfinding::Algorithms
{
   inline Pathfinding::Datastructures::Vec2i 
    getWallPosition(Pathfinding::Datastructures::Node * from, 
                    Pathfinding::Datastructures::Node * to)
    {
        Pathfinding::Datastructures::Vec2i wallPosition;
        if(from->location.height == to->location.height)
        {
            wallPosition = {from->location.height, std::min(from->location.width, to->location.width) + 1};
        }
        else
        {
            wallPosition = {std::min(from->location.height, to->location.height) + 1, to->location.width};
        }
        return wallPosition;
    } 

    template<typename IntegerType>
    bool isEven(IntegerType number)
    {
        static_assert(std::is_integral<IntegerType>::value, "Integral required.");
        return number % 2 == 0;
    }

    template<typename ElementType>
    ElementType pop(std::stack<ElementType> & stack)
    {
        auto lastTop = stack.top();
        stack.pop();
        return lastTop;
    }

    template<typename ElementType>
    inline bool inVector(std::vector<ElementType> vec, ElementType element)
    {
        return std::find(vec.begin(), vec.end(), element) != vec.end();
    }

    class DFSMazeGenerator final : public Pathfinding::Abstract::IMazeGenrator
    {
        private:
            using PAIlatticeGraph = Pathfinding::Abstract::ILatticeGraph;
            using PDVec2i = Pathfinding::Datastructures::Vec2i;
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            void generate(PAIlatticeGraph & latGraph) override;
        private:
            void setWalls(PAIlatticeGraph & latGraph);
            void DFS(PDVec2i from, PAIlatticeGraph & latGraph);
            std::vector<PDNode *> getAvailableneighbors(PAIlatticeGraph & latGraph, PDNode * node) const;
            void connectNodes(PAIlatticeGraph & latGraph, PDNode * from ,PDNode * to);
        private:
            std::vector<PDNode*> visited;
            std::stack<PDNode*> pathStack;
    };
}

#endif /* A6815231_9623_4CAC_A973_3D5406AD5FA6 */
