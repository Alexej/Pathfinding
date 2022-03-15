#ifndef AF527768_19D6_4F99_A25F_EEF58472AEC7
#define AF527768_19D6_4F99_A25F_EEF58472AEC7

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <array>
#include <numbers>

#include "Node.hpp"
#include "Constants.hpp"
#include "OtherHelpers.hpp"

namespace Pathfinding::Helpers
{
    class ColorGradient
    {
        public:
            void operator()(uint8_t & color, uint8_t incrementStep)
            {
                if(increment)
                {
                    if(color < Pathfinding::Constants::MAX_COLOR_CHANNEL) { color += incrementStep; }
                    else { increment = false; }
                }
                if(!increment)
                {
                    if(color > Pathfinding::Constants::MIN_COLOR_CHANNEL) { color -= incrementStep; }
                    else { increment = true; }
                }
            }
        private:
            bool increment = true;
    };


    inline sf::Color convertToSfmlColor(std::array<uint8_t, 3> color)
    {
        return {color[Pathfinding::Constants::RED],
                color[Pathfinding::Constants::GREEN],
                color[Pathfinding::Constants::BLUE]};
    }

    inline sf::Vector2f getNodePosition(const Pathfinding::Datastructures::Node *node, int32_t sideLength)
    {
        float nodesHorF = static_cast<float>(node->location.width);
        float nodesVertF = static_cast<float>(node->location.height);
        float sideLengthF = static_cast<float>(sideLength);
        float positionHor = nodesHorF * sideLengthF;
        float positionVer = nodesVertF * sideLengthF;
        return {positionHor, positionVer};
    }

    /**
     * @brief converts double to string and removes zeros and dot.
     * under the assumption  rhs, g and key values are always integers.
     * @param d
     * @return std::string
     */
    inline std::string dToStr(double d)
    {
        std::string dStr = std::to_string(d);
        return getSubstrBeforeChar(dStr, '.');
    }

    inline double getAngleBetweenTwoNodes(Pathfinding::Datastructures::Node *n1, Pathfinding::Datastructures::Node *n2)
    {
        float y1 = static_cast<float>(n1->location.height);
        float x1 = static_cast<float>(n1->location.width);
        float y2 = static_cast<float>(n2->location.height);
        float x2 = static_cast<float>(n2->location.width);
        return std::atan2(y2 - y1, x2 - x1) * (180.0 / std::numbers::pi);
    }

    inline bool diagonal(double angle)
    {
        return std::abs(angle) == 45 || std::abs(angle) == 135;
    }

    
    inline sf::Color stateColor(Pathfinding::Datastructures::NodeState state)
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

#endif /* AF527768_19D6_4F99_A25F_EEF58472AEC7 */
