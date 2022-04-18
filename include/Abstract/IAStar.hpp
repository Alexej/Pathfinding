#ifndef AB72A75C_C14C_4E10_BC57_FC713E017903
#define AB72A75C_C14C_4E10_BC57_FC713E017903


#include <memory>

namespace Pathfinding::Datastructures { struct PathfinderReturnType; }
namespace Pathfinding::Datastructures { struct InformedSearchFunctions; }

namespace Pathfinding::Abstract
{
    class ALatGraphWr;
    class IAStar
    {
        protected:
            using PDInformedSearchFunctions = Pathfinding::Datastructures::InformedSearchFunctions;
            using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;
        public:
            virtual PDPathfinderReturnType calculatePath(const ALatGraphWr & graphWrapper, 
                                                        const PDInformedSearchFunctions & functions) const = 0;

        virtual ~IAStar() = default;

    };
}

#endif /* AB72A75C_C14C_4E10_BC57_FC713E017903 */
