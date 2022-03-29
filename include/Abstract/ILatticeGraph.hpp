#ifndef A7E4056A_9F95_44D2_A6A6_79885E3D6223
#define A7E4056A_9F95_44D2_A6A6_79885E3D6223

#include <vector>

#include "Resizable2DArray.hpp"
#include "Vec2.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph : public Resizable2DArray
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDVec2i = Pathfinding::Datastructures::Vec2i;

        public:
            virtual bool inBounds(PDVec2i location) const = 0;

            virtual PDNode *node(PDVec2i location) = 0;

            virtual const PDNode *node(PDVec2i location) const = 0;

            virtual void reset() = 0;
            
            virtual ~ILatticeGraph() = default;
            
    };
}

#endif /* A7E4056A_9F95_44D2_A6A6_79885E3D6223 */
