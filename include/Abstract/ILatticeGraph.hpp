#ifndef A7E4056A_9F95_44D2_A6A6_79885E3D6223
#define A7E4056A_9F95_44D2_A6A6_79885E3D6223

#include <vector>
#include <SFML/Graphics/Drawable.hpp>

#include "Vec2.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph : public sf::Drawable
    {
        public:
            virtual bool inBounds(Pathfinding::Datastructures::Vec2i location) const = 0;

            virtual Pathfinding::Datastructures::Node *node(Pathfinding::Datastructures::Vec2i location) = 0;

            virtual const Pathfinding::Datastructures::Node * node(Pathfinding::Datastructures::Vec2i location) const = 0;

            virtual void reset() = 0;

            virtual void update() = 0;

            virtual void resize(int32_t height, int32_t width) = 0;
            
            virtual std::size_t width() const = 0;
            
            virtual std::size_t height() const = 0;
                        
            virtual ~ILatticeGraph() = default;
            
    };
}

#endif /* A7E4056A_9F95_44D2_A6A6_79885E3D6223 */
