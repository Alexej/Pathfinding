#include "Node.hpp"
#include "NodeStateColors.hpp"

#include <iostream>
namespace Pathfinding::Datastructures
{
    using Pathfinding::Rendering::NodeStateColors;

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

    void Node::update()
    {
        prepareDrawableNode(*this);
    }

    void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        drawDrawableNode(target, state != NodeState::Blocked);
    }
}