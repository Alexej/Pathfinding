#ifndef AF527768_19D6_4F99_A25F_EEF58472AEC7
#define AF527768_19D6_4F99_A25F_EEF58472AEC7

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <string>
#include "Node.hpp"


namespace Pathfinding::Helpers
{
    class ColorGradient
    {
        public:
            void operator()(uint8_t & color, uint8_t incrementStep);
        private:
            bool increment = true;
    };


    sf::Color convertToSfmlColor(std::array<uint8_t, 3> color);

    sf::Vector2f getNodePosition(const Pathfinding::Datastructures::Node *node, int32_t sideLength);

    /**
     * @brief converts double to string and removes zeros and dot.
     * under the assumption  rhs, g and key values are always integers.
     * @param d
     * @return std::string
     */
    std::string dToStr(double d);

    double getAngleBetweenTwoNodes(Pathfinding::Datastructures::Node *n1, Pathfinding::Datastructures::Node *n2);

    bool diagonal(double angle);
    
    sf::Color stateColor(Pathfinding::Datastructures::NodeState state);
}

#endif /* AF527768_19D6_4F99_A25F_EEF58472AEC7 */
