#ifndef EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA
#define EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA

#include <SFML/System/Vector2.hpp>
#include "Vector2.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::Vector2i;
    Vector2i mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength);
}

#endif /* EC2C5678_AF5E_406F_AA9A_2BDDCA1C64FA */
