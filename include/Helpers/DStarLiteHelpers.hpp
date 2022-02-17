#ifndef CDC2E736_775D_4CD3_B2C9_3AF63B5AE551
#define CDC2E736_775D_4CD3_B2C9_3AF63B5AE551

#include "Node.hpp"
#include <limits>

namespace Pathfinding::Helpers
{
    class DStarLiteHelpers
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDNodeState = Pathfinding::Datastructures::NodeState;
        public:
            static double infinity()
            {
                return std::numeric_limits<double>::infinity();
            }

            static bool locallyConsistent(const PDNode *node)
            {
                return node->g == node->rhs;
            }

            static bool locallyOverconsistent(const PDNode *node)
            {
                return node->g > node->rhs;
            }

            static bool blocked(const PDNode *node)
            {
                return node->state == PDNodeState::Blocked;
            }
    };
}

#endif /* CDC2E736_775D_4CD3_B2C9_3AF63B5AE551 */
