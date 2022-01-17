#include "LatticeGraphOperations.hpp"
#include "Node.hpp"

using Pathfinding::Datastructures::NodeState;
using Pathfinding::Datastructures::Node;



namespace Pathfinding::Helpers
{
    LatticeGraphOperations::LatticeGraphOperations(LatticeGraph * graph)
    : graphPtr(graph) {

    }

    void LatticeGraphOperations::setGoal(GraphLocation location)
    {
        graphPtr->node(location).state = NodeState::Free;
        goalLocation = location;
        graphPtr->node(location).state = NodeState::Goal;
    }

    void LatticeGraphOperations::setStart(GraphLocation location)
    {
        graphPtr->node(location).state = NodeState::Free;
        startLocation = location;
        graphPtr->node(location).state = NodeState::Start;
    }

    void LatticeGraphOperations::blockNode(GraphLocation location)
    {
        if(graphPtr->node(location).state == NodeState::Free)
        {
            graphPtr->node(location).state = NodeState::Blocked;
        }
    }

    void LatticeGraphOperations::clearNode(GraphLocation location)
    {
        if(graphPtr->node(location).state == NodeState::Blocked)
        {
            graphPtr->node(location).state = NodeState::Free;
        }
    }
}