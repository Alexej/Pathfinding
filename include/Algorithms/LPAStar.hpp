#ifndef B1DF0005_3F12_457B_B336_BD85CCCF269E
#define B1DF0005_3F12_457B_B336_BD85CCCF269E

#include <vector>
#include <functional>

#include "PriorityQueue.hpp"
#include "AIncrementalInformedAlgorithm.hpp"

namespace Pathfinding::Datastructures { struct Key;}
namespace Pathfinding::Datastructures { struct Node;}
namespace Pathfinding::Datastructures { struct PathfinderReturnType;}


namespace Pathfinding::Algorithms
{
    class LPAStar final : public Pathfinding::Abstract::AIncrementalInformedAlgorithm
    {
        private:
            using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
            using PDNode = Pathfinding::Datastructures::Node;
            using PDKey = Pathfinding::Datastructures::Key;
            using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;
            using PDPriorityQueue = Pathfinding::Datastructures::PriorityQueue;
        public:
            LPAStar() = default;
        
            explicit LPAStar(std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr);
            
            void initialize() override;
            
            PDPathfinderReturnType initialRun() override;
            
            PDPathfinderReturnType followingRun() override;
            
            void reset() override;
            
            void addChangedNode(PDNode *node) override;

        private:
            PDKey calculateKey(const PDNode * node) const;

            void updateKey(PDNode * node);

        private:
            PDPriorityQueue U;
            std::unordered_set<PDNode *> nodesChanged;
            std::vector<PDNode *> nodexExpanded;
    };
}

#endif /* B1DF0005_3F12_457B_B336_BD85CCCF269E */
