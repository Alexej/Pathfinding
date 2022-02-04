#include "SFMLHelpers.hpp"

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::Vec2i;
    Vec2i mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength)
    {
        int32_t faH = pos.y / currentSideLength;
        int32_t faW = pos.x / currentSideLength;
        return {faH, faW};
    }
}