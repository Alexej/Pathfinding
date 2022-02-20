#ifndef B15A85B1_6958_4A28_833B_2236EE9D4AE5
#define B15A85B1_6958_4A28_833B_2236EE9D4AE5

#include "ALatGrWrHelpers.hpp"
#include "ALatticeGraphWrapper.hpp"
#include "ILatticeGraph.hpp"
#include "Node.hpp"
#include "Vec2.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;

    void ALatGrWrHelpers::initRandomGraph(std::shared_ptr<ALatticeGraphWrapper> latGraphWrapperSPtr)
    {
        for (int32_t h = 0; h < latGraphWrapperSPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latGraphWrapperSPtr->width(); ++w)
            {
                if (latGraphWrapperSPtr->node(Vec2i(h, w))->state == NodeState::Free && rand() % 3 == 0)
                {
                    latGraphWrapperSPtr->node(Vec2i(h, w))->state = NodeState::Blocked;
                }
            }
        }
    }
    std::vector<Node *> 
    ALatGrWrHelpers::neighbors(std::shared_ptr<ALatticeGraphWrapper> latGraphWrapperSPtr, Node *node_)
    {
        std::vector<Node *> nbors;
        int32_t hFrom = node_->location.height - 1;
        int32_t hTo = node_->location.height + 1;
        int32_t wFrom = node_->location.width - 1;
        int32_t wTo = node_->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                auto coord = Vec2i(h, w);
                if (latGraphWrapperSPtr->inBounds(coord) && node_->location != coord)
                {
                    nbors.push_back(latGraphWrapperSPtr->node(coord));
                }
            }
        }
        return nbors;
    }

    void ALatGrWrHelpers::blockNode(std::shared_ptr<ALatticeGraphWrapper> latGraphWrapper, Vec2i location)
    {
        if (latGraphWrapper->node(location)->state != NodeState::Start && 
            latGraphWrapper->node(location)->state != NodeState::Goal)
        {
            latGraphWrapper->node(location)->state = NodeState::Blocked;
        }
    }

    void ALatGrWrHelpers::clearNode(std::shared_ptr<ALatticeGraphWrapper> latGraphWrapper, Vec2i location)
    {
        if (latGraphWrapper->node(location)->state == NodeState::Blocked)
        {
            if (latGraphWrapper->node(location)->visitedOnce)
            {
                latGraphWrapper->node(location)->state = NodeState::Visited;
            }
            else
            {
                latGraphWrapper->node(location)->state = NodeState::Free;
            }
        }
    }

}

#endif /* B15A85B1_6958_4A28_833B_2236EE9D4AE5 */
