#ifndef A6815231_9623_4CAC_A973_3D5406AD5FA6
#define A6815231_9623_4CAC_A973_3D5406AD5FA6

#include <vector>
#include <stack>

#include "IMazeGenerator.hpp"
#include "Vec2.hpp"
#include "Node.hpp"

namespace Pathfinding::Core { class RandomIntegers; }

// https://hurna.io/academy/algorithms/maze_generator/dfs.html
namespace Pathfinding::Algorithms
{
    class DFSMazeGenerator final : public Pathfinding::Abstract::IMazeGenrator
    {
    private:
        using PAIlatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
        using RCRandomIntegers = Pathfinding::Core::RandomIntegers;

    public:
        void generate(PAIlatticeGraph &latGraph, RCRandomIntegers & ri) override;

    private:
        void setWalls(PAIlatticeGraph &latGraph);
        void DFS(PDVec2i from, PAIlatticeGraph &latGraph, RCRandomIntegers & ri);
        std::vector<PDNode *> getAvailableneighbors(PAIlatticeGraph &latGraph, PDNode *node) const;
        void connectNodes(PAIlatticeGraph &latGraph, PDNode *from, PDNode *to);

    private:
        std::vector<PDNode *> visited;
        std::stack<PDNode *> pathStack;
    };
}

#endif /* A6815231_9623_4CAC_A973_3D5406AD5FA6 */
