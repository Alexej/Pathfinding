#include "Node.hpp"

#include <iostream>

#include "IDrawNodeStrategy.hpp"
namespace Pathfinding::Datastructures
{
    using Pathfinding::Abstract::IDrawNodeStrategy;


    bool operator==(const Node &lhs, const Node &rhs)
    {
        return lhs.location == rhs.location;
    }

    void Node::initNode()
    {
        state = NodeState::Free;
        rhs = std::numeric_limits<double>::infinity();
        g = std::numeric_limits<double>::infinity();
        visitedOnce = false;
        factor = 1;
    }

    void Node::reset()
    {
        initNode();
        key = Key();
    }


    void Node::draw(Pathfinding::Abstract::IDrawNodeStrategy & drawStrategy) const
    {
        drawStrategy.draw(this);
    }
}