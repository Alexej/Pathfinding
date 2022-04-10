#ifndef ECA2282D_10B3_4CEE_951C_9DE558D84232
#define ECA2282D_10B3_4CEE_951C_9DE558D84232

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class IDrawNodeStrategy
    {
        public:
            virtual void draw(const Pathfinding::Datastructures::Node * node) = 0;

            virtual void resize() = 0;
    };
}

#endif /* ECA2282D_10B3_4CEE_951C_9DE558D84232 */
