#ifndef EF091C2C_702A_4E72_882C_6AB418436A17
#define EF091C2C_702A_4E72_882C_6AB418436A17

#include <SFML\System\Vector2.hpp>

namespace Pathfinding::Events
{
    struct MouseData
    {
        sf::Vector2i cursorPosition;
        int32_t wheelDelta;
    };
}

#endif /* EF091C2C_702A_4E72_882C_6AB418436A17 */


