#ifndef E74645A2_E778_4D73_9B8B_A89EF935C407
#define E74645A2_E778_4D73_9B8B_A89EF935C407

#include <functional>
#include <memory>
#include <vector>
#include "AInformedSearchAlgorithm.hpp"

namespace Pathfinding::Datastructures
{
    struct Node;
    struct PathfinderReturnType;
}

namespace Pathfinding::Abstract
{
    class IDStarLite : public AInformedSearchAlgorithm
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;
        public:
            virtual void addDoneCallBack(std::function<void(void)> callBack) = 0;
            virtual void addNoPathCallBack(std::function<void(void)> callBack) = 0;
            virtual void initialize() = 0;
            virtual void reset() = 0;
            virtual PDPathfinderReturnType initialRun() = 0;
            virtual PDPathfinderReturnType moveStart() = 0;
            virtual void addChangedNode(PDNode *node) = 0;
            virtual ~IDStarLite() = default;
    };
}

#endif /* E74645A2_E778_4D73_9B8B_A89EF935C407 */
