#ifndef C6BCD717_D222_4EF4_9463_0AFA2C68BD0A
#define C6BCD717_D222_4EF4_9463_0AFA2C68BD0A

#include "GraphLocation.hpp"
#include "LatticeGraph.hpp"

using Pathfinding::Datastructures::LatticeGraph;
using Pathfinding::Datastructures::GraphLocation;

namespace Pathfinding::Helpers
{
    class LatticeGraphOperations
    {
        public:
            explicit LatticeGraphOperations(LatticeGraph * graph);
            void setGoal(GraphLocation location);
            void setStart(GraphLocation location);
            void blockNode(GraphLocation location);
            void clearNode(GraphLocation location);
            std::size_t width() const;
            std::size_t height() const;
            GraphLocation startLocation() const;
            GraphLocation goalLocation() const;
            bool inBounds(GraphLocation location) const;
        private:
            LatticeGraph * graphPtr;
            GraphLocation startLocation_;
            GraphLocation goalLocation_;
    };
}

#endif /* C6BCD717_D222_4EF4_9463_0AFA2C68BD0A */
