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
        iterateOverALatticeGraphWrapper(latGraphWrapperSPtr, [](PDNode * node, int32_t h, int32_t w)
        {
            if (node->state == NodeState::Free && rand() % 3 == 0)
            {
                node->state = NodeState::Blocked;
            } 
        });
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

    void  ALatGrWrHelpers::iterateOverALatticeGraphWrapperConst(const std::shared_ptr<ALatticeGraphWrapper> latticeGraphWrapperSPtr,
                                                                 std::function<void(const Node * node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < latticeGraphWrapperSPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latticeGraphWrapperSPtr->width(); ++w)
            {
                func(latticeGraphWrapperSPtr->node(Vec2i(h,w)), h,w);
            }
        }
    }

    void  ALatGrWrHelpers::iterateOverALatticeGraphWrapper(std::shared_ptr<ALatticeGraphWrapper> latticeGraphWrapperSPtr,
                                                                 std::function<void(Node * node, int32_t h, int32_t w)> func)
    {
        for (int32_t h = 0; h < latticeGraphWrapperSPtr->height(); ++h)
        {
            for (int32_t w = 0; w < latticeGraphWrapperSPtr->width(); ++w)
            {
                func(latticeGraphWrapperSPtr->node(Vec2i(h,w)), h,w);
            }
        }
    }

}

#endif /* B15A85B1_6958_4A28_833B_2236EE9D4AE5 */
