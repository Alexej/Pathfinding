#ifndef E74645A2_E778_4D73_9B8B_A89EF935C407
#define E74645A2_E778_4D73_9B8B_A89EF935C407

#include <functional>
#include <memory>
#include <vector>
#include "IInformedSearchAlgorithm.hpp"

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class IDStarLite : public IInformedSearchAlgorithm
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            virtual void addDoneCallBack(std::function<void(void)> callBack) = 0;
            virtual void addNoPathCallBack(std::function<void(void)> callBack) = 0;
            virtual void initialize() = 0;
            virtual void computePath() = 0;
            virtual void reset() = 0;
            virtual void moveStart() = 0;
            virtual void addChangedNode(PDNode *node) = 0;
            virtual std::vector<PDNode *> path() const = 0;
            virtual void initialRun() = 0;
            virtual ~IDStarLite() = default;
    };
}

#endif /* E74645A2_E778_4D73_9B8B_A89EF935C407 */
