#ifndef D789F663_4F72_4879_B70B_FE12085348E0
#define D789F663_4F72_4879_B70B_FE12085348E0

#include "IAStar.hpp"

#include <utility>

namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Datastructures { struct PathfinderReturnType; }

namespace Pathfinding::Algorithms
{
    struct QueueElement
    {
        QueueElement(std::pair<double, double> key_, Pathfinding::Datastructures::Node * node_)
        : key(key_), node(node_) {}
        
        std::pair<double, double> key;
        
        Pathfinding::Datastructures::Node * node;
        
    };

    class AStarQueueComperator
    {
    public:
        bool operator()(const QueueElement& lhs, const QueueElement& rhs)
        {
            return lhs.key > rhs.key;
        }
    };

    class AStar final : public Pathfinding::Abstract::IAStar
    {
        private:
            using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;
            using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        public:
            PDPathfinderReturnType calculatePath(const std::shared_ptr<PAALatGraphWr> graphWrapper) const override;
    };
}

#endif /* D789F663_4F72_4879_B70B_FE12085348E0 */
