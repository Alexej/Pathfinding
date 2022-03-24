#include "LPAStar.hpp"

namespace Pathfinding::Algorithms
{
        LPAStar::LPAStar(std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr_)
        : AIncrementalInformedAlgorithm(latticeGraphWrapperSPtr_) {}
        
        void LPAStar::initialize()
        {
            latticeGraphWrapperSPtr->goalNode()->rhs = 0;
            insertIntoQueueAndUpdateStateAndKey(latticeGraphWrapperSPtr->goalNode());
        }
        
        
        void LPAStar::reset()
        {
            U.reset();
            nodesChanged.clear();
            nodexExpanded.clear();
        }
        
        void LPAStar::addChangedNode(PDNode *node)
        {
            for (auto &succ : LatticeGraphHelpers::neighbors(latticeGraphWrapperSPtr->latGraphSPtr, node))
            {
                nodesChanged.insert(succ);
            }
            nodesChanged.insert(node);
        }

        PDKey LPAStar::calculateKey(const PDNode * node) const
        {
            auto pseudoG = std::min(s->g, s->rhs);
            auto k1 = pseudoG + heuristicUPtr->calculate(sStart, s);
            auto k2 = pseudoG;
            return {k1, k2};
        }

        void LPAStar::updateKey(PDNode * node)
        {
            s->key = calculateKey(s);
        }
        
        PDPathfinderReturnType LPAStar::initialRun()
        {

        }
        
        PDPathfinderReturnType LPAStar::followingRun()
        {

        }
}