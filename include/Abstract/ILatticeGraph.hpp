#ifndef A7E4056A_9F95_44D2_A6A6_79885E3D6223
#define A7E4056A_9F95_44D2_A6A6_79885E3D6223

#include <vector>

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class ILatticeGraph
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            virtual void resize(int32_t height, int32_t width) = 0;
            virtual std::vector<PDNode> &operator[](std::size_t height) = 0;
            virtual const std::vector<PDNode> &operator[](std::size_t height) const = 0;
            virtual bool inBounds(int32_t height, int32_t width) const = 0;
            virtual std::size_t width() const = 0;
            virtual std::size_t height() const = 0;
            virtual ~ILatticeGraph() = default;
    };
}

#endif /* A7E4056A_9F95_44D2_A6A6_79885E3D6223 */
