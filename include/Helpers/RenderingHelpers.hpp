#ifndef AF527768_19D6_4F99_A25F_EEF58472AEC7
#define AF527768_19D6_4F99_A25F_EEF58472AEC7

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>
#include <type_traits>
#include "Vec2.hpp"
#include "Node.hpp"


namespace Pathfinding::Helpers
{
    template<typename VectorType> Pathfinding::Datastructures::Vec2<VectorType> 
    swapElements(Pathfinding::Datastructures::Vec2<VectorType> vec)
    {
        return {vec.width, vec.height};
    }

    template<typename DrawableType>
    void drawArrayOfDrawables(sf::RenderTarget& target, const std::vector<DrawableType> & objects)
    {
        static_assert(std::is_base_of<sf::Drawable, DrawableType>(), "Element not drawable");
        for(const auto & element : objects)
        {
            target.draw(element);
        }
    }


    sf::Color convertToSfmlColor(std::array<uint8_t, 3> color);

    sf::Vector2f getNodePosition(const Pathfinding::Datastructures::Node *node, int32_t sideLength);

    /**
     * @brief converts double to string and removes zeros and dot.
     * under the assumption  rhs, g and key values are always integers.
     * @param d
     * @return std::string
     */
    std::string dToStr(double d);

    double getAngleBetweenTwoNodes(const Pathfinding::Datastructures::Node *n1, const Pathfinding::Datastructures::Node *n2);

    bool diagonal(double angle);
    
    sf::Color stateColor(Pathfinding::Datastructures::NodeState state);
}

#endif /* AF527768_19D6_4F99_A25F_EEF58472AEC7 */
