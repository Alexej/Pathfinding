#ifndef A8F39E2A_B87B_43DF_A67F_993CBD86DC47
#define A8F39E2A_B87B_43DF_A67F_993CBD86DC47

#include <vector>
#include "Vec2.hpp"
#include <memory>

namespace Pathfinding::Abstract
{
    class ALatticeGraphWrapper;
}

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Helpers
{
    class ALatGrWrHelpers
    {
    private:
        using PAALatticeGraphWrapper = Pathfinding::Abstract::ALatticeGraphWrapper;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
    public:
        static std::vector<PDNode *> neighbors(std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperSPtr, PDNode *node);
        static void initRandomGraph(std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperSPtr);
        static void blockNode(std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperSPtr, PDVec2i location);
        static void clearNode(std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperSPtr, PDVec2i location);
    };
}

#endif /* A8F39E2A_B87B_43DF_A67F_993CBD86DC47 */