#ifndef AF527768_19D6_4F99_A25F_EEF58472AEC7
#define AF527768_19D6_4F99_A25F_EEF58472AEC7

#include <SFML/Graphics/Color.hpp>
#include <array>
#include "Constants.hpp"

namespace Pathfinding::Helpers
{
    inline sf::Color convertToSfmlColor(std::array<uint8_t, 3> color)
    {
        return {color[Pathfinding::Constants::RED], 
                color[Pathfinding::Constants::GREEN], 
                color[Pathfinding::Constants::BLUE]};
    }
}

#endif /* AF527768_19D6_4F99_A25F_EEF58472AEC7 */
