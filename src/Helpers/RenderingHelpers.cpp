#include "RenderingHelpers.hpp"

#include <numbers>

#include "Constants.hpp"
#include "CppHelpers.hpp"

namespace Pathfinding::Helpers
{
    sf::Color convertToSfmlColor(std::array<uint8_t, 3> color)
    {
        return {color[Pathfinding::Constants::RED],
                color[Pathfinding::Constants::GREEN],
                color[Pathfinding::Constants::BLUE]};
    }

    sf::Vector2f getNodePosition(const Pathfinding::Datastructures::Node *node, int32_t sideLength)
    {
        float nodesHorF = static_cast<float>(node->location.width);
        float nodesVertF = static_cast<float>(node->location.height);
        float sideLengthF = static_cast<float>(sideLength);
        float positionHor = nodesHorF * sideLengthF;
        float positionVer = nodesVertF * sideLengthF;
        return {positionHor, positionVer};
    }

    std::string dToStr(double d)
    {
        std::string dStr = std::to_string(d);
        return getSubstrBeforeChar(dStr, '.');
    }

    double getAngleBetweenTwoNodes(const Pathfinding::Datastructures::Node* n1, const Pathfinding::Datastructures::Node* n2)
    {
        float y1 = static_cast<float>(n1->location.height);
        float x1 = static_cast<float>(n1->location.width);
        float y2 = static_cast<float>(n2->location.height);
        float x2 = static_cast<float>(n2->location.width);
        return std::atan2(y2 - y1, x2 - x1) * (180.0 / std::numbers::pi);
    }

    bool diagonal(double angle)
    {
        return std::abs(angle) == 45 || std::abs(angle) == 135;
    }

    
    sf::Color stateColor(Pathfinding::Datastructures::NodeState state)
    {
        sf::Color color;
        switch (state)
        {
        case Pathfinding::Datastructures::NodeState::Free:
            color = convertToSfmlColor(Pathfinding::Constants::FREE_NODE_COLOR);
            break;
        case Pathfinding::Datastructures::NodeState::Blocked:
            color = convertToSfmlColor(Pathfinding::Constants::BLOCKED_NODE_COLOR);
            break;
        case Pathfinding::Datastructures::NodeState::Frontier:
            color = convertToSfmlColor(Pathfinding::Constants::FRONTIER_NODE_COLOR);
            break;
        case Pathfinding::Datastructures::NodeState::Visited:
            color = convertToSfmlColor(Pathfinding::Constants::VISITED_NODE_COLOR);
            break;
        case Pathfinding::Datastructures::NodeState::Start:
            color = convertToSfmlColor(Pathfinding::Constants::START_NODE_COLOR);
            break;
        case Pathfinding::Datastructures::NodeState::Goal:
            color = convertToSfmlColor(Pathfinding::Constants::GOAL_NODE_COLOR);
            break;
        }
        return color;
    }
}