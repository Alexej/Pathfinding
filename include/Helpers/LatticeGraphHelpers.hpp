#ifndef A8F39E2A_B87B_43DF_A67F_993CBD86DC47
#define A8F39E2A_B87B_43DF_A67F_993CBD86DC47

#include <vector>
#include <memory>
#include <functional>

#include "Vec2.hpp"

namespace Pathfinding::Abstract { class ILatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Core { class RandomIntegers; }

namespace Pathfinding::Helpers
{
    class ILatticeGraphHelpers
    {
    private:
        using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PCRandomIntegers = Pathfinding::Core::RandomIntegers;
    public:
        static std::vector<PDNode *> neighbors(PAILatticeGraph & iLatticeGraph, PDNode *node);
        
        static void initRandomGraph(PAILatticeGraph & iLatticeGraph, PCRandomIntegers & ri);
        
        static void blockNode(PAILatticeGraph & iLatticeGraph, PDVec2i location);
        
        static void clearNode(PAILatticeGraph & iLatticeGraph, PDVec2i location);
        
        static void  iterateOverLatticeGraphConst(const PAILatticeGraph & iLatticeGraph,
                                                std::function<void(const PDNode * node, int32_t h, int32_t w)>);
                                                     
        static void  iterateOverLatticeGraph(PAILatticeGraph & iLatticeGraph,
                                                std::function<void(PDNode * node, int32_t h, int32_t w)>);                              
    };
}

#endif /* A8F39E2A_B87B_43DF_A67F_993CBD86DC47 */
