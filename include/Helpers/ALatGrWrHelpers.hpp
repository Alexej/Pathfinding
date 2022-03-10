#ifndef A8F39E2A_B87B_43DF_A67F_993CBD86DC47
#define A8F39E2A_B87B_43DF_A67F_993CBD86DC47

#include <vector>
#include <memory>
#include <functional>
#include "Vec2.hpp"

namespace Pathfinding::Abstract { class ALatticeGraphWrapper; }
namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Helpers
{
    class ALatGrWrHelpers
    {
    private:
        using PAALatGraphWr = Pathfinding::Abstract::ALatticeGraphWrapper;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        template<typename T>
        using shptr = std::shared_ptr<T>;
    public:
        static std::vector<PDNode *> neighbors(shptr<PAALatGraphWr> latGraphWrapperSPtr, PDNode *node);
        
        static void initRandomGraph(shptr<PAALatGraphWr> latGraphWrapperSPtr);
        
        static void blockNode(shptr<PAALatGraphWr> latGraphWrapperSPtr, PDVec2i location);
        
        static void clearNode(shptr<PAALatGraphWr> latGraphWrapperSPtr, PDVec2i location);
        
        static void  iterateOverALatticeGraphWrapperConst(const shptr<PAALatGraphWr> latticeGraphWrapperSPtr,
                                                     std::function<void(const PDNode * node, int32_t h, int32_t w)>);
                                                     
        static void  iterateOverALatticeGraphWrapper(shptr<PAALatGraphWr> latticeGraphWrapperSPtr,
                                                     std::function<void(PDNode * node, int32_t h, int32_t w)>);
                                                     
    };
}

#endif /* A8F39E2A_B87B_43DF_A67F_993CBD86DC47 */
