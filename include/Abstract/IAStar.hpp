#ifndef AB72A75C_C14C_4E10_BC57_FC713E017903
#define AB72A75C_C14C_4E10_BC57_FC713E017903


#include <memory>
#include "AInformedSearchAlgorithm.hpp"

namespace Pathfinding::Datastructures
{
    struct AStarReturnType;
}

namespace Pathfinding::Abstract
{
    class ALatticeGraphWrapper;
    class IAStar : public AInformedSearchAlgorithm
    {
    private:
        using PDAStarReturnType = Pathfinding::Datastructures::AStarReturnType;
    public:
        virtual PDAStarReturnType calculatePath(std::shared_ptr<ALatticeGraphWrapper> graphWrapper) = 0;
        virtual ~IAStar() = default;
    };
}

#endif /* AB72A75C_C14C_4E10_BC57_FC713E017903 */
