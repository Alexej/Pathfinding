#ifndef A8F39E2A_B87B_43DF_A67F_993CBD86DC47
#define A8F39E2A_B87B_43DF_A67F_993CBD86DC47

#include <vector>
#include <memory>
#include <functional>

#include "Vec2.hpp"

namespace Pathfinding::Abstract { class ILatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Helpers
{
    class LatticeGraphHelpers
    {
    private:
        using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        template<typename T>
        using shptr = std::shared_ptr<T>;
    public:
        static std::vector<PDNode *> neighbors(shptr<PAILatticeGraph> latticeGraphSPtr, PDNode *node);
        
        static void initRandomGraph(shptr<PAILatticeGraph> latticeGraphSPtr);
        
        static void blockNode(shptr<PAILatticeGraph> latticeGraphSPtr, PDVec2i location);
        
        static void clearNode(shptr<PAILatticeGraph> latticeGraphSPtr, PDVec2i location);
        
        static void  iterateOverALatticeGraphConst(const shptr<PAILatticeGraph> latticeGraphSPtr,
                                                     std::function<void(const PDNode * node, int32_t h, int32_t w)>);
                                                     
        static void  iterateOverALatticeGraph(shptr<PAILatticeGraph> latticeGraphSPtr,
                                                     std::function<void(PDNode * node, int32_t h, int32_t w)>);                              
    };
}

#endif /* A8F39E2A_B87B_43DF_A67F_993CBD86DC47 */
