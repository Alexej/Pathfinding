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
        if (renderNodeInfo())
        {
            prepareNodeInfo(g, rhs, key);
        }

        factorRect.setFillColor(sf::Color(100 + 28 * factor, 0, 140 - 28 * factor));
        nodeRect.setFillColor(colors->getColor(state));
    }

    void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(nodeRect);
        if (renderNodeInfo())
        {
            target.draw(rhsText);
            target.draw(gText);
            target.draw(keyText);
            if (state != NodeState::Blocked)
            {
                target.draw(factorRect);
            }
        }
    }
}