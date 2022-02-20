#ifndef EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA
#define EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA

#include <SFML/System/Vector2.hpp>
#include "Vec2.hpp"

namespace Pathfinding::Helpers
{
    Pathfinding::Datastructures::Vec2i mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength);
}

#endif /* EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA */
