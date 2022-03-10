#ifndef A7E4056A_9F95_44D2_A6A6_79885E3D6223
#define A7E4056A_9F95_44D2_A6A6_79885E3D6223

#include <vector>
#include "Resizable2DArray.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph : public Resizable2DArray
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            virtual std::vector<PDNode> &operator[](std::size_t height) = 0;
            
            virtual const std::vector<PDNode> &operator[](std::size_t height) const = 0;
            
            virtual bool inBounds(int32_t height, int32_t width) const = 0;
            
            virtual ~ILatticeGraph() = default;
            
    };
}

#endif /* A7E4056A_9F95_44D2_A6A6_79885E3D6223 */
