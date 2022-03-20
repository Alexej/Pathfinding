#ifndef B3DF59F7_C3A6_4542_B581_A035E9C01278
#define B3DF59F7_C3A6_4542_B581_A035E9C01278

#include <memory>
#include <functional>
#include "AInformedSearchAlgorithm.hpp"

namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Datastructures { struct PathfinderReturnType; }

namespace Pathfinding::Abstract
{
    class AIncrementalInformedAlgorithm : public AInformedSearchAlgorithm
    {
        private:
            using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
            using PDNode = Pathfinding::Datastructures::Node;
            using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;

        public:
            explicit AIncrementalInformedAlgorithm(std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr_)
            : latticeGraphWrapperSPtr(latticeGraphWrapperSPtr_) {}

            virtual void addDoneCallBack(std::function<void(void)> callBack) = 0;
            
            virtual void addNoPathCallBack(std::function<void(void)> callBack) = 0;
            
            virtual void initialize() = 0;
            
            virtual void reset() = 0;

            virtual void addChangedNode(PDNode *node) = 0;

            virtual PDPathfinderReturnType initialRun() = 0;
            
            virtual PDPathfinderReturnType followingRun() = 0;

            virtual ~AIncrementalInformedAlgorithm() = default;
        protected:
            std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr = nullptr;
    };
}

#endif /* B3DF59F7_C3A6_4542_B581_A035E9C01278 */
