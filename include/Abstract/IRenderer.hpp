#ifndef E0993BE7_1552_4FDD_B2ED_36A6D9591A37
#define E0993BE7_1552_4FDD_B2ED_36A6D9591A37

#include <vector>

namespace Pathfinding::Datastructures
{
    struct Node;
    class LatticeGraph;
}

namespace Pathfinding::Abstract
{
    class IRenderer
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        public:
            virtual void render(const PDLatticeGraph &graph) = 0;
            virtual void renderPath(std::vector<PDNode *> path) = 0;
            virtual void update() = 0;
            virtual void reset() = 0;
    };
}

#endif /* E0993BE7_1552_4FDD_B2ED_36A6D9591A37 */
