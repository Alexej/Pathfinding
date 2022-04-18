#ifndef B3DF59F7_C3A6_4542_B581_A035E9C01278
#define B3DF59F7_C3A6_4542_B581_A035E9C01278

#include <memory>
#include <functional>
#include "InformedSearchFunctions.hpp"

namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Datastructures { struct PathfinderReturnType; }

namespace Pathfinding::Abstract
{
    class AIncrementalInformedAlgorithm
    {
        public:
            explicit AIncrementalInformedAlgorithm(std::shared_ptr<Pathfinding::Abstract::ALatGraphWr> latticeGraphWrapperSPtr_,
                                                   Pathfinding::Datastructures::InformedSearchFunctions & functions_)
            : latticeGraphWrapperSPtr(latticeGraphWrapperSPtr_), functions(functions_) {}

            void addFoundPathCallBack(std::function<void(void)> callBack)
            {
                doneCallBack = callBack;
            }

            void addNoPathCallBack(std::function<void(void)> callBack)
            {
                noPathCallBack = callBack;
            }
            
            virtual void initialize() = 0;
            
            virtual void reset() = 0;

            virtual void addChangedNode(Pathfinding::Datastructures::Node *node) = 0;

            virtual Pathfinding::Datastructures::PathfinderReturnType initialRun() = 0;
            
            virtual Pathfinding::Datastructures::PathfinderReturnType followingRun() = 0;

            virtual ~AIncrementalInformedAlgorithm() = default;

        protected:
            std::shared_ptr<Pathfinding::Abstract::ALatGraphWr> latticeGraphWrapperSPtr = nullptr;
            const Pathfinding::Datastructures::InformedSearchFunctions & functions;
            std::function<void(void)> doneCallBack;
            std::function<void(void)> noPathCallBack;
            
    };
}

#endif /* B3DF59F7_C3A6_4542_B581_A035E9C01278 */
