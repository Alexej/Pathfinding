#ifndef AB72A75C_C14C_4E10_BC57_FC713E017903
#define AB72A75C_C14C_4E10_BC57_FC713E017903


#include <memory>

#include "AInformedSearchAlgorithm.hpp"

namespace Pathfinding::Datastructures { struct PathfinderReturnType; }

namespace Pathfinding::Abstract
{
    class ALatGraphWr;
    class IAStar : public AInformedSearchAlgorithm
    {
    public:
        virtual Pathfinding::Datastructures::PathfinderReturnType calculatePath(const ALatGraphWr & graphWrapper) const = 0;

        virtual ~IAStar() = default;

    };
}

#endif /* AB72A75C_C14C_4E10_BC57_FC713E017903 */
