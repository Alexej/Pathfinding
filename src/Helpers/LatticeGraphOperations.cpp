#include "LatticeGraphOperations.hpp"
#include "Node.hpp"

using Pathfinding::Datastructures::Node;
using Pathfinding::Datastructures::NodeState;

namespace Pathfinding::Helpers
{
    LatticeGraphOperations::LatticeGraphOperations(LatticeGraph * graph)
        : graphPtr(graph)
    {
        resize();
    }

    void LatticeGraphOperations::resize()
    {
        int32_t heightI = static_cast<int32_t>(graphPtr->height());
        int32_t widthI = static_cast<int32_t>(graphPtr->width());
        goalLocation_ = GraphLocation(heightI - 1, widthI - 1);
        startLocation_ = GraphLocation(0,0);
        graphPtr->node(goalLocation_).state = NodeState::Goal;
        graphPtr->node(startLocation_).state = NodeState::Start;
    }

    std::size_t LatticeGraphOperations::width() const
    {
        return graphPtr->width();
    }

    std::size_t LatticeGraphOperations::height() const
    {
        return graphPtr->height();
    }

    GraphLocation LatticeGraphOperations::startLocation() const
    {
        return startLocation_;
    }

    GraphLocation LatticeGraphOperations::goalLocation() const
    {
        return goalLocation_;
    }

    void LatticeGraphOperations::setGoal(GraphLocation location)
    {
        if(graphPtr->node(location).state == NodeState::Free)
        {
            graphPtr->node(goalLocation_).state = NodeState::Free;
            goalLocation_ = location;
            graphPtr->node(goalLocation_).state = NodeState::Goal;
        }
    }

    void LatticeGraphOperations::setStart(GraphLocation location)
    {
        if(graphPtr->node(location).state == NodeState::Free)
        {
            graphPtr->node(startLocation_).state = NodeState::Free;
            startLocation_ = location;
            graphPtr->node(startLocation_).state = NodeState::Start;
        }
    }

    void LatticeGraphOperations::blockNode(GraphLocation location)
    {
        if (graphPtr->node(location).state == NodeState::Free)
        {
            graphPtr->node(location).state = NodeState::Blocked;
        }
    }

    void LatticeGraphOperations::clearNode(GraphLocation location)
    {

        if (graphPtr->node(location).state == NodeState::Blocked)
        {
            graphPtr->node(location).state = NodeState::Free;
        }
    }

    bool LatticeGraphOperations::inBounds(GraphLocation location) const
    {
        return graphPtr->inBounds(location);
    }
}