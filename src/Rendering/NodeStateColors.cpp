#include "NodeStateColors.hpp"
#include "RenderingHelpers.hpp"
#include "Constants.hpp"
#include "Node.hpp"

namespace Pathfinding::Rendering
{
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Helpers::convertToSfmlColor;
    using namespace Pathfinding::Constants;

    NodeStateColors::NodeStateColors()
    {
        reset();
    }
    
    sf::Color NodeStateColors::getColor(NodeState state) const
    {
        sf::Color color;
        switch (state)
        {
        case NodeState::Free:
            color = freeNodeColor;
            break;
        case NodeState::Frontier:
            color = frontierNodeColor;
            break;
        case NodeState::Visited:
            color = visitedNodeColor;
            break;
        case NodeState::Blocked:
            color = blockedNodeColor;
            break;
        case NodeState::Start:
            color = startNodeColor;
            break;
        case NodeState::Goal:
            color = goalNodeColor;
            break;
        }
        return color;
    }

    void NodeStateColors::reset()
    {
        freeNodeColor = convertToSfmlColor(FREE_NODE_COLOR);
        frontierNodeColor = convertToSfmlColor(FRONTIER_NODE_COLOR);
        visitedNodeColor = convertToSfmlColor(VISITED_NODE_COLOR);
        blockedNodeColor = convertToSfmlColor(BLOCKED_NODE_COLOR);
        startNodeColor = convertToSfmlColor(START_NODE_COLOR);
        goalNodeColor = convertToSfmlColor(GOAL_NODE_COLOR);
    }
}
